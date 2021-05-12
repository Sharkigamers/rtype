/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-emmanuel.blineau
** File description:
** TcpConnection
*/

#ifndef TcpConnection_HPP_
#define TcpConnection_HPP_

#include <boost/asio.hpp>
#include <memory>

#include "ITcpSocket.hpp"

namespace rtype {
    namespace server {
        class TcpConnection {
            public:
                TcpConnection(boost::asio::io_service &ioService);
                ~TcpConnection();

                std::unique_ptr<boost::asio::ip::tcp::socket> &getSocket() { return _socket; }

            protected:
            private:
                std::unique_ptr<boost::asio::ip::tcp::socket> _socket;
        };
    }
}

#endif /* !TcpConnection_HPP_ */
