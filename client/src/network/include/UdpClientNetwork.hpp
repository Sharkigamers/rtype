/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** UdpClientNetwork
*/

#ifndef UdpClientNetwork_HPP_
#define UdpClientNetwork_HPP_

#include <boost/asio.hpp>
#include "AProtocol.hpp"

#include <thread>

using boost::asio::ip::udp;

namespace rtype {
    namespace client {
        class UdpClientNetwork {
            public:
                UdpClientNetwork(const std::string &endpoint, const uint16_t port);
                ~UdpClientNetwork();

                bool hasNewMessage() noexcept
                {
                    globalMutex.lock();
                    bool res = !_messageQueue.empty();
                    globalMutex.unlock();
                    return res;
                }

                std::shared_ptr<rtype::protocol::RoomMessage> getLastMessage()
                {
                    globalMutex.lock();
                    std::shared_ptr<rtype::protocol::RoomMessage> lastMessage = _messageQueue.front();

                    _messageQueue.erase(_messageQueue.begin());
                    globalMutex.unlock();
                    return lastMessage;
                }

                template <typename T, typename Handler>
                void writeToServer(const T &t, Handler handler)
                {
                    (void)handler;
                    std::ostringstream archive_stream;
                    boost::archive::text_oarchive archive(archive_stream);
                    archive << t;
                    std::string m_outbound_data = archive_stream.str();

                    std::ostringstream header_stream;
                    header_stream << std::setw(8)
                        << m_outbound_data.size();
                    if (!header_stream || header_stream.str().size() != 8)
                    {
                        std::cout << "RIP" << std::endl;
                        return;
                    }
                    std::string m_outbound_header = header_stream.str();

                    std::vector<boost::asio::const_buffer> buffers;
                    buffers.push_back(boost::asio::buffer(m_outbound_header));
                    buffers.push_back(boost::asio::buffer(m_outbound_data));
                    // boost::asio::async_write(_udpConnection->getSocket(), buffers, handler);
                }

                void run()
                {
                    _ioService.run();
                };
                void stop()
                {
                    _ioService.stop();
                };

            private:
                void startRead()
                {
                    // boost::asio::async_read(*socket, boost::asio::buffer(_readData), 
                    //     boost::bind(&UdpClientNetwork::readHandler, this, boost::asio::placeholders::error));
                }

                void readHandler(const boost::system::error_code &error)
                {
                    if (!error) {
                        try
                        {
                            rtype::protocol::RoomMessage currentMessage;

                            std::string newBuffer(&_readData[0], _readData.size());
                            try
                            {
                                std::istringstream archive_stream(newBuffer);
                                archive_stream >> currentMessage;
                                globalMutex.lock();
                                _messageQueue.push_back(std::make_shared<rtype::protocol::RoomMessage>(currentMessage));
                                globalMutex.unlock();
                            }
                            catch(const std::exception& e)
                            {
                                std::cerr << e.what() << '\n';
                            }
                            startRead();
                            }
                        catch(const std::exception& e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                    } else {
                        std::cout << error.message() << std::endl;
                    }
                }

            private:
                std::vector<std::shared_ptr<rtype::protocol::RoomMessage> > _messageQueue;
                std::array<char, sizeof(rtype::protocol::RoomMessage)> _readData;

            private:
                std::unique_ptr<std::thread> networkThread;
                std::mutex globalMutex;
                bool isActive = true;
            private:
                boost::asio::io_service _ioService;
                boost::asio::ip::udp::endpoint _endpoint;
                std::unique_ptr<boost::asio::ip::udp::socket> socket;
                uint16_t _port;
        };
    }
}

#endif /* !UdpClientNetwork_HPP_ */
