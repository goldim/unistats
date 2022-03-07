#pragma once

// STL
#include <map>
#include <string>
#include <vector>
#include <memory>

#include "defs.h"
#include <MathStats/correlation.h>
#include <StorageStats/Config.h>
#include <StorageStats/storage.h>

class Perfomance
{
public:
    struct CorrelationInfo
    {
        std::map<std::string, stats::TimeSeries> _points;
        stats::MeanCorrelation::Matrix _mtx;
    };

    struct Trends
    {
        std::map<std::string, std::array<double, 2>> y;
        int x0;
        int x1;
    };

    Perfomance() = default;
    Perfomance(const Config &cfg);

    inline void setX(DomainFilter timeseries){
        _conditions.timeseries = timeseries;
        _storage.set(_conditions);
    }
    inline void setY(DomainFilter category){
        _conditions.category = category;
        _storage.set(_conditions);
    }
    inline void setGroupClass(int klass){
        _conditions.klass = klass;
        _storage.set(_conditions);
    }

    inline void setExam(int order){
        _conditions.exam = order;
        _storage.set(_conditions);
    }

    //general
    idNameMap_t getItems();
    std::vector<int> getGroupClasses();

    //statistics
    struct Statistics
    {
        std::string conclusion;
        stats::Sample sample;
    };

    stats::Range getRange(const ids_t &ids) const;
    Statistics getStatistics(const ids_t &ids) const;
    idNameMap_t getSpecialties(const std::string &facName) const;

    //time series
    stats::TimeSeries getPerfomance(const ids_t &ids);
    stats::TimeSeries getPerfomanceFromStore(const ids_t &ids);
    Trends trends(const ids_t &ids);
    CorrelationInfo correlation(const ids_t &ids);
    double correlation2(const ids_t &ids);
    double autocorrelation(const ids_t &ids);
    std::string FTest2(const ids_t &ids);
private:
    stats::Sample getCommonSampleInternal(const idValueMap_t &values) const;
    std::vector<stats::Sample> getSamplesById(const idValueMap_t &values) const;
private:
    Conditions _conditions;
    Storage _storage;
};
