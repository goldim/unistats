#pragma once

#include <vector>
#include <string>
#include <map>

struct IdValStruct
{
    std::string id;
//    long long id;
    double value;
};

//using idNameMap_t = std::map<long long, std::string>;
using idNameMap_t = std::map<std::string, std::string>;
using idValueMap_t = std::vector<IdValStruct>;
using values_t = std::vector<double>;
using ids_t = std::vector<std::string>;

#include <memory>
#include <cassert>
#include <algorithm>

template<typename __TY = int, typename __TVAL = double>
class Grid
{
public:
    Grid(unsigned n, unsigned m):
        _rowNames(n),
        _columnNames(m)
    {
        _values = new __TVAL[n][m];
    }

    void addRow(const std::string &y)
    {
        _rowNames.push_back(y);
    }

    void addColumn(const __TY &x)
    {
        _columnNames.push_back(x);
    }

    void setValue(unsigned y, unsigned x, const __TVAL &value)
    {
        _values[y][x] = value;
    }

    __TVAL getValue(const std::string &x, const __TY &y) const
    {

    }
    void setValue(const std::string &x, const __TY &y, const __TVAL &value)
    {
        if (!XExists(x))
            _rowNames.push_back(x);
        if (!YExists(y))
            _columnNames.push_back(y);
    }

    bool XExists(const std::string &x) const
    {
        return std::find(_columnNames.begin(), _columnNames.end(), x) != _columnNames.end();
    }

    bool YExists(const __TY &y) const
    {
        return std::find(_rowNames.begin(), _rowNames.end(), y) != _rowNames.end();
    }

    unsigned getRowCount(){ return _rowNames.size(); }
    unsigned getColumnCount(){ return _columnNames.size(); }
protected:
    std::unique_ptr<__TVAL> _values;
    std::vector<std::string> _rowNames;
    std::vector<__TY> _columnNames;
};
