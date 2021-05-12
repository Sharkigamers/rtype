/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** RoomIPC
*/

#include "RoomIPC.hpp"

#include <iostream>

rtype::room::RoomIPC::RoomIPC(const std::string &pipePath)
    : _pipePath(pipePath), _currentFd(0), isActive(true)
{
    setupIPC();
}

rtype::room::RoomIPC::~RoomIPC()
{
    isActive = false;
    _readMessageThread.join();
    std::remove(_pipePath.c_str());
}

void rtype::room::RoomIPC::setupIPC()
{
    _currentFd = open(_pipePath.c_str(), O_RDWR);

    if (_currentFd == -1) {
        isActive = false;
        throw std::runtime_error("Error while opening server Named pipe.");
    }
    _readMessageThread = std::thread([this]() {
        readMessageLoop();
    });
}

void rtype::room::RoomIPC::readMessageLoop()
{
    rtype::room::IPCMessage currentMessage;

    while (isActive) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        if (read(_currentFd, &currentMessage, sizeof(IPCMessage)) == -1) {
            isActive = false;
            break;
        }
        _globalMutex.lock();
        if (currentMessage.from != getpid())
            _messageQueue.push_back(std::make_shared<IPCMessage>(currentMessage));
        _globalMutex.unlock();
    }
}

bool rtype::room::RoomIPC::writeMessage(const std::shared_ptr<rtype::room::IPCMessage> &message)
{
    if (isActive == false || _currentFd == -1)
        throw std::runtime_error("Error while opening server Named pipe.");
    _globalMutex.lock();
    if (write(_currentFd, static_cast<void *>(message.get()), sizeof(IPCMessage)) == -1) {
        throw std::runtime_error("Error while sending a message to server.");
    }
    _globalMutex.unlock();
    return true;
}