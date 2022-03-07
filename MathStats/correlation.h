#pragma once

#include <map>
#include <limits>

#include "sample.h"
#include "timeseries.h"

namespace stats
{

class TwoFactorCorrelation
{
public:
    TwoFactorCorrelation(const Sample &x, const Sample &y);

    double getRegression();
private:
    Sample _x;
    Sample _y;
};

class MeanCorrelation
{
public:
    using Matrix = std::map<std::string, std::map<std::string, double>>;

    MeanCorrelation() = default;
    Matrix getRegressionMatrix(const std::map<std::string, Sample> &samplesMap);
private:
    int _min = 0;
    int _max = std::numeric_limits<int>::max();
    Matrix _result;
};

}// stats
