/*
** EPITECH PROJECT, 2020
** OOP_babel_2019
** File description:
** AProtocol
*/

#ifndef APROTOCOL_HPP_
#define APROTOCOL_HPP_

#include "IProtocol.hpp"

#include <string>
#include <memory>

namespace rtype {
    namespace protocol {
        class AProtocol {
            public:
                AProtocol();
                ~AProtocol();

                static std::shared_ptr<rtype::protocol::Message> createMessage(bool, const std::string &, const std::string &, uint16_t);
                static std::shared_ptr<rtype::protocol::RoomMessage> createRoomMessage(messageType type, const std::string &entity, uint32_t posX, uint32_t posY, int *rect, uint32_t frame);

            protected:
            private:
        };

    }
}

#endif /* !APROTOCOL_HPP_ */
