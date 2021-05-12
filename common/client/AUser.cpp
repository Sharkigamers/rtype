/*
** EPITECH PROJECT, 2020
** client
** File description:
** AUser
*/

#include "AUser.hpp"

rtype::common::AUser::AUser(const std::string &username, const std::string &password)
    : _username(username), _password(password)
{
}

rtype::common::AUser::AUser()
    : _username(""), _password("")
{

}

rtype::common::AUser::~AUser()
{
}

std::string rtype::common::AUser::getUsername() const
{
    return _username;
}

std::string rtype::common::AUser::getPassword() const
{
    return _password;
}

void rtype::common::AUser::operator=(const AUser &other)
{
    if (&other != this) {
        _username = other.getUsername();
        _password = other.getPassword();
    }
}

void rtype::common::AUser::authentificate(const std::string &username, const std::string &password)
{
    setUsername(username);
    setPassword(password);
}

void rtype::common::AUser::setUsername(const std::string &username)
{
    _username = username;
}

void rtype::common::AUser::setPassword(const std::string &password)
{
    _password = password;
}
