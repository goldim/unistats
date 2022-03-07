#include "perfomance.h"
#include <MathStats/sample_builder.h>
#include <MathStats/correlation.h>
#include <MathStats/anova.h>
#include <MathStats/ols.h>
#include "analyser.h"

#include <iostream>

using std::string;

Perfomance::Perfomance(const Config &cfg):
    _storage(cfg)
{
    _conditions.category = DomainFilter::dfYears;
    _conditions.timeseries = DomainFilter::dfNone;
    _storage.set(_conditions);
}

stats::TimeSeries Perfomance::getPerfomance(const ids_t &ids)
{
    auto items = _storage.getItems(ids, true);
    stats::PerfomanceSampleBuilder builder;

    for (auto &item: items)
    {
        builder.add(atoi(item.id.c_str()), item.success, item.all);
    }

    std::map<int, stats::PerfomanceSample> samples = builder.build();

    stats::TimeSeries res;
    for (const auto &sample : samples)
    {
        if (sample.first == 0)
            continue;
        res.add(sample.first, sample.second.getPerfomance());
    }

    return res;
}

template<typename T>
static T *transform(std::vector<T> &v)
{
    int size = v.size();
    T *result = new T[size];
    std::copy(v.begin(), v.end(), result);
    return result;
}

class DataEqualizer
{
public:
    DataEqualizer() = default;
    ~DataEqualizer() = default;

    void add(const std::string &name, const stats::TimeSeries &data);

    std::map<std::string, stats::TimeSeries> getData(){ return _output; }
    std::map<std::string, stats::Sample> getSamples();
protected:
    bool _firstAdding = true;

    std::vector<int> _columns;
    std::map<std::string, stats::TimeSeries> _input;
    std::map<std::string, stats::TimeSeries> _output;
    std::map<std::string, stats::Sample> _samples;
};

void DataEqualizer::add(const std::string &name, const stats::TimeSeries &series)
{
    auto moments = series.getMoments();
    if (_firstAdding)
    {
        _firstAdding = false;
        _columns = moments;
    }
    else
    {
        std::vector<int> tmp;
        tmp = moments;
        std::vector<int> res(std::min(tmp.size(), _columns.size()));
        auto it = std::set_intersection(_columns.begin(),_columns.end(), tmp.begin(), tmp.end(), res.begin());
        res.resize(it - res.begin());
        _columns.clear();
        _columns = res;
    }

    _input[name] = series;
}

std::map<std::string, stats::Sample> DataEqualizer::getSamples()
{
    for (auto &category : _input)
    {
        for (auto &point: category.second)
        {
            if (std::find(_columns.begin(), _columns.end(), point.x) == _columns.end())
                continue;
            _samples[category.first].add(point.y);
            _output[category.first].add(point);
        }
        _samples[category.first].refresh();
    }

    return _samples;
}

Perfomance::CorrelationInfo Perfomance::correlation(const ids_t &ids)
{
    DataEqualizer eq;
    for (const auto &id: ids)
    {
        ids_t newids{id};
        stats::TimeSeries series = getPerfomance(newids);
        eq.add(id, series);
    }

    stats::MeanCorrelation c;
    CorrelationInfo info;
    info._mtx = c.getRegressionMatrix(eq.getSamples());
    info._points = eq.getData();

    return info;
}

Perfomance::Trends Perfomance::trends(const ids_t &ids)
{
    Trends res;
    DataEqualizer eq;
    for (const auto &id: ids)
    {
        ids_t newids{id};
        stats::TimeSeries series = getPerfomance(newids);
        eq.add(id, series);
    }
    eq.getSamples();
    auto data = eq.getData();
    stats::Point<> p0, p1;

    for (auto &category: data)
    {
        std::vector<stats::Point<>> points;

        for (auto &point: category.second)
            points.push_back(stats::Point<>(point.x, point.y));

        stats::WOLS ols(points);
        ols.apply();

        p0 = ols.getStartPoint();
        p1 = ols.getEndPoint();
        res.y[category.first][0] = p0.y;
        res.y[category.first][1] = p1.y;
    }

    res.x0 = p0.x;
    res.x1 = p1.x;

    return res;
}

stats::TimeSeries Perfomance::getPerfomanceFromStore(const ids_t &ids)
{
//    bool bCompare = _lastIds == ids;
//    if (bCompare)
//    {
//        for (int i = 0; i < _lastIds.size(); i++)
//        {
//            if (_lastIds[i] != ids[i])
//            {
//                bCompare = false;
//                break;
//            }
//        }
//    }

//    if (!bCompare)
//    {
//        _lastPerfomance = getPerfomance(ids);
//        _lastIds = ids;
//    }

//    return _lastPerfomance;
    return getPerfomance(ids);
}

double Perfomance::correlation2(const ids_t &ids)
{
    stats::TimeSeries series = getPerfomanceFromStore(ids);
    stats::Sample s1;
    stats::Sample s2;
    for (auto &point: series)
    {
        s1.add(point.x);
        s2.add(point.y);
    }
    s1.refresh();s2.refresh();
    stats::TwoFactorCorrelation c(s1, s2);
    return c.getRegression();
}

double Perfomance::autocorrelation(const ids_t &ids)
{
    stats::TimeSeries series = getPerfomanceFromStore(ids);
    stats::Sample s1;
    stats::Sample s2;
    for (auto it = series.begin(); std::next(it, 1) != series.end(); it++)
    {
        s1.add(it->y);
        auto it2 = std::next(it, 1);
        s2.add(it2->y);
    }
    s1.refresh();
    s2.refresh();
    stats::TwoFactorCorrelation c(s1, s2);
    return c.getRegression();
}

std::string Perfomance::FTest2(const ids_t &ids)
{
    DataEqualizer eq;
    for (const std::string &id: ids)
    {
        ids_t newids{id};
        stats::TimeSeries series = getPerfomance(newids);
        eq.add(id, series);
    }
    std::vector<stats::Sample> samples;

    for (auto &sample: eq.getSamples())
    {
        samples.push_back(sample.second);
    }

    stats::TwoFactorAnova anova;
    anova.FTest(samples);

    stats::Analyser anylyser;
    anylyser.addAnova2(anova);

    return anylyser.getConclusion();
}

//--------------------------------------------------------
#include "analyser.h"
#include <MathStats/anova.h>

idNameMap_t Perfomance::getItems()
{
    auto items = _storage.getIDs();
    idNameMap_t res;
    for (auto item: items)
    {
        res[item.id] = item.name;
    }
    return res;
}

idNameMap_t Perfomance::getSpecialties(const std::string &facName) const
{
    idNameMap_t res;
    for (auto &item: _storage.getIDsByID(DomainFilter::dfFaculties, facName))
    {
        res[item.id] = item.name;
    }
    return res;
}

std::vector<int> Perfomance::getGroupClasses()
{
    return _storage.getKlasses();
}

stats::Range Perfomance::getRange(const ids_t &ids) const
{
    auto items = _storage.getItems(ids);
    stats::Sample s;
    for (const Storage::Item &item: items)
    {
        s.add(double(item.success) / double(item.all) * 100);
    }

    return s.buildRange();
}

Perfomance::Statistics Perfomance::getStatistics(const ids_t &ids) const
{
    auto items = _storage.getItems(ids);
    idValueMap_t idValues;
    for (auto item: items)
    {
        IdValStruct idvalue;
        idvalue.id = item.id;
        idvalue.value = double(item.success) / double(item.all) * 100;
        idValues.push_back(idvalue);
    }
    auto sample = getCommonSampleInternal(idValues);
    stats::Anova anova;
    double FTest = 0;
    if (ids.size() != 1)
        FTest = anova.FTest(getSamplesById(idValues));

    stats::Analyser anylyser;
    anylyser.addSample(sample);
    anylyser.addAnova(anova);

    return Statistics{anylyser.getConclusion(), sample};
}

std::vector<stats::Sample> Perfomance::getSamplesById(const idValueMap_t &items) const
{
    std::map<std::string, stats::Sample> sampleMap;

    for (const auto &item: items)
    {
        sampleMap[item.id].add(item.value);
    }

    std::vector<stats::Sample> res;
    for (auto &item: sampleMap)
    {
        item.second.refresh();
        res.push_back(item.second);
    }
    return res;
}

stats::Sample Perfomance::getCommonSampleInternal(const idValueMap_t &items) const
{
    stats::Sample sample;
    for (const auto &item: items)
    {
        sample.add(item.value);
    }
    sample.refresh();
    return sample;
}
