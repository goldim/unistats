#pragma once

#include <memory>
#include <map>
#include <vector>

#include "domain_filter.h"
#include "Config.h"
#include <iostream>

class Category
{
public:
    Category(const Config &cfg, const std::string &section):
        _idField(cfg.get(section, "id", "")),
        _nameField(cfg.get(section, "title", _idField)),
        _table(cfg.get(section, "table_name", "")),
        _sortFields(cfg.get(section, "sort", "1"))
    {
    }

    inline std::string getID() const { return _idField; }
    inline std::string getName() const { return _nameField; }
    inline std::string getTable() const { return _table; }
    inline std::string getSortFields() const { return _sortFields; }

protected:
    std::string _idField;
    std::string _nameField;
    std::string _table;
    std::string _sortFields;
};

class CategoryCatalog
{
public:
    CategoryCatalog() = default;
    CategoryCatalog(const Config &cfg){
        for (const DomainSection &section: _sections)
        {
            _categories[section.filter] = std::make_shared<Category>(cfg, section.section);
        }
    }

    std::shared_ptr<Category> getCategory(DomainFilter filter) const
    {
        return _categories.at(filter);
    }

private:
    struct DomainSection{
        DomainFilter filter;
        std::string section;
    };

    static std::vector<DomainSection> _sections;
    std::map<DomainFilter, std::shared_ptr<Category>> _categories;
};
