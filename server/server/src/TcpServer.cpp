/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-emmanuel.blineau
** File description:
** TcpServer
*/

#include "TcpServer.hpp"

#include <iostream>
#include <ios>

#include "Server.hpp"

rtype::server::TcpServer::TcpServer(bool isIPv4, unsigned short port, rtype::server::IServer *server)
    : _ioService(), _server(server), _clientWatcherThread([this]() {
        std::mutex mutex;
        while (static_cast<rtype::server::Server *>(_server)->isUp()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            mutex.lock();
            std::cout << "Nb clients: " << _clientsQueue.size() << std::endl;
            for (std::size_t i = 0; i < _clientsQueue.size(); i++) {
                if (_clientsQueue[i]->isLogedIn() == false) {
                    static_cast<rtype::server::Server *>(_server)->onClientDisconnect(*_clientsQueue.at(i));
                    _clientsQueue.erase(_clientsQueue.begin() + i);
                    continue;
                }
            }
            mutex.unlock();
        }
        mutex.unlock();
        _ioService.stop();
    })
{
    auto x = [isIPv4]() {
        if (isIPv4) {
            return boost::asio::ip::tcp::v4();
        } else {
            return boost::asio::ip::tcp::v6();
        }
    };
    boost::asio::ip::tcp::endpoint endpoint(x(), port);
    _acceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(getIoService(), endpoint);

    std::cout << "Listening on port " << port << '\n';
}

rtype::server::TcpServer::~TcpServer()
{
    _clientWatcherThread.join();
}

void rtype::server::TcpServer::waitClient()
{
    std::shared_ptr<rtype::server::TcpConnection> newConnection = std::make_shared<rtype::server::TcpConnection>(getIoService());

    _acceptor->async_accept(*newConnection->getSocket(),
        std::bind(&rtype::server::TcpServer::acceptConnection, this,
        std::placeholders::_1,
        newConnection)
    );
}

void rtype::server::TcpServer::acceptConnection(const boost::system::error_code& error, std::shared_ptr<rtype::server::TcpConnection> newConnection)
{
    if (!error)
    {
        std::cout << "Connection accepted from " << newConnection->getSocket()->remote_endpoint().address().to_string() << std::endl;
        _clientsQueue.push_back(std::make_shared<rtype::server::ServerClient>(newConnection));
        _clientsQueue[_clientsQueue.size() -1]->setServer(_server);
        static_cast<rtype::server::Server *>(_server)->onClientConnection(*_clientsQueue[_clientsQueue.size() -1]);
        _clientsQueue[_clientsQueue.size() -1]->readFromClient();
        this->waitClient();
	}
	else {
		std::cerr << "Connection denied" << std::endl;
	}
}