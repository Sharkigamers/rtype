/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-emmanuel.blineau
** File description:
** UdpClient
*/

#ifndef UdpClient_HPP_
#define UdpClient_HPP_

#include <string>
#include <boost/asio.hpp>

namespace rtype {
    namespace server {
        class UdpClient {
            public:
                UdpClient(const std::string &addr, unsigned short);
                ~UdpClient();

                boost::asio::ip::udp::endpoint getEndpoint() const { return _clientEndpoint; }

            protected:
            private:
                boost::asio::ip::udp::endpoint _clientEndpoint;
        };
    }
}



#endif /* !UdpClient_HPP_ */
