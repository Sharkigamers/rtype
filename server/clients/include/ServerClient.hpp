/*
** EPITECH PROJECT, 2020
** OOP_babel_2019
** File description:
** ServerClient
*/

#ifndef SERVERCLIENT_HPP_
#define SERVERCLIENT_HPP_

#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>
#include <array>

#include "common/client/AUser.hpp"
#include "common/ISerializable.hpp"
#include "common/protocol/IProtocol.hpp"

#include "TcpConnection.hpp"

#include "IServer.hpp"

namespace rtype {
    namespace server {
        class ServerClient : public rtype::common::AUser, public rtype::common::ISQLSerializable {
            public:
                explicit ServerClient(int id, const std::string &username, const std::string &password, bool isConnected);
                explicit ServerClient(std::shared_ptr<rtype::server::TcpConnection> &tcpConnection);
                explicit ServerClient(const ServerClient &);
                explicit ServerClient();
                ~ServerClient();

                ServerClient &operator=(const ServerClient &other);
                std::string toSQLString() const final;

                void setTcpConnection(std::shared_ptr<rtype::server::TcpConnection> tcpConnection) { _tcpConnection = tcpConnection; };
                std::shared_ptr<rtype::server::TcpConnection> getTcpConnection() const { return _tcpConnection; };

                bool isNewMessage() const { return !_messageQueue.empty(); }
                std::shared_ptr<rtype::protocol::Message> getLastMessage();

                std::string getClientInfo() const;
                int getId() const { return _id; }
                void setId(int id) { _id = id; }
                
                bool isConnected() const { return _isConnected; }
                
                bool isLogedIn() const { return _isLogedIn; }
                void setIsLogedIn(bool state) { _isLogedIn = state; }

                void authentificateClient(int id, const std::string &username, const std::string &password);

                void readFromClient();
                std::vector<std::shared_ptr<rtype::protocol::Message> > &getMessageQueue() { return _messageQueue; }
                void setServer(rtype::server::IServer *server) { _server = server; }

                template <typename T, typename Handler>
                void writeToClient(const T &t, Handler handler)
                {
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
                    boost::asio::async_write(*getTcpConnection()->getSocket(), buffers, handler);
                }

            private:
                void readDataFromClient(const boost::system::error_code &error, const std::size_t toRead);

            protected:
            private:
                int _id;
                bool _isConnected;
                bool _isLogedIn = false;
                std::shared_ptr<rtype::server::TcpConnection> _tcpConnection;
                std::vector<std::shared_ptr<rtype::protocol::Message> > _messageQueue;
                rtype::server::IServer *_server;
                char _readBufferHeader[8];
        };
    }
}

#endif /* !SERVERCLIENT_HPP_ */
