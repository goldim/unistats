/*
 * Accumulator.h
 *
 *  Created on: 10.01.2017
 *      Author: goldim
 */

#pragma once

//local
#include "range.h"

//boost
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

namespace stats
{

using values_t = std::vector<double>;

class SampleBase
{
public:
    SampleBase() = default;

    inline values_t getElements() const { return _elements; }
    inline long long getCount() const { return _n; }
    inline void setName(const std::string &name) { _name = name; }
    inline std::string getName() { return _name; }
protected:
    values_t _elements;
    long long _n = 0;
    std::string _name;
};

class Sample : public SampleBase
{
public:
    Sample() = default;
    Sample(const std::initializer_list<double> &elements);

    void add(double value);
    Range buildRange();
    void refresh();
    Sample sqr();

    inline double getMean() const { return _mean; }
    inline double getVariance() const { return _variance; }
    inline double getKurtosis() const { return _kurtosis; }
    inline double getSkewness() const { return _skewness; }
    inline double getVariation() const { return _variation; }
    inline double getDeviation() const { return _deviation; }

    Sample operator+(const Sample &sample);
    Sample operator*(const Sample &sample);
private:
    double _mean = 0.0;
    double _variance = 0.0;
    double _deviation = 0.0;
    double _kurtosis = 0.0;
    double _skewness = 0.0;
    double _variation = 0.0;

    boost::accumulators::accumulator_set<double, boost::accumulators::features<
            boost::accumulators::tag::count,
            boost::accumulators::tag::mean,//среднее арифметическое
            boost::accumulators::tag::variance,//дисперсия
            boost::accumulators::tag::kurtosis,//экцесс
            boost::accumulators::tag::skewness>>//ассиметрия
            _acc;
};

class PerfomanceSample : public SampleBase
{
public:
    PerfomanceSample() = default;

    void add(double successful, double all);

    inline double getPerfomance() const { return _perfomance; }
private:
    double _perfomance = 0.0;
    double _successful = 0.0;
    double _all = 0.0;

    values_t _successfulElements;
    values_t _allElements;
};

using Samples = std::vector<Sample>;

}
