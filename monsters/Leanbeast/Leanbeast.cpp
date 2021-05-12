/*
** EPITECH PROJECT, 2020
** Leanbeast
** File description:
** Leanbeast
*/

#include "Leanbeast.hpp"

rtype::API::Leanbeast::Leanbeast(const std::string &path) : _path(path)
{
}

std::string rtype::API::Leanbeast::getPath() const
{
    return _path;
}

void rtype::API::Leanbeast::setPath(const std::string &path) 
{
    _path = path;
}
