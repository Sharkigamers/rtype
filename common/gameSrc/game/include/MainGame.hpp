/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** MainGame
*/

#ifndef MAINGAME_HPP_
#define MAINGAME_HPP_


#include <map>
#include <array>

#include "Music.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Parallax.hpp"
#include "Projectiles.hpp"
#include "PowerUp.hpp"
#include "SpawnEnemy.hpp"

#include "OpenConfigFile.hpp"

#include "Manager.hpp"
#include "Window.hpp"
#include "Clock.hpp"
#include "Types.hpp"
#include "Event.hpp"

#include "MusicComponent.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "ButtonComponent.hpp"
#include "TextComponent.hpp"
#include "SpawnComponent.hpp"

#include "SystemRenderText.hpp"
#include "SystemMusic.hpp"
#include "SystemRender.hpp"
#include "SystemClick.hpp"
#include "SystemMovement.hpp"
#include "SystemControl.hpp"
#include "SystemAnimation.hpp"
#include "SystemFire.hpp"
#include "SystemDestroyObjs.hpp"
#include "SystemCollider.hpp"
#include "SystemSpawnE.hpp"

#include "TcpClient.hpp"

namespace rtype::common {
    class MainGame {
        static const std::string CONFIG_BACKGROUND() { return "./client/assets/config/background/Background.json"; };
        static const std::string CONFIG_MUSIC_GAME() { return "./client/assets/config/music/MusicGame.json"; };

        static const std::string CONFIG_PLAYER() { return "./client/assets/config/player/Player.json"; };
        static const std::string CONFIG_SHOT() { return "./client/assets/config/projectiles/playerShot1.json"; };

        static const std::string CONFIG_MONSTER() { return "./client/assets/config/monster/monster1.json"; }

        static const std::string CONFIG_LVL1() { return "./client/assets/config/level/level1.json"; }

        public:
            MainGame(rtype::common::Manager &);
            ~MainGame();
            void initEntities() noexcept;
            void initSystems() noexcept;

            void initParallax(std::map<std::string, std::string> params) noexcept;

            void EventGame(rtype::common::TcpClient &, rtype::common::Event &) noexcept;
            void EventFire(rtype::common::TcpClient &, rtype::common::Event &) noexcept;

            bool displayGame(rtype::common::Window &, rtype::common::TcpClient &, rtype::common::Event &, rtype::common::Clock &) noexcept;

            void playMusic() noexcept;

        protected:
        private:
            rtype::common::Manager _manager;
            rtype::common::SystemRender _sysRender;
            rtype::common::SystemMusic _sysMusic;
            rtype::common::SystemRenderText _sysTxt;
            rtype::common::SystemMovement _sysMove;
            rtype::common::SystemControl _sysCtrl;
            rtype::common::SystemAnimation _sysAnim;
            rtype::common::SystemFire _sysFire;
            rtype::common::SystemDestroyObjs _sysDestroyProjectiles;
            rtype::common::SystemCollider _sysCollider;
            rtype::common::SystemSpawnE _sysSpawnE;

    };
}

#endif /* !MAINGAME_HPP_ */
