#pragma once

#include <memory>

#include "rdbfactory.h"

class RDBFactory : public IRDBFactory
{
public:
    RDBFactory() = default;
    RDBFactory(const std::string &filename);

    virtual std::unique_ptr<IRDB> createRDB();
    virtual std::unique_ptr<IRDBValue> createRDBValue();

    virtual ~RDBFactory() = default;
private:
    std::string _filename;
};
