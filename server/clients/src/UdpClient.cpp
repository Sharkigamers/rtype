/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-emmanuel.blineau
** File description:
** UdpClient
*/

#include "UdpClient.hpp"

rtype::server::UdpClient::UdpClient(const std::string &addr, unsigned short port)
    : _clientEndpoint(boost::asio::ip::address::from_string(addr), port)
{
}

rtype::server::UdpClient::~UdpClient()
{
}
