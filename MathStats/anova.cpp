#include "anova.h"

// STL
#include <vector>
#include <algorithm>

// debug
#include <iostream>
#include <iomanip>

#include <boost/math/distributions/fisher_f.hpp>

template<typename T>
static T *transform(std::vector<T> &v)
{
    int size = v.size();
    T *result = new T[size];
    std::copy(v.begin(), v.end(), result);
    return result;
}

namespace stats
{

class MeanEnumer
{
public:
    MeanEnumer() = default;

    void operator()(const Sample &s)
    {
        _n += s.getCount();
        for (auto &el: s.getElements())
            _sum += el;
    }

    inline double getMean(){ return _sum / _n; }
    inline int getN(){ return _n; }
private:
    int _n = 0;
    double _sum = 0;
};

double Anova::FTest(const Samples &samples)
{
    assert(samples.size() > 1);
    if (samples.size()  <= 1)
        throw std::domain_error("count of samples must be more than 1");

    MeanEnumer enumer = std::for_each(samples.begin(), samples.end(), MeanEnumer());
    double generalMean = enumer.getMean();
    int N = enumer.getN();

    double Qa = 0;

    std::for_each(samples.begin(), samples.end(), [&Qa, &generalMean](const Sample &s){
        Qa += s.getCount() * pow(s.getMean() - generalMean, 2);
    });

    double Qoct = 0;
    std::for_each(samples.begin(), samples.end(), [&Qoct](const Sample &s){
        for (auto &el: s.getElements())
            Qoct += pow(el - s.getMean(), 2);
    });

    int sampleSize = samples.size();
    _v1 = sampleSize - 1;
    _v2 = N - sampleSize;
    _F = (Qa / _v1) / (Qoct / _v2);
    return _F;
}

double Anova::FCriticalTest(double alpha) const
{
    using namespace boost::math;
    fisher_f dist(_v1, _v2);
    return quantile(complement(dist, alpha));
}

//---------Two factor ANOVA---------------------------------------
TwoFactorAnova::Result TwoFactorAnova::FTest(const Samples &rowSamples)
{
    int m = rowSamples.size();
    assert(m != 0);
    if (m  == 0)
        throw std::domain_error("count of samples must be more than 1");

    int r = rowSamples[0].getCount();
    Samples columnSamples(r);
    Sample commonSample;
    for (int i = 0; i < m; i++)
    {
        const Sample &rowSample = rowSamples[i];
        int j = 0;
        for (auto &el: rowSample.getElements())
        {
            columnSamples[j].add(el);
            commonSample.add(el);
            j++;
        }
    }

    commonSample.refresh();
    for (auto &sample: columnSamples)
    {
        sample.refresh();
    }

    double Qa = 0.0, Qb = 0.0, Qoct = 0.0;

    for (const Sample &sample: columnSamples)
    {
        Qa += r*pow(sample.getMean() - commonSample.getMean(), 2);
    }

    double Da = Qa / (m - 1);

    for (const Sample &sample: rowSamples)
    {
        Qb += m*pow(sample.getMean() - commonSample.getMean(), 2);
    }

    double Db = Qb / (r - 1);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < r; j++)
        {
            Qoct += pow((rowSamples[i].getElements())[j]
                        + commonSample.getMean() - (rowSamples[i].getMean() + columnSamples[j].getMean()), 2);
        }
    }
    double Doct = Qoct / ((m - 1)*(r - 1));

    _Va = m - 1;
    _Vb = r - 1;
    _V2 = (m - 1) * (r - 1);

    Result res;
    res.FA = _F.FA =  Da / Doct;
    res.FB = _F.FB =  Db / Doct;
    res.FAB = _F.FAB = std::max(res.FA, res.FB) / std::min(res.FA, res.FB);

    return res;
}

double TwoFactorAnova::FcriticalTest(double alpha, int v1, int v2) const
{
    using namespace boost::math;
    fisher_f dist(v1, v2);
    return quantile(complement(dist, alpha));
}

double TwoFactorAnova::FCriticalTestA(double alpha) const
{
    return FcriticalTest(alpha, _Va, _V2);
}

double TwoFactorAnova::FCriticalTestB(double alpha) const
{
    return FcriticalTest(alpha, _Vb, _V2);
}

double TwoFactorAnova::FCriticalTestAB(double alpha) const
{
    return FcriticalTest(alpha, _V2, _V2);
}

}// stats
