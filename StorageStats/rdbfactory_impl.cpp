#include "rdbfactory_impl.h"
#include "rdb_impl.h"

RDBFactory::RDBFactory(const std::string &filename):
    _filename(filename)
{

}

std::unique_ptr<IRDB> RDBFactory::createRDB()
{
    return std::unique_ptr<RDB>(new RDB(_filename));
}

std::unique_ptr<IRDBValue> RDBFactory::createRDBValue()
{
    return std::unique_ptr<RDBValue>(new RDBValue());
}
