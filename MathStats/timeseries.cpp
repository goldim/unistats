#include "timeseries.h"

#include <algorithm>

namespace stats
{

void TimeSeries::add(Point<int> p)
{
    _points.push_back(p);
}

void TimeSeries::add(int moment, double value)
{
    _points.push_back(Point<int>(moment, value));
}

std::vector<int> TimeSeries::getMoments() const
{
    std::vector<int> res;
    for (auto point: _points)
        res.push_back(point.x);
    return res;
}

std::vector<int> TimeSeries::getValues() const
{
    std::vector<int> res;
    for (auto point: _points)
        res.push_back(point.y);
    return res;
}

bool TimeSeries::isExist(int moment) const
{
    return _points.end() != std::find_if(_points.begin(), _points.end(), [&moment](const Point<int> &p){
        return p.x == moment;
    });
}

}
