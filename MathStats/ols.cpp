#include "ols.h"

// STL
#include <algorithm>
// GSL
#include <gsl/gsl_fit.h>


namespace stats
{

OLS::OLS(const std::vector<Point<>> &points):
    _N(points.size())
{
    for (int i = 0; i < _N; i++)
    {
        _xVec.push_back(points[i].x);
        _yVec.push_back(points[i].y);
    }
}

void OLS::apply()
{
    double cov00, cov01, cov11, chisq;
    double *xArr = &_xVec[0];
    double *yArr = &_yVec[0];
    gsl_fit_linear(xArr, 1, yArr, 1, _N,
                    &_C, &_B, &cov00, &cov01, &cov11,
                    &chisq);
}

Point<> OLS::getStartPoint() const
{
    auto x = _xVec.at(0);
    return Point<>(x, _B * x + _C);
}

Point<> OLS::getEndPoint() const
{
    auto x = _xVec.at(_xVec.size()-1);
    return Point<>(x, _B * x + _C);
}

void WOLS::apply()
{
    double cov00, cov01, cov11, chisq;
    double *xArr = &_xVec[0];
    double *yArr = &_yVec[0];

    double wArr[_N];
    double b1 = 1;
    double q = 0.9;
    for (int i = 0; i < _N; i++)
    {
        wArr[i] = b1 * pow(q, i);
    }
    std::reverse(&wArr[0], &wArr[_N-1]);

    gsl_fit_wlinear(xArr, 1, wArr, 1, yArr, 1, _N,
                    &_C, &_B, &cov00, &cov01, &cov11,
                    &chisq);
}

}
