/*
 * Config.cpp
 *
 *  Created on: 07.01.2017
 *      Author: goldim
 */

#include "Config.h"
#include <boost/property_tree/ini_parser.hpp>

#include <iostream>

using namespace boost;
using std::string;

Config::Config(const string &path):
_Path(path)
{
	property_tree::ini_parser::read_ini(_Path, _Tree);
}

string Config::get(const string &key) const
{
    return _Tree.get<string>(key);
}

string Config::get(const string &key, const string &defVal) const
{
    std::string value = defVal;
    try
    {
        value = get(key);
    }
    //catch (const boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::ptree_bad_path> > &ex)
    catch (...)
    {
    }
    return value;
}

string Config::get(const string &section, const string &key, const std::string &defVal) const
{
    return get(section + "." + key, defVal);
}

void Config::set(const string &key, const string &value)
{
    //_Tree.set<string, string>(key, value);
}


