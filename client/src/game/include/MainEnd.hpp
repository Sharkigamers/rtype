/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** MainEnd
*/

#ifndef MAINEND_HPP_
#define MAINEND_HPP_

#include <map>
#include <array>

#include "Background.hpp"
#include "Button.hpp"
#include "Music.hpp"

#include "OpenConfigFile.hpp"

#include "Manager.hpp"
#include "Window.hpp"
#include "Clock.hpp"
#include "Types.hpp"
#include "Event.hpp"
#include "CText.hpp"

#include "MusicComponent.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "ButtonComponent.hpp"
#include "TextComponent.hpp"

#include "SystemRenderText.hpp"
#include "SystemMusic.hpp"
#include "SystemStopMusic.hpp"
#include "SystemRender.hpp"
#include "SystemClick.hpp"
#include "SystemInteractifBtn.hpp"

#include "TcpClient.hpp"

namespace rtype::client {
    class MainEnd {

        static const std::string CONFIG_BACKGROUND() { return "./client/assets/config/background/Background.json"; };

        static const std::string CONFIG_MUSIC() { return "./client/assets/config/music/Music.json"; };

        static const std::string CONFIG_MENU_BUTTON() { return "./client/assets/config/button/ButtonMenu.json"; };
        static const std::string CONFIG_MENUQUIT_BUTTON() { return "./client/assets/config/button/ButtonMenuQuit.json"; };

        static const std::string CONFIG_RESULT_TEXT() { return "./client/assets/config/text/ResultEnd.json"; };

        enum button {
            menu = 0,
            quit = 1
        };

        public:
            MainEnd(rtype::common::Manager &manager, std::string const &endStatus);
            ~MainEnd();

            void initEntities() noexcept;
            void removeEntitiesBtsEnd() noexcept;
            void removeEntitiesEnd() noexcept;

            bool displayEnd(rtype::common::Window &, rtype::client::TcpClient &, rtype::common::Event &) noexcept;
            
            bool EventEnd(rtype::common::Window &, rtype::client::TcpClient &, rtype::common::Event &) noexcept;

            void playMusic() noexcept { _sysMusic.update(_manager); };

        protected:
        private:
            rtype::common::Manager _manager;
            rtype::common::SystemRender _sysRender;
            rtype::common::SystemClick _sysClick;
            rtype::common::SystemMusic _sysMusic;
            rtype::common::SystemStopMusic _sysStopMusic;
            rtype::common::SystemRenderText _sysTxt;
            rtype::common::SystemInteractifBtn _sysIBtn;

            std::string _endStatus;
    };
}

#endif /* !MAINEND_HPP_ */
