/*
 * RangeBuilder.h
 *
 *  Created on: 08.01.2017
 *      Author: goldim
 */

#pragma once

#include <vector>

namespace stats
{

struct Range
{
    struct Interval
    {
        double left;
        double right;
        long n = 0;
    };

    double min = 0.0;
    double max = 0.0;
    double h = 0;
    long n = 0;
	std::vector<Interval> _Intervals;
};

}// stats
