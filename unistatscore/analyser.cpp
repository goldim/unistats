#include "analyser.h"

#include <array>

namespace stats {

using std::string;

Analyser::Analyser()
{

}

void Analyser::addSample(const Sample &sample)
{
    string sampleStr = "Выборка: ";
    string homogeneity;
    if (sample.getVariation() < 17)
    {
        homogeneity = "абсолютно однородная";
    }
    else if (sample.getVariation() >= 17 && sample.getVariation() < 35)
    {
        homogeneity = "достаточно однородная";
    }
    else if (sample.getVariation() >= 35 && sample.getVariation() < 45)
    {
        homogeneity = "недостаточно однородная";
    }
    else
    {
        homogeneity = "неоднородная";
    }

    sampleStr += homogeneity;

    string skewnessStr = "ассиметрия ";

    if (sample.getSkewness() > 0)
    {
        skewnessStr += "правосторонняя";
    }
    else
    {
        skewnessStr += "левосторонняя";
    }

    string kurtosisStr = "мера крутости: ";

    if (sample.getKurtosis() > 0)
    {
        kurtosisStr += "островершинность";
    }
    else
    {
        kurtosisStr += "плосковершинность";
    }

    string res = sampleStr + ", " + skewnessStr + ", " + kurtosisStr;
    _output << res + "<br/>";
}


static double myTrunc(double val)
{
    return trunc(1000 * val) / 1000;
}

void Analyser::addAnova(Anova &anova)
{
    auto v1 = anova.getV1();
    auto v2 = anova.getV2();
    if (v1 == 0 || v2 == 0)
    {
        _output << "Для дисперсионного анализа степени свободы должны быть больше 0. "
                   "Вероятно выбран 1 элемент";
        return;
    }

    std::vector<std::string> headers{
        "Крит. значимости",
        "F-набл",
        "F-крит",
        "H0",
        "Влияние"
    };

    _output << "<b>Заключение дисперсионного анализа:</b>";
    _output << "<table><tr>";
    for (const auto &header: headers)
        _output << "<td><b>" << header<< "</b></td>";
    _output << "</tr>";

    std::array<double, 3> a = {0.05, 0.01, 0.001};

    for (auto &el : a)
    {
        double Fcrit = anova.FCriticalTest(el);
        double Fq = anova.getFTestRes();

        _output << "<tr>"
                << "<td>" << el << "</td>"
                << "<td>" << myTrunc(Fq) << "</td>"
                << "<td>" << myTrunc(Fcrit) << "</td>"
                << "<td>" << (Fq > Fcrit?"отверг.":"не отверг.") << "</td>"
                << "<td>" << (Fq > Fcrit?"<font color=green>да</font>":"<font color=red>нет</font>") << "</td>"
                << "</tr>";
    }
    _output << "</table>";
}
void Analyser::addAnova2(TwoFactorAnova &anova)
{
    auto Va = anova.getVA();
    auto Vb = anova.getVB();
    auto v2 = anova.getV2();
    if (Va == 0 || Vb == 0 || v2 == 0)
    {
        _output << "Для дисперсионного анализа степени свободы должны быть больше 0."
                   "Выбран 1 элемент.";
        return;
    }

    std::vector<std::string> headers{
        "Фактор",
        "Крит. значимости",
        "F-набл",
        "F-крит",
        "H0",
        "Влияние"
    };

    _output << "<b>Заключение дисперсионного анализа по двум факторам:</b>";
    _output << "<table><tr>";
    for (const auto &header: headers)
        _output << "<td><b>" << header<< "</b></td>";
    _output << "</tr>";

    std::array<double, 3> a = {0.05, 0.01, 0.001};
    std::array<double, 2> vArr = {Va, Vb};
    std::array<double, 2> FArr = {anova.getFTestRes().FA, anova.getFTestRes().FB};
    std::array<std::string, 2> factorNameArr = {"A", "B"};

    for (auto &el : a)
    {
        double FcritA = anova.FCriticalTestA(el);
        double FcritB = anova.FCriticalTestB(el);
        std::array<double, 2> FcritArr = {FcritA, FcritB};

        for (int i = 0; i < 2; i++)
        {
            _output << "<tr>"
                    << "<td>" << factorNameArr[i] << "</td>"
                    << "<td>" << el << "</td>"
                    << "<td>" << myTrunc(FArr[i]) << "</td>"
                    << "<td>" << myTrunc(FcritArr[i]) << "</td>"
                    << "<td>" << (FArr[i] > FcritArr[i]?"отверг.":"не отверг.") << "</td>"
                    << "<td>" << (FArr[i] > FcritArr[i]?"<font color=green>да</font>":"<font color=red>нет</font>") << "</td>"
                    << "</tr>";
        }

        double FcritAB = anova.FCriticalTestAB(el);
        bool bFComparing = anova.getFTestRes().FAB > FcritAB;

        _output << "<tr>"
                << "<td>" << "AB" << "</td>"
                << "<td>" << el << "</td>"
                << "<td>" << myTrunc(anova.getFTestRes().FAB) << "</td>"
                << "<td>" << myTrunc(FcritAB) << "</td>"
                << "<td>" << (bFComparing?"отверг.":"не отверг.") << "</td>"
                << "<td>" << (bFComparing?"<font color=green>да</font>":"<font color=red>нет</font>") << "</td>"
                << "</tr>";
    }
    _output << "</table>";
}

}//stats
