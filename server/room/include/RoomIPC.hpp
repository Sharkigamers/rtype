/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** RoomIPC
*/

#ifndef ROOMIPC_HPP_
#define ROOMIPC_HPP_

#include <string>
#include <thread>
#include <mutex>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "IPCMessage.hpp"

namespace rtype {
    namespace room {
        class RoomIPC {
            public:
                RoomIPC(const std::string &pipePath);
                ~RoomIPC();

                bool hasNewMessage() const { return !_messageQueue.empty(); }

                std::shared_ptr<rtype::room::IPCMessage> getLastMessage()
                {
                    std::shared_ptr<rtype::room::IPCMessage> lastMessage = _messageQueue.front();

                    _messageQueue.erase(_messageQueue.begin());
                    return lastMessage;
                }

                bool writeMessage(const std::shared_ptr<rtype::room::IPCMessage> &message);

                bool getIsActive() const noexcept { return isActive; }

            private:
                void setupIPC();
                void readMessageLoop();
            private:
                std::thread _readMessageThread;
                std::mutex _globalMutex;
                std::vector<std::shared_ptr<rtype::room::IPCMessage> > _messageQueue;
                std::string _pipePath;
                int _currentFd;
                bool isActive;
        };

    }
}

#endif /* !ROOMIPC_HPP_ */
