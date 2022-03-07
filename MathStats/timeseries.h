#pragma once

#include <vector>
#include "point.h"

namespace stats
{

class TimeSeries: public std::iterator<std::input_iterator_tag, int>
{
public:
    using Points = std::vector<Point<int>>;

    TimeSeries() = default;

    std::vector<int> getMoments() const;
    std::vector<int> getValues() const;
    inline Points getPoints() const { return _points; }

    void add(Point<int> p);
    void add(int moment, double value);

    bool isExist(int moment) const;

/*-----------------Iterator Part----------------------*/
    int size() const { return _points.size(); }

    Points::iterator begin()
    {
        return _points.begin();
    }

    Points::iterator end()
    {
        return _points.end();
    }

    Points::const_iterator begin() const
    {
        return _points.begin();
    }

    Points::const_iterator end() const
    {
        return _points.end();
    }

private:
    Points _points;
};

}
