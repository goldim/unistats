#pragma once

#include <memory>

class IRDBValue
{
public:
    virtual int toInt() = 0;
    virtual long long toLongLong() = 0;
    virtual double toDouble() = 0;
    virtual std::string toStdString() = 0;

    virtual ~IRDBValue() = default;
};

class IRDB
{
public:
    enum class Types{
        INT,
        DOUBLE,
        TEXT,
        LONGLONG
    };

    virtual void select() = 0;
    virtual void insert() = 0;
    virtual void update() = 0;
    virtual void del() = 0;

    virtual void request(const char *sql) = 0;
    virtual bool next() = 0;
    virtual std::unique_ptr<IRDBValue> get(int column) const = 0;

    virtual ~IRDB() = default;
};
