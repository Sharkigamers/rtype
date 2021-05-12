/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** ITcpSocket
*/

#ifndef ITCPSOCKET_HPP_
#define ITCPSOCKET_HPP_

#include "IProtocol.hpp"

namespace rtype {
    namespace server {
        class ITcpSocket {
            public:
                ~ITcpSocket() = default;

                template<typename T>
                void write(const T &t) = delete;

                template<typename T>
                void asyncWrite(const T &t) = delete;

                template<typename T>
                T read(const T &t) = delete;

                template<typename T>
                T asyncRead(const T &t) = delete;
        };

    }
}

#endif /* !ITCPSOCKET_HPP_ */
