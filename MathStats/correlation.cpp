#include "correlation.h"

#include <iostream>

namespace stats
{

TwoFactorCorrelation::TwoFactorCorrelation(const Sample &x, const Sample &y):
    _x(x),
    _y(y)
{
    assert(_x.getCount() == _y.getCount());
}

double TwoFactorCorrelation::getRegression()
{
    Sample x2 = _x.sqr();
    Sample y2 = _y.sqr();
    Sample xy = _x * _y;

    double meanX2 = x2.getMean();
    double meanY2 = y2.getMean();
    double meanXY = xy.getMean();

    double Sx = sqrt(meanX2 - pow(_x.getMean(), 2));
    double Sy = sqrt(meanY2 - pow(_y.getMean(), 2));

    return (meanXY - _x.getMean() * _y.getMean()) / (Sx * Sy);
}

MeanCorrelation::Matrix MeanCorrelation::getRegressionMatrix(const std::map<std::string, Sample> &samplesMap)
{
    int xLen = samplesMap.size();
    std::map<int, std::string> x;
    Samples samples;

    int i = 0;
    for (auto &category: samplesMap)
    {
        x[i] = category.first;
        samples.push_back(category.second);
        i++;
    }

    Matrix res;

    for (i = 0; i < xLen; i++)
    {
        for (int j = 0; j < xLen; j++)
        {
            TwoFactorCorrelation c(samples[i], samples[j]);
            res[x[i]][x[j]] = c.getRegression();
//            std::cout << std::fixed << x[i] << " " << x[j] << " " << res[x[i]][x[j]] << std::endl;
        }
    }

    return res;
}

}// stats
