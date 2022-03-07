#include "storage.h"
#include "rdbfactory_impl.h"

using std::string;

Storage::Storage(const Config &cfg):
    _db((new RDBFactory(cfg.get("db", "path", "")))->createRDB().release()),
    _catalog(cfg)
{
}

std::vector<Storage::ID> Storage::getIDs()
{
    auto cat = _catalog.getCategory(_conditions.category);
    std::string sql = "select distinct " + cat->getID() + "," + cat->getName()
                        + " from " + cat->getTable()
                        + " where " + cat->getID()
                        + " != '' AND " + cat->getName()
                        + " != '' order by 2";

    _db->request(sql.c_str());
    std::cout << sql << std::endl;

    std::vector<Storage::ID> res;

    while (_db->next()){
        Storage::ID id;
        id.id = _db->get(0)->toStdString();
        id.name = _db->get(1)->toStdString();
        res.push_back(id);
    }
    return res;
}

std::vector<Storage::ID> Storage::getIDsByID(DomainFilter category, const std::string &id) const
{
    auto auxCat = _catalog.getCategory(category);
    auto auxId = auxCat->getID();
    auto auxTitle = auxCat->getName();

    auto mainCat = _catalog.getCategory(_conditions.category);
    auto mainId = mainCat->getID();
    auto mainTitle = mainCat->getName();

    string sql = "SELECT distinct " + mainId + "," + mainTitle
                + " FROM " + mainCat->getTable()
                + " where " + auxId + " != '' AND " + auxTitle + " != ''"
                + " AND " + auxId + " = '" + id + "' order by 2";
    std::cout << sql << std::endl;
    _db->request(sql.c_str());

    std::vector<Storage::ID> res;

    while (_db->next()){
        Storage::ID item;
        item.id = _db->get(0)->toStdString();
        item.name = _db->get(1)->toStdString();
        res.push_back(item);
    }

    return res;
}

std::vector<int> Storage::getKlasses()
{
    std::string sql = "select distinct klass from marks_stat order by 1";
    _db->request(sql.c_str());
    std::vector<int> res;
    while (_db->next()){
        res.push_back(_db->get(0)->toInt());
    }
    return res;
}

static string convert(const ids_t &ids)
{
    string idsStr = "";

    for (auto &id : ids)
    {
        idsStr += "'" + id + "'";
        idsStr += ",";
    }

    idsStr = idsStr.substr(0, idsStr.size() - 1);

    return idsStr;
}

std::vector<Storage::Item> Storage::getItems(const ids_t &ids, bool bTimeSeries) const
{
    auto cat = _catalog.getCategory(_conditions.category);

    string klass = "";
    if (_conditions.klass != 0)
    {
        klass = " AND klass=" + std::to_string(_conditions.klass);
    }

    string idsStr = convert(ids);
    auto mainCat = (!bTimeSeries) ? cat : _catalog.getCategory(_conditions.timeseries);
    string where = "WHERE cast(" + cat->getID() +" as text) IN (" + idsStr + ")" + klass;
    string from = "FROM " + cat->getTable() + " ";
    string order = "ORDER BY " + ((_conditions.exam > 0 && _conditions.timeseries != DomainFilter::dfExamOrder)
                    ? _catalog.getCategory(DomainFilter::dfExamOrder)->getSortFields()
                    : mainCat->getSortFields());

    string byExam = "";
    if (_conditions.exam > 0 && _conditions.timeseries != DomainFilter::dfExamOrder)//по экзаменам
    {
        byExam = _catalog.getCategory(DomainFilter::dfExamOrder)->getID()  + ", ";
    }
    string sql = "SELECT " + byExam + mainCat->getID() + ", count_satisfactory_student, count_student";
    sql = sql + " " + from + " " + where + " " + order;

     std::cout << sql << std::endl;
    _db->request(sql.c_str());

    if (bTimeSeries && _conditions.timeseries == DomainFilter::dfExamOrder)
    {
        return examTimeSeries();
    }

    if (_conditions.exam > 0)
    {
        return examPostProcess();
    }

    std::vector<Storage::Item> res;

    while (_db->next()){
        Storage::Item item;
        item.id = _db->get(0)->toStdString();
        item.success = _db->get(1)->toInt();
        item.all = _db->get(2)->toInt();
        res.push_back(item);
    }

    return res;
}

std::vector<Storage::Item> Storage::examPostProcess() const
{
    long long term = 0;
    int order = 0;
    string group = "unknown";
    string group_title = "unknown";
    string subj = "unknown";

    std::vector<Storage::Item> res;

    while (_db->next()){
        if (_db->get(2)->toLongLong() != term
                || (_db->get(0)->toStdString() != group
                && _db->get(1)->toStdString() != group_title))
        {
            order = 1;
        }
        else
        {
            if (_db->get(3)->toStdString() != subj)
            {
                order++;
            }
        }

        if (order > 4)
            continue;

        term = _db->get(2)->toLongLong();
        group = _db->get(0)->toStdString();
        group_title = _db->get(1)->toStdString();
        subj = _db->get(3)->toStdString();

        if (_conditions.exam == order){
            Storage::Item item;
            item.id = _db->get(4)->toStdString();
            item.success = _db->get(5)->toDouble();
            item.all = _db->get(6)->toDouble();
            res.push_back(item);
        }
    }

    return res;
}

std::vector<Storage::Item> Storage::examTimeSeries() const
{
    long long term = 0;
    int order = 0;
    string group = "unknown";
    string group_title = "unknown";
    string subj = "unknown";

    std::vector<Storage::Item> res;

    while (_db->next()){

        if ((_db->get(2)->toLongLong() != term)
                || (_db->get(0)->toStdString() != group
                && _db->get(1)->toStdString() != group_title))
        {
            order = 1;
        }
        else
        {
            if (_db->get(3)->toStdString() != subj)
            {
                order++;
            }
        }

        if (order > 4)
            continue;

        term = _db->get(2)->toLongLong();
        group = _db->get(0)->toStdString();
        group_title = _db->get(1)->toStdString();
        subj = _db->get(3)->toStdString();
//            std::cout << order << " " << term << " " << group << " " << group_title << " " << _db->get(3)->toStdString() << std::endl;
        Storage::Item item;
        item.id = std::to_string(order);
        item.success = _db->get(4)->toDouble();
        item.all = _db->get(5)->toDouble();
        res.push_back(item);
    }
    return res;
}
