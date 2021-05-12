/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-emmanuel.blineau
** File description:
** UdpServer
*/

#include "UdpServer.hpp"

rtype::server::UdpServer::UdpServer(const std::string &host, unsigned short port, int id, const std::vector<rtype::server::UdpClient> &clients)
    : _ioService(), _endpoint(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), _socket(_ioService, _endpoint), _clients(clients), _id(id)
{
    (void)host;
    std::cout << "Udp server listening on port : " << port << ".\n";
    // _ioService.run();
    // _ioService.post()
}

rtype::server::UdpServer::UdpServer(const std::string &host, unsigned short port, int id, const rtype::server::UdpClient &client)
    : _ioService(), _endpoint(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), _socket(_ioService), _id(id)
{
    (void)host;
    _socket.open(_endpoint.protocol());
    _socket.bind(_endpoint);
    std::cout << "Udp server listening on port : " << port << ".\n";
    _clients.push_back(client);
}

rtype::server::UdpServer::UdpServer(const std::string &host, unsigned short port, int id)
    : _ioService(), _endpoint(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), _socket(_ioService, _endpoint), _id(id)
{
    (void)host;
    std::cout << "Udp server listening on port : " << port << ".\n";
}

rtype::server::UdpServer::UdpServer(const UdpServer &other)
    : _ioService(), _socket(_ioService, other.getEndpoint())
{
    if (&other != this) {
        _endpoint = other.getEndpoint();
        _clients = other.getClients();
    }
    // _ioService.run();
}

rtype::server::UdpServer::~UdpServer()
{
    std::cout << "Udp server listening on port: " << _endpoint.port() << " shutdown.\n"; 
    _socket.close();
}

rtype::server::UdpServer &rtype::server::UdpServer::operator=(const UdpServer &other)
{
    if (&other != this) {
        _endpoint = other.getEndpoint();
        _clients = other.getClients();
    }
    std::cout << "??" << std::endl;
    return *this;
}

void rtype::server::UdpServer::startReceive()
{
    _running = true;
    try
    {
        std::mutex mutex;
        while (_running) {
            boost::system::error_code error;
            boost::asio::ip::udp::endpoint senderEndpoint;
            std::array<char, sizeof(rtype::protocol::RoomMessage)> buffers;
            rtype::protocol::RoomMessage currentMessage;

            try
            {
                _socket.receive_from(boost::asio::buffer(buffers), senderEndpoint, 0, error);
                std::string newBuffer(&buffers[0], buffers.size());
                std::istringstream archive_stream(newBuffer);
                archive_stream >> currentMessage;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
            std::cout << "Received from " << senderEndpoint.address().to_string() << std::endl;

            bool add = true;
            mutex.lock();
            for (const auto &x: _clientEndpoint) {
                if (x->address().to_string() == senderEndpoint.address().to_string() && x->port() == senderEndpoint.port()) add = false;
            }
            if (add)
                _clientEndpoint.push_back(std::make_shared<boost::asio::ip::udp::endpoint>(boost::asio::ip::make_address(senderEndpoint.address().to_string()), senderEndpoint.port()));
            mutex.unlock();

            _packets.push_back(std::make_pair(senderEndpoint, std::make_shared<rtype::protocol::RoomMessage>(currentMessage)));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}

void rtype::server::UdpServer::startWrite()
{
    _running = true;
    try
    {
        std::mutex mutex;
        while (_running) {
			// std::this_thread::sleep_for(std::chrono::milliseconds(200));
            // // mutex.lock();
            // std::cout << "Packets size: " << _packets.size() << std::endl;
            // for (const auto &packet : _packets) {
            //     for (const auto &x: _clientEndpoint) {
            //         if (x->address().to_string() != packet.first.address().to_string() && x->port() != packet.first.port()) {
            //             _socket.send_to(boost::asio::buffer(packet.second), *x, 0);
            //         }
            //     }
            // }
            // _packets.clear();
            // // mutex.unlock();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}