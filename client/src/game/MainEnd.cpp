/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** MainEnd
*/

#include "MainEnd.hpp"

rtype::client::MainEnd::MainEnd(rtype::common::Manager &manager, std::string const &endStatus)
{
    _manager = manager;
    _endStatus = endStatus;
}

rtype::client::MainEnd::~MainEnd()
{
}

void rtype::client::MainEnd::initEntities() noexcept
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
        rtype::common::OpenConfigFile(CONFIG_MENU_BUTTON()).getData(),
        rtype::common::BUTTON_PLAY,
        _manager
    );
    rtype::common::Button::initButtons(
        rtype::common::OpenConfigFile(CONFIG_MENUQUIT_BUTTON()).getData(),
        rtype::common::BUTTON_SETTINGS,
        _manager
    );

    rtype::common::CText::initCText (
        rtype::common::OpenConfigFile(CONFIG_RESULT_TEXT()).getData(),
        _manager,
        _endStatus
    );
}

void rtype::client::MainEnd::removeEntitiesBtsEnd() noexcept
{
    auto entities = _manager.getEntitiesList();
    auto living = _manager.getLivingEntities();
    for (auto x:living) {
        if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_BUTTON))) {
            _manager.removeEntity(x);
        }
    }
}

void rtype::client::MainEnd::removeEntitiesEnd() noexcept
{
    auto entities = _manager.getEntitiesList();
    auto living = _manager.getLivingEntities();
    for (auto x:living) {
        _manager.removeEntity(x);
    }
}

bool rtype::client::MainEnd::displayEnd(
    rtype::common::Window &window,
    rtype::client::TcpClient &client,
    rtype::common::Event &event
) noexcept
{
    _sysIBtn.update(_manager, event);
    _sysRender.update(_manager, window);
    _sysTxt.update(_manager, window);
}

bool rtype::client::MainEnd::EventEnd(
    rtype::common::Window &window,
    rtype::client::TcpClient &client,
    rtype::common::Event &event
) noexcept
{
    if (_sysClick.update(_manager, event, "rr") == button::menu) {
        std::cout << "menu" << std::endl;
        removeEntitiesBtsEnd();
        _sysStopMusic.update(_manager);
        return false;
    } else if (_sysClick.update(_manager, event, "''") == button::quit) {
        std::cout << "quit" << std::endl;
        window.closeWindow();
    }

    return true;
}
