/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** RoomManager
*/

#include "RoomManager.hpp"

rtype::room::RoomManager::RoomManager()
    : _isActive(true)
{
    _roomWatcherThread = std::thread([this]() {
        waitRoomLoop();
    });

    _roomReadThread = std::thread([this]() {
        readClientsLoop();
    });
}

rtype::room::RoomManager::~RoomManager()
{
    _isActive = false;
    _roomWatcherThread.join();
    _roomReadThread.join();
    
    for (const auto &x : _listRoom) {
        kill(x.Pid(), SIGINT);
        if (remove(x.Path().c_str()) == -1)
            perror("remove");
    }
}

void rtype::room::RoomManager::closeRoom(const rtype::room::RoomInfo &info)
{
    kill(info.Pid(), SIGINT);
    std::remove(info.Path().c_str());
    _listRoom.erase(std::find(_listRoom.begin(), _listRoom.end(), info));
}

void rtype::room::RoomManager::createRoom(uint16_t port, const std::vector<rtype::API::Imonster *> &monsters)
{
    RoomId newRoomId;
    rtype::common::Cuuid newId;
    std::string pipePath = "Room:" + newId.getUuidString();

    mkfifo(pipePath.data(), 0666);
    newRoomId = fork();
    if (newRoomId == -1)
        throw std::runtime_error("Error while creating a room process : " + std::string(strerror(errno)));
    if (newRoomId == 0) {
        Room newRoom(port, pipePath, newId, monsters);
        exit(newRoom.run());
    } else {
        _listRoom.emplace_back(newId, pipePath, newRoomId, port);
    }
}

void rtype::room::RoomManager::broadcast(const std::shared_ptr<rtype::room::IPCMessage> &message)
{
    for (const auto &x : _listRoom) {
        sendToRoom(x.Pid(), message);
    }
}

void rtype::room::RoomManager::sendToRoom(RoomId toSend, const std::shared_ptr<rtype::room::IPCMessage> &message)
{
    for (const auto &x : _listRoom) {
        if (x.Pid() == toSend) {
            _globalMutex.lock();
            int fd = open(x.Path().data(), O_WRONLY | O_NONBLOCK);

            if (write(fd, static_cast<void *>(message.get()), sizeof(rtype::room::IPCMessage)) == -1)
                if (errno != EAGAIN)
                    std::cerr << "Error writing a message to pipe.\n";
            close(fd);
            _globalMutex.unlock();
        }
    }
}

void rtype::room::RoomManager::updateRoomInfoFromMessage(const rtype::room::IPCMessage &message)
{
    for (auto &x : _listRoom) {
        if (x.Pid() == message.from) {
            const std::map<std::string, std::string> objects = rtype::common::JsonUtility::jsonToMap(message.message);
            uint8_t players;

            try
            {
                players = static_cast<uint8_t>(std::stoi(objects.at("PLAYERS")));
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            x.nbPlayers(players);
        }
    }
}

void rtype::room::RoomManager::readClientsLoop()
{
    rtype::room::IPCMessage currentMessage;

    while (_isActive) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        _globalMutex.lock();
        for (auto &x : _listRoom) {
            int fd = open(x.Path().c_str(), O_RDONLY | O_NONBLOCK);
            ssize_t dataSize;
            if (fd == -1) {
                // Mauvais fd = pipe non existant = pas de communication du coup on clos
                closeRoom(x);
                break;
            }
            if (dataSize = read(fd, &currentMessage, sizeof(IPCMessage)) == -1) {
                if (errno != EAGAIN) {
                    // Il y a eu une error de read, on la print.
                    std::cerr << "Error reading from pipe.\n";
                }
            } if (dataSize > 0) {
                // Si le message provient du server, on le renvoie dans le pipe
                if (currentMessage.from != getpid()) {
                    if (currentMessage.type == IPCMessageType::ROOM_STATUS) {
                        updateRoomInfoFromMessage(currentMessage);
                    } else
                        _messageQueue.push_back(std::make_shared<IPCMessage>(currentMessage));
                }
                else {
                    sendToRoom(currentMessage.from, std::make_shared<IPCMessage>(currentMessage));
                }
            }
            close(fd);
        }
        _globalMutex.unlock();
    }
}

void rtype::room::RoomManager::waitRoomLoop()
{
    RoomId IdError;
    int status;
    const std::shared_ptr<IPCMessage> statusMessage = createIPCMessage(IPCMessageType::ROOM_STATUS, 1, "", getpid());

    while (_isActive) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        broadcast(statusMessage);
        for (const auto &x : _listRoom) {
            IdError = waitpid(x.Pid(), &status, WNOHANG | WUNTRACED | WCONTINUED);
            if (IdError == 0) continue;
            if (IdError == -1) {
                perror("waitpid");
            }

            if (WIFEXITED(status)) {
                closeRoom(x);
                break;
            } if (WIFSIGNALED(status)) {
                closeRoom(x);
                break;
            }
        }
    }
}
