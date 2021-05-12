/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Room
*/

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <string>
#include <map>
#include <chrono>

#include "Cuuid.hpp"
#include "UdpServer.hpp"
#include "RoomIPC.hpp"
#include "SignalHandler.hpp"
#include "Imonster.hpp"

#include "MainGameServ.hpp"

namespace rtype {
    namespace room {
        class RoomInfo {
            public:
                RoomInfo(const rtype::common::Cuuid &id, const std::string &path, pid_t pid, uint16_t port) 
                    : _id(id), _path(path), _pid(pid), _port(port), _nbPlayers(0)
                {}

                ~RoomInfo() {}

                RoomInfo(const RoomInfo &other)
                {
                    if (&other != this) {
                        _id = other._id;
                        _path = other._path;
                        _pid = other._pid;
                        _port = other._port;
                    }
                }

                RoomInfo &operator=(const RoomInfo &other)
                {
                    if (&other != this) {
                        _id = other._id;
                        _path = other._path;
                        _pid = other._pid;
                        _port = other._port;
                    }
                    return *this;
                }

                bool operator==(const rtype::common::Cuuid &other)
                {
                    return Id() == other;
                }

                bool operator==(const RoomInfo &other)
                {
                    return Id() == other.Id();
                }

                bool operator==(const pid_t pid)
                {
                    return Pid() == pid;
                }

                rtype::common::Cuuid Id() const { return _id; }
                void Id(const rtype::common::Cuuid &newId) { _id = newId; }

                std::string Path() const { return _path; }
                void Path(const std::string newPath) { _path = newPath; }

                pid_t Pid() const { return _pid; }
                void Pid(const pid_t newId) { _pid = newId; }

                uint16_t Port() const { return _port; }
                void Port(const uint16_t newId) { _port = newId; }

                uint16_t nbPlayers() const { return _nbPlayers; }
                void nbPlayers(const uint16_t newId) { _nbPlayers = newId; }

            private:
                rtype::common::Cuuid _id;
                std::string _path;
                pid_t _pid;
                uint16_t _port;
                uint8_t _nbPlayers;
        };
        
        class Room {
            public:
                explicit Room(uint16_t portToUse, const std::string &pipePath, const rtype::common::Cuuid &id, const std::vector<rtype::API::Imonster*> &lstMonster);
                Room() = delete;
                ~Room();

            public:
                int run();

                void onGetStatusMessage();

            private:
                std::unique_ptr<rtype::room::RoomIPC> _roomIPC;
                std::unique_ptr<std::thread> _gameThread;
                bool _gameStarted = false;
                uint16_t _port;
                rtype::common::Cuuid _id;
                rtype::utils::SignalHandler _signalHandler;
                uint8_t nbPlayers = 0;
                
            private:
                std::thread _writeThread;
                std::thread _readThread;
                std::mutex _globalMutex;
                rtype::server::UdpServer _udpServer;

            private:
                void startGame()
                {
                    _mainGame.initEntities();
                    _mainGame.initSystems();
                    
                    rtype::common::Clock clock;
                    while (1) {
                        if (_udpServer.hasNewMessage()) {
                            std::pair<boost::asio::ip::udp::endpoint, std::shared_ptr<rtype::protocol::RoomMessage> > lastMessage = _udpServer.getLastMessage();

                            if (lastMessage.second->getType() == rtype::protocol::messageType::JOIN_ROOM) {
                                lstPlayer.push_back(std::make_pair<boost::asio::ip::udp::endpoint, uint32_t>(std::move(lastMessage.first), rtype::common::Player::initPlayer(rtype::common::OpenConfigFile(rtype::server::MainGame::CONFIG_MUSIC_GAME()).getData(), _gameManager)));
                            }
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                        _globalMutex.lock();
                        _mainGame.displayGame(clock);
                        _globalMutex.unlock();
                    }
                }

                std::vector<std::pair<std::string, std::pair<uint16_t, uint16_t> > > getEntitiesInfo()
                {
                    return _gameManager.getEntitiesInfo();
                }

                bool gameStarted()
                {
                    if (_gameStarted == false && _udpServer.nbClients() > 0) {
                        _gameStarted = true;
                        return true;
                    }
                    return _gameStarted;
                }

            private:
                rtype::common::Manager _gameManager;
                rtype::server::MainGame _mainGame;
                std::vector<rtype::API::Imonster*> _lstMonster;
                std::vector<std::pair<boost::asio::ip::udp::endpoint, uint32_t> > lstPlayer;
        };

    }
}

#endif /* !ROOM_HPP_ */
