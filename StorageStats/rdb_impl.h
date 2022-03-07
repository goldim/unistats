#pragma once

// STL
#include <iostream>
#include <memory>
// Qt
#include <QtSql>
// local
#include "rdb.h"

class RDBValue : public IRDBValue
{
public:
    RDBValue() = default;
    RDBValue(const QVariant &val);

    virtual int toInt();
    virtual long long toLongLong();
    virtual double toDouble();
    virtual std::string toStdString();

    virtual ~RDBValue() = default;
private:
    QVariant _val;
};

class RDB : public IRDB
{
public:
    RDB(const std::string &filename);

    virtual void select(){}
    virtual void insert(){}
    virtual void update(){}
    virtual void del(){}

    virtual void request(const char *sql);
    virtual bool next();
    virtual std::unique_ptr<IRDBValue> get(int column) const;

    virtual ~RDB();
private:
    QSqlDatabase _db;
    QSqlQuery _query;
};
