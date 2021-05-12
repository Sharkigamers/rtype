/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** IPCMessage
*/

#ifndef IPCMESSAGE_HPP_
#define IPCMESSAGE_HPP_

#include <memory>
#include <string.h>

#include "JsonUtility.hpp"

namespace rtype {
    namespace room {
        enum IPCMessageType : uint8_t {
            ROOM_NONE = 0,
            ROOM_SHUTDOWN = 1,
            ROOM_STATUS = 2
        };
        
        #pragma pack(0)
        struct IPCMessage {
            IPCMessage(IPCMessageType messageType, bool request, const char newMessage[480], pid_t idFrom)
                : type(messageType), isRequest(request), from(idFrom)
            {
                bzero(message, 480);
                if (memcpy(message, newMessage, 480) == nullptr)
                    throw std::runtime_error("Error while creating a message");
            }

            IPCMessage(const IPCMessage &other)
                : type(other.type), isRequest(other.isRequest), from(other.from)
            {
                bzero(message, 480);
                if (memcpy(message, other.message, 480) == nullptr)
                    throw std::runtime_error("Error while creating a message");
            }

            IPCMessage()
                : type(ROOM_NONE), isRequest(!true), from(0)
            {
                bzero(message, 480);
            }

            IPCMessage &operator=(const IPCMessage &other)
            {
                if (&other != this) {
                    type = other.type;
                    isRequest = other.isRequest;
                    memcpy(message, other.message, 480);
                    from = other.from;
                }
                return *this;
            }

            std::size_t size() const
            {
                return sizeof(IPCMessageType) + sizeof(bool) + sizeof(pid_t) + (strlen(message) + 1);
            }

            IPCMessageType type;
            bool isRequest;
            pid_t from;
            char message[480];
        };
        #pragma pack(1)

        inline std::shared_ptr<IPCMessage> createIPCMessage(IPCMessageType messageType, bool request, const std::string &newMessage, pid_t from)
        {
            if (newMessage.size() >= 480)
                throw std::runtime_error("Invalid message (too huge).");
            return std::make_shared<IPCMessage>(messageType, request, newMessage.c_str(), from);
        }

    }
}

#endif /* !IPCMESSAGE_HPP_ */
