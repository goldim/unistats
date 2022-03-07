/*
 * Config.h
 *
 *  Created on: 07.01.2017
 *      Author: goldim
 */

#pragma once

#include <boost/property_tree/ptree.hpp>
#include <string>

class ptree;

class Config
{
public:
    Config(const std::string &path);
    ~Config() = default;

    std::string get(const std::string &key) const;
    std::string get(const std::string &key, const std::string &defVal) const;
    std::string get(const std::string &section, const std::string &key, const std::string &defVal) const;
    void set(const std::string &key, const std::string &value);
private:
	std::string _Path;
	boost::property_tree::ptree _Tree;
};
