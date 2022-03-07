#pragma once

#include <map>

#include "sample.h"

namespace stats
{

class PerfomanceSampleBuilder
{
public:
    PerfomanceSampleBuilder() = default;
    void add(int name, unsigned m, unsigned n);
    std::map<int, PerfomanceSample> build();
private:
    std::map<int, PerfomanceSample> _samples;
};

}// stats


