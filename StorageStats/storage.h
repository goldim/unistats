#pragma once

#include <vector>

#include "defs.h"
#include "rdb.h"
#include "category_catalog.h"
#include "query.h"

class Storage
{
public:
    Storage(const Config &cfg);

    struct ID
    {
        std::string id;
        std::string name;
    };

    struct Item
    {
        std::string id;
        int success;
        int all;
    };

    inline void set(Conditions c){ _conditions = c; }

    std::vector<ID> getIDs();
    std::vector<ID> getIDsByID(DomainFilter category, const std::string &id) const;
    std::vector<int> getKlasses();
    std::vector<Item> getItems(const ids_t &ids, bool bTimeSeries = false) const;
private:
    std::vector<Item> examTimeSeries() const;
    std::vector<Item> examPostProcess() const;
private:
    std::shared_ptr<IRDB> _db;
    CategoryCatalog _catalog;

    Conditions _conditions;
//    Query _lastquery;
};
