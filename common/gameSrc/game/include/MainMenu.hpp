/*
** EPITECH PROJECT, 2020
** MainMenu
** File description:
** MainMenu
*/

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

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

namespace rtype::common {
    class MainMenu {

        static const std::string CONFIG_BACKGROUND() { return "./client/assets/config/background/Background.json"; };

        static const std::string CONFIG_MUSIC() { return "./client/assets/config/music/Music.json"; };

        static const std::string CONFIG_PLAY_BUTTON() { return "./client/assets/config/button/ButtonPlay.json"; };
        static const std::string CONFIG_SETTINGS_BUTTON() { return "./client/assets/config/button/ButtonSettings.json"; };
        static const std::string CONFIG_QUIT_BUTTON() { return "./client/assets/config/button/ButtonQuit.json"; };

        public:
            MainMenu(rtype::common::Manager &);
            ~MainMenu();

            void initEntities() noexcept;
            void removeEntitiesBtnMenu() noexcept;
            void removeEntitiesMenu() noexcept;

            void initSystems() noexcept;

            bool displayMenu(rtype::common::Window &, rtype::common::TcpClient &, rtype::common::Event &) noexcept;
            
            bool EventMenu(rtype::common::Window &, rtype::common::TcpClient &, rtype::common::Event &) noexcept;

            button_type_t getBtnClick(rtype::common::Event &event) noexcept { return (_sysClick.update(_manager, event)); };

            void playMusic() noexcept;

            bool _check = false;

        protected:
        private:
            rtype::common::Manager _manager;
            rtype::common::SystemRender _sysRender;
            rtype::common::SystemClick _sysClick;
            rtype::common::SystemMusic _sysMusic;
            rtype::common::SystemStopMusic _sysStopMusic;
            rtype::common::SystemRenderText _sysTxt;
            rtype::common::SystemInteractifBtn _sysIBtn;
    };
}

#endif /* !MAINMENU_HPP_ */
