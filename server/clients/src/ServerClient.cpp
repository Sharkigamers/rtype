/*
** EPITECH PROJECT, 2020
** OOP_babel_2019
** File description:
** ServerClient
*/

#include "ServerClient.hpp"
#include "Server.hpp"
#include <iostream>

rtype::server::ServerClient::ServerClient(int id, const std::string &username, const std::string &password, bool isConnected)
    : AUser(username, password), _id(id), _isConnected(isConnected), _tcpConnection(nullptr)
{
}

rtype::server::ServerClient::ServerClient(std::shared_ptr<rtype::server::TcpConnection> &tcpConnection)
    : AUser(), _id(-1), _isConnected(true), _tcpConnection(tcpConnection)
{
    _isLogedIn = true;
}

rtype::server::ServerClient::ServerClient()
    : AUser(), _id(-1), _isConnected(false), _tcpConnection(nullptr)
{
}

rtype::server::ServerClient::ServerClient(const rtype::server::ServerClient &other)
    : AUser(other.getUsername(), other.getPassword())
{
    if (&other != this) {
        this->setId(other.getId());
        this->setTcpConnection(other.getTcpConnection());
    }
}

rtype::server::ServerClient::~ServerClient()
{
}

std::string rtype::server::ServerClient::toSQLString() const 
{
    std::string res = "";

    res.append("('" + getUsername() + "'," + "'" + getPassword() + "'" + ");");
    return res;
}

std::shared_ptr<rtype::protocol::Message> rtype::server::ServerClient::getLastMessage()
{
    std::mutex mutex;

    mutex.lock();
    std::shared_ptr<rtype::protocol::Message> lastMessage = _messageQueue[_messageQueue.size() - 1];
    
    _messageQueue.pop_back();
    mutex.unlock();
    return lastMessage;
}

std::string rtype::server::ServerClient::getClientInfo() const
{
	return "";
}

void rtype::server::ServerClient::authentificateClient(int id, const std::string &username, const std::string &password)
{
    setId(id);
    authentificate(username, password);
}

rtype::server::ServerClient &rtype::server::ServerClient::operator=(const ServerClient &other)
{
    if (&other != this) {

    }
    return *this;
}

void rtype::server::ServerClient::readFromClient()
{
    (*getTcpConnection()->getSocket()).async_read_some(boost::asio::buffer(_readBufferHeader, 8), [this](const boost::system::error_code &error, std::size_t len) {
        if (!error) {
            try
            {
                std::string header(_readBufferHeader, len);
                std::size_t toRead = std::atof(header.c_str());
                std::cout << header << std::endl;
                readDataFromClient(error, toRead);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        } else {
            std::cout << (getUsername() == "" ? "Unconnected" : getUsername()) << " : Disconnected." << std::endl;
            setIsLogedIn(false);
        }
    });
}

void rtype::server::ServerClient::readDataFromClient(const boost::system::error_code &error, const std::size_t toRead)
{
    (void)error;
	#if defined(_WIN32)
		char *buffer = new char[toRead];
	#else
		char buffer[toRead];
	#endif

    (*getTcpConnection()->getSocket()).async_read_some(boost::asio::buffer(buffer, toRead), [this, &buffer](const boost::system::error_code &newError, std::size_t len) {
        if (!newError) {
            rtype::protocol::Message newMessage;
            
            
            try
            {
                std::string newBuffer(buffer, len);
                std::istringstream archive_stream(newBuffer);
                boost::archive::text_iarchive archive(archive_stream);
                archive >> newMessage;
                _messageQueue.push_back(std::make_shared<rtype::protocol::Message>(newMessage));
                static_cast<rtype::server::Server *>(_server->getInstance())->handleNewMessage(this);
                readFromClient();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
            
        } else {
            std::cout << newError.message() << std::endl;
            setIsLogedIn(false);
        }
    });
}