/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** TcpClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include "TcpConnectionClient.hpp"
#include "FileDownload.hpp"

#include <thread>

using boost::asio::ip::tcp;

namespace rtype {
    namespace client {
        class TcpClient {
            public:
                TcpClient(const std::string &endpoint, const uint16_t port);
                ~TcpClient();

                std::shared_ptr<rtype::client::TcpConnectionClient> getConnection()
                {
                    return _tcpConnection;
                }

                bool hasNewMessage() noexcept
                {
                    globalMutex.lock();
                    bool res = !_messageQueue.empty();
                    globalMutex.unlock();
                    return res;
                }

                std::shared_ptr<rtype::protocol::Message> getLastMessage()
                {
                    globalMutex.lock();
                    std::shared_ptr<rtype::protocol::Message> lastMessage = _messageQueue.front();

                    _messageQueue.erase(_messageQueue.begin());
                    globalMutex.unlock();
                    return lastMessage;
                }

                void downloadRessource(const std::string &fileName)
                {
                    const std::vector<std::string> data {fileName};
                    const std::map<std::string, std::string> header = rtype::protocol::createHeader("FILE_DOWNLOAD");
                    const std::map<std::string, std::string> body = rtype::protocol::createBody(data, rtype::protocol::emptyPos, rtype::protocol::emptyId);

                    const std::shared_ptr<rtype::protocol::Message> message = rtype::protocol::AProtocol::createMessage(1, rtype::common::JsonUtility::mapToJson(header), rtype::common::JsonUtility::mapToJson(body), rtype::protocol::messageType::FILE_DOWNLOAD);

                    writeToServer(*message, [](const boost::system::error_code &error, const long unsigned int read){(void)error;(void)read;});
                
                    // while (hasNewMessage() == false);
                    // std::shared_ptr<rtype::protocol::Message> response = getLastMessage();
                    
                    // std::map<std::string, std::string> responseBody = response->parseBody();
                    // std::cout << responseBody["DATA"] << std::endl;
                    // const std::vector<std::string> responseData = rtype::protocol::unformatData(responseBody["DATA"]);
                    // const std::string decoded = rtype::common::Base64::base64_decode(responseData[0]);

                    // std::ofstream file("lopes2.png");

                    // file << decoded << std::endl;

                    // file.close();
                }

                void createRoom()
                {
                    const std::vector<std::string> data {"OK"};
                    const std::map<std::string, std::string> header = rtype::protocol::createHeader("CREATE_ROOM");
                    const std::map<std::string, std::string> body = rtype::protocol::createBody(data, rtype::protocol::emptyPos, rtype::protocol::emptyId);

                    const std::shared_ptr<rtype::protocol::Message> message = rtype::protocol::AProtocol::createMessage(1, rtype::common::JsonUtility::mapToJson(header), rtype::common::JsonUtility::mapToJson(body), rtype::protocol::messageType::CREATE_ROOM);

                    writeToServer(*message, [](const boost::system::error_code &error, const long unsigned int read){(void)error;(void)read;});
                }

                void getRoom()
                {
                    const std::vector<std::string> data;
                    const std::map<std::string, std::string> header = rtype::protocol::createHeader("GET_ROOMS");
                    const std::map<std::string, std::string> body = rtype::protocol::createBody(data, rtype::protocol::emptyPos, rtype::protocol::emptyId);

                    const std::shared_ptr<rtype::protocol::Message> message = rtype::protocol::AProtocol::createMessage(1, rtype::common::JsonUtility::mapToJson(header), rtype::common::JsonUtility::mapToJson(body), rtype::protocol::messageType::GET_ROOMS);

                    writeToServer(*message, [](const boost::system::error_code &error, const long unsigned int read){(void)error;(void)read;});
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
                    boost::asio::async_write(*socket, buffers, handler);
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
                void handle_connect(std::shared_ptr<rtype::client::TcpConnectionClient> &connection, const boost::system::error_code& error) // (4)
                {
                    if (!error)
                    {
                        connection->startRead();
                    } else {
                        std::cout << error.message() << std::endl;
                    }
                }

                void startRead()
                {
                    boost::asio::async_read(*socket, boost::asio::buffer(_readBufferHeader), 
                        boost::bind(&TcpClient::readHandler, this, boost::asio::placeholders::error));
                }

                void readHandler(const boost::system::error_code &error)
                {
                    if (!error) {
                        try
                        {
                            std::string header(_readBufferHeader, 8);
                            std::size_t toRead = std::atof(header.c_str());
                            _readData.resize(toRead);
                            boost::asio::async_read(*socket, boost::asio::buffer(_readData), 
                                boost::bind(&TcpClient::readDataFromClient, this, boost::asio::placeholders::error));
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
                void readDataFromClient(const boost::system::error_code &error)
                {
                    if (!error) {
                        rtype::protocol::Message newMessage;
                        
                        std::string newBuffer(&_readData[0], _readData.size());
                        try
                        {
                            std::istringstream archive_stream(newBuffer);
                            boost::archive::text_iarchive archive(archive_stream);
                            archive >> newMessage;
                            globalMutex.lock();
                            _messageQueue.push_back(std::make_shared<rtype::protocol::Message>(newMessage));
                            globalMutex.unlock();
                        }
                        catch(const std::exception& e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                        startRead();
                    } else {
                        std::cerr << error.message() << std::endl;
                    }
                }

                char _readBufferHeader[8];
                std::vector<std::shared_ptr<rtype::protocol::Message> > _messageQueue;
                std::vector<char> _readData;

            private:
                std::unique_ptr<std::thread> networkThread;
                std::mutex globalMutex;
                bool isActive = true;

            public:
                void startDownload(const std::string &file, uint32_t nbPackets) 
                {
                    _fileDownload.push_back(std::make_unique<FileDownload>(file, nbPackets));
                    std::cout << "Started download of file " << file << "\n";
                }

                void addDataDownload(const std::shared_ptr<rtype::protocol::Message> &message)
                {
                    const std::map<std::string, std::string> headerInfo = message->parseHeader();
                    const std::string fileName = headerInfo.at("ID");

                    for (const auto &x : _fileDownload) {
                        if (*x == fileName) {
                            x->addNewMessage(message);
                        }
                    }
                }

            private:
                std::vector<std::unique_ptr<FileDownload> > _fileDownload;

            private:
                boost::asio::io_service _ioService;
                boost::asio::ip::tcp::endpoint _endpoint;
                std::unique_ptr<boost::asio::ip::tcp::socket> socket;
                std::shared_ptr<rtype::client::TcpConnectionClient> _tcpConnection;
                uint16_t _port;
        };
    }
}

#endif /* !TCPCLIENT_HPP_ */
