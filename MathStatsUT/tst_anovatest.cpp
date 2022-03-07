#include <QString>
#include <QtTest>

// system under test
#include <MathStats/anova.h>
#include <MathStats/correlation.h>

#include <iostream>
#include <cmath>

class AnovaTest : public QObject
{
    Q_OBJECT

public:
    AnovaTest() = default;

private Q_SLOTS:
    void oneFactor();
    void twoFactor();
};

using stats::Sample;

void AnovaTest::oneFactor()
{
    Sample s1{54,58,57};
    Sample s2{58,62,64};
    Sample s3{64,62,63};
    std::vector<Sample> samples{s1,s2,s3};

    stats::Anova anova;
    anova.FTest(samples);

    double expected = 7.39;
    QVERIFY(round(anova.getFTestRes() * 100) / 100 == expected);
}

void AnovaTest::twoFactor()
{
    Sample s1{30,31,35};
    Sample s2{31,33,36};
    Sample s3{29,34,38};
    std::vector<Sample> samples{s1,s2,s3};

    stats::TwoFactorAnova anova;
    anova.FTest(samples);

    double expectedA = 18.2;
    double expectedB = 1.4;
    QVERIFY2(round(anova.getFTestRes().FA * 10) / 10 == expectedA, "Fa - failed");
    QVERIFY2(round(anova.getFTestRes().FB * 10) / 10 == expectedB, "Fb - failed");
}

class CorrelationTest : public QObject
{
    Q_OBJECT

public:
    CorrelationTest() = default;
private Q_SLOTS:
    void twoFactor();
};

void CorrelationTest::twoFactor()
{
    Sample s1{5,4,3,15,8,12};
    Sample s2{8,9,12,2,5,4};

    stats::TwoFactorCorrelation c(s1,s2);
    double r = c.getRegression();

    double expected = -0.948;
    QVERIFY(round(r * 1000) / 1000 == expected);
}

int main(int argc, char *argv[])
{
    int status = 0;
    {
        AnovaTest tc;
        status |= QTest::qExec(&tc, argc, argv);
    }
    {
        CorrelationTest tc;
        status |= QTest::qExec(&tc, argc, argv);
    }
    return status;
}

#include "tst_anovatest.moc"
