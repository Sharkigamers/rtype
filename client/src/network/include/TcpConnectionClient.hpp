/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** TcpConnectionClient
*/

#ifndef TCPCONNECTIONCLIENT_HPP_
#define TCPCONNECTIONCLIENT_HPP_

#include "AProtocol.hpp"

#include <memory>
#include <boost/asio.hpp>
#include <string>
#include <vector>

namespace rtype {
    namespace client {
        class TcpConnectionClient {
            public:
                TcpConnectionClient(boost::asio::io_service &ioService)
                    : _socket(ioService)
                {};
                ~TcpConnectionClient() = default;

                static std::shared_ptr<TcpConnectionClient> createInstance(boost::asio::io_service &ioService)
                {
                    return std::shared_ptr<TcpConnectionClient>(new TcpConnectionClient(ioService));
                }

                boost::asio::ip::tcp::socket &getSocket()
                {
                    return _socket;
                }

                void startRead()
                {
                    _socket.async_read_some(boost::asio::buffer(_readBufferHeader, 8), [this](const boost::system::error_code &error, std::size_t len) {
                        if (!error) {
                            try
                            {
                                std::string header(_readBufferHeader, len);
                                std::size_t toRead = std::atof(header.c_str());
                                readDataFromClient(error, toRead);
                            }
                            catch(const std::exception& e)
                            {
                                std::cerr << e.what() << '\n';
                            }
                        } else {
                            std::cout << error.message() << std::endl;
                        }
                    });
                }

                bool hasNewMessage() const noexcept
                {
                    return !_messageQueue.empty();
                }

                std::shared_ptr<rtype::protocol::Message> getLastMessage()
                {
                    std::shared_ptr<rtype::protocol::Message> lastMessage = _messageQueue.front();

                    _messageQueue.erase(_messageQueue.begin());
                    return lastMessage;
                }

            protected:
            private:
                void readDataFromClient(const boost::system::error_code &error, const std::size_t toRead)
                {
                    (void)error;
                    #if defined(_WIN32)
                        char *buffer = new char[toRead];
                    #else
                        char buffer[toRead];
                    #endif

                    _socket.async_read_some(boost::asio::buffer(buffer, toRead), [this, &buffer, &toRead](const boost::system::error_code &newError, std::size_t len) {
                        if (!newError) {
                            rtype::protocol::Message newMessage;
                            
                            std::string newBuffer(buffer, toRead);
                            std::istringstream archive_stream(newBuffer);
                            boost::archive::text_iarchive archive(archive_stream);
                            archive >> newMessage;
                            _messageQueue.push_back(std::make_shared<rtype::protocol::Message>(newMessage));
                            startRead();
                        } else {
                            std::cout << newError.message() << std::endl;
                            // setIsLogedIn(false);
                        }
                    });
                }

                char _readBufferHeader[8];
                boost::asio::ip::tcp::socket _socket;
                std::vector<std::shared_ptr<rtype::protocol::Message> > _messageQueue;
        };
    }
}
#endif /* !TCPCONNECTIONCLIENT_HPP_ */
