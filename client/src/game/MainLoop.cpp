/*
** EPITECH PROJECT, 2020
** MainLoop.cpp
** File description:
** MainLoop
*/

#include "MainLoop.hpp"
#include "TcpClient.hpp"
#include "LoadMonster.hpp"

rtype::client::MainLoop::MainLoop() : _mainWindow(), _manager()
{
}

rtype::client::MainLoop::~MainLoop()
{
}


void rtype::client::MainLoop::run(const std::string &ip)
{
    rtype::client::MainMenu menu(_manager);
    rtype::client::MainGame game(_manager);
    rtype::client::TcpClient client(ip, 42424);
    rtype::common::Clock clock;
    rtype::common::Clock clockRoom;
    bool changeScreen = true;
    std::vector<std::pair<int, int>> dataRoom;
    menu.playMusic();

    while (_mainWindow.isWindowOpen()) {
        rtype::common::Event myEvent;
        float timer = clockRoom.getElapsedTime();
        while (_mainWindow.pollEventFromRenderWindow(myEvent))
        {
            if (myEvent.isClosing() || myEvent.isEscapePressed()) {
                _mainWindow.closeWindow();
            }
            if (menu.EventMenu(_mainWindow, client, myEvent, dataRoom, ip) == false && changeScreen) {
                menu.removeEntitiesMenu();
                game.initEntities();
                game.initSystems();
                game.playMusic();
                _mainWindow.makeCursorVisible(false);
                changeScreen = false;
            } else
                game.EventFire(client, myEvent);
        }
        if (client.hasNewMessage() == true) {
            std::shared_ptr<rtype::protocol::Message> message = client.getLastMessage();
            std::map<std::string, std::string>body = message->parseBody();
            std::vector<std::string> data = rtype::protocol::unformatData(body["DATA"]);
            bool checkRoom = false;
            for(unsigned int i=0; i < dataRoom.size(); ++i)
            {
                if (dataRoom[i].first == std::stoi(data[0]))
                    checkRoom = true;
            }
            if (checkRoom == false)
            dataRoom.push_back(std::make_pair(std::stoi(data[0]), std::stoi(data[1])));
            }
            if (timer >= 1) {
                client.getRoom();
                clockRoom.restartClock();
            }
        //auto entitiesInfo = _manager.getEntitiesInfo();
        //for(auto lopes:entitiesInfo) {
        //    std::cout << "LOPES BIGGA BOOTY " << lopes.first << " " << lopes.second.first << " " << lopes.second.second << std::endl;
        //}

        // rtype::API::LoadMonster monsterLoader;

        // rtype::API::Imonster *putridLopes = monsterLoader.load("./monsters/PutridLopes/libPutridLopes.so");
        
        // std::cout << putridLopes->getPath() << std::endl;
    
        _mainWindow.clearWindow();
        if (changeScreen)
            menu.displayMenu(_mainWindow, client, myEvent);
        else {
            game.displayGame(_mainWindow, client, myEvent, clock);
        }
        _mainWindow.displayWindow();
    }
}
