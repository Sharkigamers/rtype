/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Room
*/

#include "Room.hpp"

rtype::room::Room::Room(uint16_t portToUse, const std::string &pipePath, const rtype::common::Cuuid &id, const std::vector<rtype::API::Imonster*> &lstMonster)
    : _port(portToUse), _id(id), _signalHandler(), _udpServer("127.0.0.1", portToUse), _gameManager(), _lstMonster(lstMonster), _mainGame(_gameManager)
{
    _roomIPC = std::make_unique<rtype::room::RoomIPC>(pipePath);
    _writeThread = std::thread([this]() {
        _udpServer.startWrite();
    });

    _readThread = std::thread([this]() {
        _udpServer.startReceive();
    });
}

rtype::room::Room::~Room()
{
    _udpServer.stop();
    _writeThread.join();
    _readThread.join();
}

void rtype::room::Room::onGetStatusMessage()
{
    const std::map<std::string, std::string> objects = {
        {"PLAYERS", std::to_string(nbPlayers)}
    };

    std::shared_ptr<rtype::room::IPCMessage> message = createIPCMessage(rtype::room::IPCMessageType::ROOM_STATUS, 0, rtype::common::JsonUtility::mapToJson(objects), getpid());
    _roomIPC->writeMessage(message);
}

int rtype::room::Room::run()
{
    std::cout << "Room " << _id.getUuidString() << " now up and running.\n";
    auto start = std::chrono::system_clock::now();
    while (_roomIPC->getIsActive()) {
        if (gameStarted() == true && _gameThread.get() == nullptr) {
            _gameThread = std::make_unique<std::thread>([this]() {
                startGame();
            });
        }
        if (nbPlayers == 0) {
            auto time = std::chrono::system_clock::now();
            std::chrono::duration<double> seconds = time - start;

            if (seconds.count() > 30)
                break;
        } else {
            start = std::chrono::system_clock::now();
        }
        if (_signalHandler.hasExited()) break;
        if (_roomIPC->hasNewMessage()) {
            std::shared_ptr<rtype::room::IPCMessage> message = _roomIPC->getLastMessage();

            if (message->type == IPCMessageType::ROOM_STATUS)
                onGetStatusMessage();
            
        }
    }
    std::cout << "Room " << _id.getUuidString() << " now shutting down.\n";

    
    return 0;
}