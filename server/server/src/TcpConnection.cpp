/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-emmanuel.blineau
** File description:
** TcpConnection
*/

#include "TcpConnection.hpp"

rtype::server::TcpConnection::TcpConnection(boost::asio::io_service &ioService)
    : _socket(std::make_unique<boost::asio::ip::tcp::socket>(ioService))
{
}

rtype::server::TcpConnection::~TcpConnection()
{
}
