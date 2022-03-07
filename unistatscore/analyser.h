#pragma once

#include <string>
#include <sstream>

#include <MathStats/sample.h>
#include <MathStats/anova.h>

namespace stats
{

class Analyser
{
public:
    Analyser();

    void addSample(const Sample &params);
    void addAnova(Anova &anova);
    void addAnova2(TwoFactorAnova &anova);

    std::string getConclusion() { return _output.str(); }
private:
    std::stringstream _output;
};

}// stats

