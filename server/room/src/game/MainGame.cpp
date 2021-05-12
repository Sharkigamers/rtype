/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** MainGame
*/

#include "MainGameServ.hpp"

rtype::server::MainGame::MainGame(rtype::common::Manager &manager)
{
    this->_manager = manager;
}

rtype::server::MainGame::~MainGame()
{
}

void rtype::server::MainGame::initEntities() noexcept
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

void rtype::server::MainGame::initSystems() noexcept
{
    rtype::common::Manager _manager;
    rtype::common::SystemMusic _sysMusic;
    rtype::common::SystemMovement _sysMove;
    rtype::server::SystemControl _sysCtrl;
    rtype::common::SystemAnimation _sysAnim;
    rtype::server::SystemFire _sysFire;
    rtype::common::SystemDestroyObjs _sysDestroyProjectiles;
    rtype::common::SystemSpawnE _sysSpawnE;
    rtype::common::SystemCollider _sysCollider;
}

bool rtype::server::MainGame::displayGame(
    rtype::common::Clock &clock
) noexcept
 {
    if (clock.getElapsedTime() > 1 / 5) {
        EventGame();
        _sysCollider.update(_manager);
        _sysAnim.update(_manager);
        _sysDestroyProjectiles.update(_manager);
    }
}

void rtype::server::MainGame::playMusic() noexcept
{
    _sysMusic.update(_manager);
}

void rtype::server::MainGame::EventGame(
) noexcept
{
    _sysCtrl.update(_manager);
    _sysMove.update(_manager);
}

void rtype::server::MainGame::EventFire(
) noexcept
{
     _sysFire.update(_manager);
}
