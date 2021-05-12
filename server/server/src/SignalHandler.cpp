/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SignalHandler
*/

#include "SignalHandler.hpp"

bool rtype::utils::SignalHandler::_hasExited = false;

rtype::utils::SignalHandler::SignalHandler()
{
    std::signal(SIGINT, handler);
}

rtype::utils::SignalHandler::~SignalHandler()
{
}
