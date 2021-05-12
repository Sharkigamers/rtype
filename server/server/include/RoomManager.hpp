/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** RoomManager
*/

#ifndef ROOMMANAGER_HPP_
#define ROOMMANAGER_HPP_

#include <algorithm>
#include "JsonUtility.hpp"

#include "Room.hpp"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using RoomId = pid_t;

namespace rtype {
    namespace room {
        class RoomManager {
            public:
                RoomManager();
                ~RoomManager();

                void createRoom(uint16_t port, const std::vector<rtype::API::Imonster *> &monsters);
                void sendToRoom(RoomId toSend, const std::shared_ptr<rtype::room::IPCMessage> &message);
                
                void broadcast(const std::shared_ptr<rtype::room::IPCMessage> &message);
                std::vector<rtype::room::RoomInfo> getListRoomInfo() const
                {
                    return _listRoom;
                };
                
                std::vector<uint16_t> getListPort() const
                {
                    std::vector<uint16_t> ports;

                    ports.reserve(_listRoom.size());
                    for (const auto &x : _listRoom) {
                       ports.push_back(x.Port()); 
                    }
                    return ports;
                }
            private:
                void waitRoomLoop();
                void readClientsLoop();
                void updateRoomInfoFromMessage(const rtype::room::IPCMessage &);

                std::vector<std::shared_ptr<rtype::room::IPCMessage> > _messageQueue;
                std::thread _roomReadThread;
                void closeRoom(const rtype::room::RoomInfo &);
            public:
                bool hasNewMessage() const noexcept { return !_messageQueue.empty() ;}
                
                std::shared_ptr<rtype::room::IPCMessage> getLastMessage()
                {
                    std::shared_ptr<rtype::room::IPCMessage> lastMessage = _messageQueue.front();

                    _messageQueue.erase(_messageQueue.begin());
                    return lastMessage;
                }
            
            private:
                std::mutex _globalMutex;
                std::thread _roomWatcherThread;
                std::vector<rtype::room::RoomInfo> _listRoom;
                bool _isActive;
        };
        
    }
}

#endif /* !ROOMMANAGER_HPP_ */
