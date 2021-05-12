/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-emmanuel.blineau
** File description:
** CUdpSocket
*/

#ifndef UdpServer_HPP_
#define UdpServer_HPP_

#include <boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/core/ref.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <boost/tuple/tuple.hpp>
#include <memory>
#include <vector>
#include <iostream>
#include <array>
#include <tuple>

#include "AProtocol.hpp"
#include "UdpClient.hpp"

namespace rtype {
    namespace server {
        class UdpServer {
            public:
                UdpServer(const std::string &, unsigned short, int, const std::vector<rtype::server::UdpClient> &);
                UdpServer(const std::string &, unsigned short, int, const rtype::server::UdpClient &);
                UdpServer(const std::string &, unsigned short, int = 0);
                UdpServer(const UdpServer &other);
                UdpServer() = delete;
                ~UdpServer();

                int getId() const noexcept { return _id; }
                boost::asio::io_service &getIoService() noexcept { return _ioService;}
                boost::asio::ip::udp::endpoint getEndpoint() const noexcept { return _endpoint; }
                boost::asio::ip::udp::socket &getSocket() noexcept { return _socket; }
                std::vector<rtype::server::UdpClient> getClients() const noexcept { return _clients; }
                unsigned short getPort() const noexcept { return _endpoint.port(); }

                void stop() { _running = false; bamboozle(); _ioService.stop(); };
                void bamboozle()
                {
                    _socket.send_to(boost::asio::buffer(""), _endpoint, 0);
                };

                bool operator==(const UdpServer &other) { return _id == other.getId(); }
                bool operator==(const int id) { return _id == id; }
                UdpServer &operator=(const UdpServer &other);
                UdpServer &operator=(UdpServer &&other)
                {
                    (void)other;
                    return *this;
                };
                void addClient(const rtype::server::UdpClient &client) { _clients.push_back(client); }

                void startReceive();
                void startWrite();

                void broadcast(const rtype::protocol::RoomMessage &message)
                {
                    char *data = (char*)&message;
                    for (const auto &x : _clientEndpoint) {
                        _socket.send_to(boost::asio::buffer(data, sizeof(rtype::protocol::RoomMessage)), *x, 0);
                    }
                }

                bool nbClients() const
                {
                    return _clientEndpoint.size();
                }

                bool hasNewMessage() const
                {
                    return !_packets.empty();
                }

                std::pair<boost::asio::ip::udp::endpoint, std::shared_ptr<rtype::protocol::RoomMessage> > getLastMessage()
                {
                    std::pair<boost::asio::ip::udp::endpoint, std::shared_ptr<rtype::protocol::RoomMessage> > lastMessage = _packets.front();

                    _packets.erase(_packets.begin());
                    return lastMessage;
                }

            private:
                boost::asio::io_service _ioService;
                boost::asio::ip::udp::endpoint _endpoint;
                boost::asio::ip::udp::socket _socket;
                std::vector<rtype::server::UdpClient> _clients;
                std::vector<std::shared_ptr<boost::asio::ip::udp::endpoint> > _clientEndpoint;
                int _id;
                char _buffer[sizeof(rtype::protocol::RoomMessage)];
                std::vector<std::shared_ptr<rtype::protocol::RoomMessage> > _inPackets;
                std::vector<std::pair<boost::asio::ip::udp::endpoint, std::shared_ptr<rtype::protocol::RoomMessage> > > _packets;
                bool _running;

            private:
                boost::asio::ip::udp::endpoint _senderEndpoint;

        };
    }
}

#endif /* !UdpServer_HPP_ */
