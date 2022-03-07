#include "controller.h"

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>

static ids_t convert(QVariantList l)
{
    ids_t res;
    for (const auto &item : l)
    {
        res.push_back(item.toString().toStdString());
    }

    return res;
}

controller::controller(const Config &cfg, QObject *parent):
    QObject(parent),
    _perf(cfg)
{
}

QVariantMap controller::loadItems()
{
    auto res = _perf.getItems();

    QVariantMap m;
    for (const auto &el : res){
        m.insert(QString::fromStdString(el.first), QString::fromStdString(el.second));
    }
    return m;
}

void controller::setOrder(int order)
{
    _perf.setExam(order);
}

std::map<QString, DomainFilter> controller::_domains = {
    {"all", DomainFilter::dfNone},
    {"Faculty", DomainFilter::dfFaculties},
    {"Specialty", DomainFilter::dfSpecialties},
    {"Specialization", DomainFilter::dfSpecializations},
    {"YearStart", DomainFilter::dfStartYears},
    {"Subject", DomainFilter::dfSubjects},
    {"Teacher", DomainFilter::dfTeachers},
    {"Term", DomainFilter::dfTerms},
    {"Group", DomainFilter::dfGroups},
    {"Year", DomainFilter::dfYears},
    {"Kurs", DomainFilter::dfKurs},
    {"ExamOrder", DomainFilter::dfExamOrder}
};

void controller::setCriterion(QString criterion)
{    
    _perf.setX(_domains[criterion]);
}

void controller::setDomain(QString domain)
{
    _perf.setY(_domains[domain]);
}

void controller::setGroupClass(QString klass)
{
    _perf.setGroupClass(klass.toInt());
}

QVariantMap controller::loadSpecialties(QString facName)
{
    auto res = _perf.getSpecialties(facName.toStdString());
    QVariantMap m;
    for (const auto &el : res){
        m.insert(QString::fromStdString(el.first), QString::fromStdString(el.second));
    }
    return m;
}

QVariantMap controller::getRangeChart(QVariantList chosenItems)
{
    QVariantMap m;
    ids_t chosenItemsStdVec = convert(chosenItems);
    stats::Range range = _perf.getRange(chosenItemsStdVec);

    QVariantList categories;
    QVariantList values;

    for (auto &interval : range._Intervals)
    {
        QString title = QString::number(trunc(interval.right));
        categories.append(title);
        values.append(QString::number(interval.n));
    }

    m["categories"] = categories;
    m["values"] = values;
    return m;
}

QVariantMap controller::getTimeChart(QVariantList chosenItems)
{
    QVariantMap m;
    ids_t chosenItemsStdVec = convert(chosenItems);
    stats::TimeSeries series = _perf.getPerfomance(chosenItemsStdVec);

    QVariantList categories;
    QVariantList values;

    for (auto &point: series.getPoints())
    {
        categories.append(point.x);
        values.append(QString::number(point.y));
    }

    m["categories"] = categories;
    m["values"] = values;
    return m;
}

double myTrunc(double val)
{
    return trunc(100 * val) / 100;
}

QVariantMap controller::getStats(QVariantList chosenItems)
{
    QVariantMap res;
    auto chosenItemsVec = convert(chosenItems);
    auto statistics = _perf.getStatistics(chosenItemsVec);

    stats::Sample sample = statistics.sample;
    res["kurtosis"] = myTrunc(sample.getKurtosis());
    res["mean"] = myTrunc(sample.getMean());
    res["n"] = sample.getCount();
    res["skewness"] = myTrunc(sample.getSkewness());
    res["variance"] = myTrunc(sample.getVariance());
    res["varFactor"] = myTrunc(sample.getVariation());
    res["conclusion"] = QString::fromStdString(statistics.conclusion);
    res["regression"] = myTrunc(_perf.correlation2(chosenItemsVec));
    res["autocorrelation"] = myTrunc(_perf.autocorrelation(chosenItemsVec));

    return res;
}

void controller::save(QString text)
{
    std::fstream fs("output.txt", std::fstream::out);
    fs << text.toStdString();
    fs.close();
}

QVariantMap controller::correlation(QVariantList chosenItems)
{
    Perfomance::CorrelationInfo info = _perf.correlation(convert(chosenItems));

    QVariantMap chartdata;
    for (const auto &category : info._points){
        QVariantMap m;

        QVariantList categoryNames;
        QVariantList values;

        for (auto &point: category.second)
        {
            categoryNames.append(point.x);
            values.append(QString::number(point.y));
        }

        m["categories"] = categoryNames;
        m["values"] = values;

        chartdata.insert(QString::fromStdString(category.first), m);
    }

//---------------------------------------------------------------------
    QVariantMap tabledata;
    QVariantList roles;
    QVariantMap dynamicData;
    QVariantList clms[info._mtx.size()];

    for (auto &row: info._mtx)
    {
        int j = 0;
        for (auto &el: row.second)
        {
            clms[j].append(QString::number(round(100 * el.second) / 100));
            j++;
        }
    }

    int i = 0;
    for (const auto &el: info._mtx){
        auto role = QString::fromStdString(el.first);
        roles.append(role);
        dynamicData[role] = clms[i];
        i++;
    }

    tabledata["roles"] = roles;
    tabledata["factors"] = dynamicData;

    QVariantMap res;
    res["chartdata"] = chartdata;
    res["tabledata"] = tabledata;
    return res;
}

QString controller::getAnova2(QVariantList chosenItems)
{
    return QString::fromStdString(_perf.FTest2(convert(chosenItems)));
}

QVariantMap controller::trends(QVariantList chosenItems)
{
    QVariantMap res;
    auto trends = _perf.trends(convert(chosenItems));

    for (auto &trend: trends.y)
    {
        QVariantList points;
        points.append(QPointF(trends.x0, trend.second[0]));
        points.append(QPointF(trends.x1, trend.second[1]));
        res[QString::fromStdString(trend.first)] = points;
    }

    return res;
}

QVariantList controller::getGroupClasses()
{
    QVariantList res;
    for (auto &klass: _perf.getGroupClasses())
        res.append(klass);
    return res;
}
