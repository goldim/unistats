#pragma once

#include <map>
#include "sample.h"

namespace stats
{

class Anova
{
public:
    inline int getV1() const { return _v1; }
    inline int getV2() const { return _v2; }
    inline double getFTestRes() const { return _F; }

    double FTest(const Samples &samples);
    double FCriticalTest(double alpha) const;
private:
    int _v1 = 0;
    int _v2 = 0;
    double _F;
};

class TwoFactorAnova
{
public:
    struct Result
    {
        double FA;
        double FB;
        double FAB;
    };

    inline int getVA() const { return _Va; }
    inline int getVB() const { return _Vb; }
    inline int getV2() const { return _V2; }

    double FCriticalTestA(double alpha) const;
    double FCriticalTestB(double alpha) const;
    double FCriticalTestAB(double alpha) const;

    inline Result getFTestRes() const { return _F; }

    Result FTest(const Samples &samples);
protected:
    double FcriticalTest(double alpha, int v1, int v2) const;
private:
    int _Va = 0;
    int _Vb = 0;
    int _V2 = 0;
    Result _F;
};

}
