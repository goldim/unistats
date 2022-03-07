#pragma once

#include "category_catalog.h"

struct Conditions
{
    DomainFilter category;
    DomainFilter timeseries = DomainFilter::dfYears;
    int klass = 0;
    int exam = 0;
};

class Query
{
public:
    Query() = default;
    Query(const Conditions &conditions);

    std::string getSQL(const CategoryCatalog &ctlg);

    Conditions _conditions;
protected:

};
