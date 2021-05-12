/*
** EPITECH PROJECT, 2020
** MainMenu
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

rtype::client::MainMenu::MainMenu(rtype::common::Manager &manager)
{
    this->_manager = manager;
    initEntities();
    initSystems();
}

rtype::client::MainMenu::~MainMenu()
{
}

void rtype::client::MainMenu::initEntities() noexcept
{
    rtype::common::Music::initMusic(
        rtype::common::OpenConfigFile(CONFIG_MUSIC()).getData(),
        _manager
    );

    rtype::common::Background::initBackground(
        rtype::common::OpenConfigFile(CONFIG_BACKGROUND()).getData(),
        _manager
    );

    rtype::common::Button::initButtons(
        rtype::common::OpenConfigFile(CONFIG_PLAY_BUTTON()).getData(),
        rtype::common::BUTTON_PLAY,
        _manager
    );
    rtype::common::Button::initButtons(rtype::common::OpenConfigFile(
        CONFIG_SETTINGS_BUTTON()).getData(),
        rtype::common::BUTTON_SETTINGS,
        _manager
    );
    rtype::common::Button::initButtons(
        rtype::common::OpenConfigFile(CONFIG_QUIT_BUTTON()).getData(),
        rtype::common::BUTTON_QUIT,
        _manager
    );
}

void rtype::client::MainMenu::refreshRoomMenu(
    rtype::client::TcpClient &client,
    rtype::common::Event &event,
     std::vector<std::pair<int, int>> &dataRoom
) noexcept
{
    size_t posX = 750;
    size_t posY = 105;
    for(unsigned int i=0; i < dataRoom.size(); ++i) {
        rtype::common::ButtonListRoom::initButtonListRoom(
            rtype::common::OpenConfigFile(CONFIG_LIST_ROOM_BUTTON()).getData(),
            rtype::common::BUTTON_ENTER_ROOM,
            _manager,
            dataRoom[i].first,
            dataRoom[i].second,
            i,
            posX,
            posY
        );
        posY += 200;
    }
}

void rtype::client::MainMenu::initJoinRoomMenu(
    rtype::client::TcpClient &client,
    rtype::common::Event &event,
     std::vector<std::pair<int, int>> &dataRoom
) noexcept
{
    removeEntitiesBtnMenu();
    rtype::common::CText::initCText(
        rtype::common::OpenConfigFile(CONFIG_TITLE_LIST_ROOM()).getData(),
        _manager
    );
    rtype::common::Button::initButtons(
        rtype::common::OpenConfigFile(CONFIG_REFRESH_BUTTON()).getData(),
        rtype::common::BUTTON_REFRESH,
        _manager
    );
    rtype::common::Button::initButtons(
            rtype::common::OpenConfigFile(CONFIG_RETURN_BUTTON()).getData(),
            rtype::common::BUTTON_RETURN,
            _manager
    );
}

void rtype::client::MainMenu::initRoomMenu(
    rtype::client::TcpClient &client,
    rtype::common::Event &event
) noexcept
{
    rtype::common::CText::initCText(
        rtype::common::OpenConfigFile(CONFIG_TITLE_1()).getData(),
        _manager
    );
    rtype::common::CText::initCText(
        rtype::common::OpenConfigFile(CONFIG_TITLE_2()).getData(),
        _manager
    );
    rtype::common::Button::initButtons(rtype::common::OpenConfigFile(
        CONFIG_CREATE_ROOM_BUTTON()).getData(),
        rtype::common::BUTTON_CREATE_ROOM,
        _manager
    );
    rtype::common::Button::initButtons(
        rtype::common::OpenConfigFile(CONFIG_JOIN_ROOM_BUTTON()).getData(),
        rtype::common::BUTTON_LIST_ROOM,
        _manager
    );
}

void rtype::client::MainMenu::initSystems() noexcept
{
    rtype::common::SystemRender _sysRender;
    rtype::common::SystemClick _sysClick;
    rtype::common::SystemMusic _sysMusic;
    rtype::common::SystemStopMusic _sysStopMusic;
    rtype::common::SystemRenderText _sysTxt;
    rtype::common::SystemInteractifBtn _sysIBtn;
}

void rtype::client::MainMenu::removeEntitiesBtnMenu() noexcept
{
    auto entities = _manager.getEntitiesList();
    auto living = _manager.getLivingEntities();
    for (auto x:living) {
        if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_BUTTON))) {
            _manager.removeEntity(x);
        }
    }
}

void rtype::client::MainMenu::removeEntitiesText() noexcept
{
    auto entities = _manager.getEntitiesList();
    auto living = _manager.getLivingEntities();
    for (auto x:living) {
        if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_RDR_TXT))) {
            _manager.removeEntity(x);
        }
    }
}

void rtype::client::MainMenu::removeEntitiesMenu() noexcept
{
    auto entities = _manager.getEntitiesList();
    auto living = _manager.getLivingEntities();
    for (auto x:living) {
        _manager.removeEntity(x);
    }
}

void rtype::client::MainMenu::checkRoom(rtype::client::TcpClient &client, std::vector<std::pair<int, int>> &dataRoom) noexcept
{
    if (client.hasNewMessage() == true) {
        std::shared_ptr<rtype::protocol::Message> message = client.getLastMessage();
        std::map<std::string, std::string>body = message->parseBody();
        std::vector<std::string> data = rtype::protocol::unformatData(body["DATA"]);
        //rtype::client::UdpClientNetwork clientUdp(ip, std::stoi(data[0]));
        bool checkRoom = false;
        for(unsigned int i=0; i < dataRoom.size(); ++i)
        {
            if (dataRoom[i].first == std::stoi(data[0]))
                checkRoom = true;
        }
        if (checkRoom == false)
        dataRoom.push_back(std::make_pair(std::stoi(data[0]), std::stoi(data[1])));
    }
}


bool rtype::client::MainMenu::EventMenu(
    rtype::common::Window &window,
    rtype::client::TcpClient &client,
    rtype::common::Event &event,
    std::vector<std::pair<int, int>> &dataRoom,
    const std::string &ip
) noexcept
{
    switch(_sysClick.update(_manager, event, ip)) {
        case rtype::common::BUTTON_PLAY:
            removeEntitiesBtnMenu();
            initRoomMenu(client, event);
            return true;
        case rtype::common::BUTTON_SETTINGS:
            removeEntitiesBtnMenu();
            return true;
        case rtype::common::BUTTON_QUIT:
            window.closeWindow();
        case rtype::common::BUTTON_CREATE_ROOM:
            removeEntitiesBtnMenu();
            removeEntitiesText();
            _sysStopMusic.update(_manager);
            client.createRoom();
            usleep(1000);
            client.getRoom();
            usleep(1000);
            checkRoom(client, dataRoom);
            initJoinRoomMenu(client, event, dataRoom);
            return true;
        case rtype::common::BUTTON_LIST_ROOM:
            removeEntitiesText();
            removeEntitiesBtnMenu();
            initJoinRoomMenu(client, event, dataRoom);
            return true;
        case rtype::common::BUTTON_ENTER_ROOM:
            _sysStopMusic.update(_manager);
            return false;
        case rtype::common::BUTTON_REFRESH:
            refreshRoomMenu(client, event, dataRoom);
            return true;
        case rtype::common::BUTTON_RETURN:
            removeEntitiesText();
            removeEntitiesBtnMenu();
            initRoomMenu(client, event);
            return true;
        default:
          return true;
    }
}

void rtype::client::MainMenu::playMusic() noexcept
{
    _sysMusic.update(_manager);
}

bool rtype::client::MainMenu::displayMenu(
    rtype::common::Window &window,
    rtype::client::TcpClient &client,
    rtype::common::Event &event
) noexcept
{
    _sysIBtn.update(_manager, event);
    _sysRender.update(_manager, window);
    _sysTxt.update(_manager, window);
}
