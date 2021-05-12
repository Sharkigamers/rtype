/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** UdpClient
*/

#include "UdpClientNetwork.hpp"

rtype::client::UdpClientNetwork::UdpClientNetwork(const std::string &endpoint, const uint16_t port)
    : _ioService(), _endpoint(boost::asio::ip::address::from_string(endpoint), port), _port(port)
{
    socket = std::make_unique<boost::asio::ip::udp::socket>(_ioService);
    socket->connect(_endpoint);
    startRead();
    networkThread = std::make_unique<std::thread>([this]() {
        while (!_ioService.stopped())
            run();
    });
}

rtype::client::UdpClientNetwork::~UdpClientNetwork()
{
    isActive = false;
    stop();
    networkThread->join();
}