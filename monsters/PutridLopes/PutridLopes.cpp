/*
** EPITECH PROJECT, 2020
** PutridLopes
** File description:
** PutridLopes
*/

#include "PutridLopes.hpp"

rtype::API::PutridLopes::PutridLopes(const std::string &path) : _path(path)
{
}

std::string rtype::API::PutridLopes::getPath() const
{
    return _path;
}

void rtype::API::PutridLopes::setPath(const std::string &path) 
{
    _path = path;
}
