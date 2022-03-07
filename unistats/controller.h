#pragma once

// Qt
#include <QObject>
#include <QString>
#include <QVariantMap>
#include <QtQml>

// unistatscore
#include <unistatscore/Config.h>
#include <unistatscore/perfomance.h>

class controller : public QObject
{
    Q_OBJECT    
public:
    controller(const Config &cfg, QObject *parent = 0);
private:            
    Perfomance _perf;
    static std::map<QString, DomainFilter> _domains;
signals:

public slots:
    QVariantMap loadItems();
    QVariantMap loadSpecialties(QString facName);
    QVariantMap getRangeChart(QVariantList chosenItems);
    QVariantMap getTimeChart(QVariantList chosenItems);
    QVariantMap getStats(QVariantList chosenItems);
    QVariantMap correlation(QVariantList chosenItems);
    QVariantMap trends(QVariantList chosenItems);
    QString getAnova2(QVariantList chosenItems);    
    QVariantList getGroupClasses();

    void setOrder(int order);
    void setCriterion(QString criterion);
    void setDomain(QString domain);
    void setGroupClass(QString klass);
    void save(QString text);
};
