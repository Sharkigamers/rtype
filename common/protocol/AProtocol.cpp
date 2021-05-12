/*
** EPITECH PROJECT, 2020
** B-CPP-500-PAR-5-1-babel-emmanuel.blineau
** File description:
** AProtocol
*/

#include "AProtocol.hpp"

rtype::protocol::AProtocol::AProtocol()
{
}

rtype::protocol::AProtocol::~AProtocol()
{
}

std::shared_ptr<rtype::protocol::Message> rtype::protocol::AProtocol::createMessage(bool isRequest, const std::string &header, const std::string &body, uint16_t status)
{
    std::shared_ptr<rtype::protocol::Message> newMessage = std::make_shared<rtype::protocol::Message>(isRequest, header, body, status);

    return newMessage;
}

std::shared_ptr<rtype::protocol::RoomMessage> createRoomMessage(rtype::protocol::messageType type, const std::string &entity, uint32_t posX, uint32_t posY, int *rect, std::string &path, uint32_t frame)
{
    std::shared_ptr<rtype::protocol::RoomMessage> newMessage = std::make_shared<rtype::protocol::RoomMessage>(type, entity, posX, posY, rect, path, frame);

    return newMessage;
}
