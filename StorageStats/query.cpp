#include "query.h"

Query::Query(const Conditions &conditions):
    _conditions(conditions)
{

}

std::string Query::getSQL(const CategoryCatalog &ctlg)
{
    auto cat = ctlg.getCategory(_conditions.category);
    std::string sql = "select distinct " + cat->getID() + "," + cat->getName()
                        + " from " + cat->getTable()
                        + " where " + cat->getID()
                        + " != '' AND " + cat->getName()
                        + " != '' order by 2";
    return sql;
}
