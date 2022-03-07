#include "sample_builder.h"

#include <algorithm>

namespace stats
{

void PerfomanceSampleBuilder::add(int name, unsigned m, unsigned n)
{
    _samples[name].add(m, n);
}

std::map<int, PerfomanceSample> PerfomanceSampleBuilder::build()
{
    return _samples;
}

}// stats
