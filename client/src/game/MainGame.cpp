/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** MainGame
*/

#include "MainGame.hpp"

rtype::client::MainGame::MainGame(rtype::common::Manager &manager)
{
    this->_manager = manager;
}

rtype::client::MainGame::~MainGame()
{
}

void rtype::client::MainGame::initEntities() noexcept
{
    rtype::common::Music::initMusic(
        rtype::common::OpenConfigFile(CONFIG_MUSIC_GAME()).getData(),
        _manager
    );

   rtype::common::Parallax::initParallax(
        rtype::common::OpenConfigFile(CONFIG_BACKGROUND()).getData(),
        _manager
    );

    rtype::common::Player::initPlayer(
        rtype::common::OpenConfigFile(CONFIG_PLAYER()).getData(),
        _manager
    );

    rtype::common::Monster::initMonster(
        rtype::common::OpenConfigFile(CONFIG_MONSTER()).getData(),
        _manager
    );
    rtype::common::SpawnEnemy::initSpawn(
        rtype::common::OpenConfigFile(CONFIG_LVL1()).getData(),
        _manager
    );

    // rtype::common::Projectiles::initProjectiles(
    //     rtype::common::OpenConfigFile(CONFIG_SHOT()).getData(),
    //     _manager
    // );
}

void rtype::client::MainGame::initSystems() noexcept
{
    rtype::common::Manager _manager;
    rtype::common::SystemRender _sysRender;
    rtype::common::SystemMusic _sysMusic;
    rtype::common::SystemRenderText _sysTxt;
    rtype::common::SystemMovement _sysMove;
    rtype::common::SystemControl _sysCtrl;
    rtype::common::SystemAnimation _sysAnim;
    rtype::common::SystemFire _sysFire;
    rtype::common::SystemDestroyObjs _sysDestroyProjectiles;
    rtype::common::SystemSpawnE _sysSpawnE;
    rtype::common::SystemCollider _sysCollider;
}

bool rtype::client::MainGame::displayGame(
    rtype::common::Window &window,
    rtype::client::TcpClient &client,
    rtype::common::Event &event,
    rtype::common::Clock &clock
) noexcept
 {

    std::thread threadSpawnE = std::thread([this](){
        _sysSpawnE.update(_manager);
    });

    std::thread threadCollider = std::thread([this](){
        _sysCollider.update(_manager);
    });
    
    std::thread threadEvent = std::thread([this, &event, &client](){
        EventGame(client, event);
    });

    std::thread threadAnim = std::thread([this](){
        _sysAnim.update(_manager);
    });

    std::thread threadDestroy = std::thread([this](){
       _sysDestroyProjectiles.update(_manager);
    });

    std::thread threadRender = std::thread([this, &window](){
       _sysRender.update(_manager, window);
    });

    if (clock.getElapsedTime() > 1 / 5) {
        // EventGame(client, event);
        // _sysCollider.update(_manager);
        // _sysAnim.update(_manager);
        // _sysDestroyProjectiles.update(_manager);
        threadEvent.join();
        threadSpawnE.join();
        threadCollider.join();
        threadAnim.join();
        threadDestroy.join();
        clock.restartClock();
    }
    threadRender.join();
}

void rtype::client::MainGame::playMusic() noexcept
{
    _sysMusic.update(_manager);
}

void rtype::client::MainGame::EventGame(
    rtype::client::TcpClient &client,
    rtype::common::Event &event
) noexcept
{
    _sysCtrl.update(_manager, event);
    _sysMove.update(_manager);
}

void rtype::client::MainGame::EventFire(
    rtype::client::TcpClient &client,
    rtype::common::Event &event
) noexcept
{
     _sysFire.update(_manager, event);
}
