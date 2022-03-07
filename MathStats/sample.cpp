/*
 * Accumulator.cpp
 *
 *  Created on: 10.01.2017
 *      Author: goldim
 */

#include "sample.h"

//C library
#include <cassert>
#include <cmath>
//STL
#include <algorithm>

namespace stats
{

using namespace boost::accumulators;

//-------------------------------------------------------------------------
Sample::Sample(const std::initializer_list<double> &elements)
{
    for (auto el: elements)
        add(el);
    refresh();
}


void Sample::add(double value)
{
    _acc(value);
    _elements.push_back(value);
}

void Sample::refresh()
{
    _n = count(_acc);
    _mean = mean(_acc);
    _variance = variance(_acc);
    _deviation = sqrt(_variance);
    _skewness = skewness(_acc);
    _kurtosis = kurtosis(_acc);

    try
    {
        if (_mean == 0) throw 1;
        _variation = (_deviation / _mean) * 100;
    }
    catch(...){}
}

Sample Sample::operator+(const Sample &sample)
{
    assert(_elements.size() == sample.getElements().size());

    Sample res;
    auto anotherElements = sample.getElements();

    for (decltype(_elements.size()) i = 0; i < _elements.size(); i++)
        res.add(_elements[i]+anotherElements[i]);

    res.refresh();
    return res;
}

Sample Sample::operator*(const Sample &sample)
{
    assert(_elements.size() == sample.getElements().size());

    Sample res;
    auto anotherElements = sample.getElements();

    for (decltype(_elements.size()) i = 0; i < _elements.size(); i++)
        res.add(_elements[i]*anotherElements[i]);

    res.refresh();
    return res;
}

Sample Sample::sqr()
{
    Sample res;

    for (decltype(_elements.size()) i = 0; i < _elements.size(); i++)
        res.add(_elements[i] * _elements[i]);

    res.refresh();
    return res;
}

Range Sample::buildRange()
{
    Range range;
    if (_elements.size() == 0)
        return range;

    std::sort(_elements.begin(), _elements.end());
    range.min = _elements.front();
    range.max = _elements.back();
    range.n = _elements.size();
    range.h = (range.max - range.min)/(1 + 3.32 * log(range.n));

    double current = range.min;
    auto it = _elements.begin();

    do
    {
        Range::Interval interval;
        interval.left = current;
        interval.right = current + range.h;

        for (;;)
        {
            if (it == _elements.end() || *it > interval.right)
                break;

            interval.n++;
            it++;
        }
        range._Intervals.push_back(interval);
        current = interval.right;
    }
    while (current < range.max);

    return range;
}

//------------------------------------------------------------------------------

void PerfomanceSample::add(double successful, double all)
{
    assert(all != 0.0);

    _successfulElements.push_back(successful);
    _allElements.push_back(all);    
    _successful += successful;
    _all += all;
    _n++;
    _perfomance = _successful / _all;
    _elements.push_back(successful / all);
}

}// stats
