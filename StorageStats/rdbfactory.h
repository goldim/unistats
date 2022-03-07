#pragma once

// STL
#include <memory>
// local
#include "rdb.h"

class IRDBFactory
{
public:
    IRDBFactory() = default;

    virtual std::unique_ptr<IRDB> createRDB() = 0;
    virtual std::unique_ptr<IRDBValue> createRDBValue() = 0;

    virtual ~IRDBFactory() = default;
};
