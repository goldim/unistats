#pragma once

#include <vector>
#include <memory>

#include "point.h"

namespace stats {

class OLS
{
public:
    OLS(const std::vector<Point<>> &points);

    inline double getB() const { return _B; }
    inline double getC() const { return _C; }
    Point<> getStartPoint() const;
    Point<> getEndPoint() const;

    void apply();
protected:
    int _N;

    std::vector<double> _xVec;
    std::vector<double> _yVec;

    double _B;
    double _C;
};

class WOLS: public OLS
{
public:
    WOLS(const std::vector<Point<>> &points):OLS(points){}

    void apply();
};

}
