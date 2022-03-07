#include "rdb_impl.h"

RDB::RDB(const std::string &filename):
    _db(QSqlDatabase::addDatabase("QSQLITE"))
{
    _db.setDatabaseName(QString::fromStdString(filename));
    _db.open();
}

RDB::~RDB()
{
    _db.close();
}

void RDB::request(const char *sql)
{    
    _query.exec(sql);
}

bool RDB::next()
{
    return _query.next();
}

RDBValue::RDBValue(const QVariant &val):
    _val(val)
{
}

int RDBValue::toInt()
{
    return _val.toInt();
}

long long RDBValue::toLongLong()
{
    return _val.toLongLong();
}

double RDBValue::toDouble()
{
    return _val.toDouble();
}

std::string RDBValue::toStdString()
{
    return _val.toString().toStdString();
}

std::unique_ptr<IRDBValue> RDB::get(int column) const
{
    auto value = _query.value(column);    
    return std::unique_ptr<IRDBValue>(new RDBValue(value));
}
