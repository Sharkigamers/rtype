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

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "Background.hpp"
#include "Button.hpp"
#include "Music.hpp"
#include "CText.hpp"
#include "ButtonListRoom.hpp"

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
#include "SystemEnterRoom.hpp"

#include "TcpClient.hpp"
#include "UdpClientNetwork.hpp"

namespace rtype::client {
    class MainMenu {

        static const std::string CONFIG_BACKGROUND() { return "./client/assets/config/background/Background.json"; };

        static const std::string CONFIG_MUSIC() { return "./client/assets/config/music/Music.json"; };

        static const std::string CONFIG_PLAY_BUTTON() { return "./client/assets/config/button/ButtonPlay.json"; };
        static const std::string CONFIG_SETTINGS_BUTTON() { return "./client/assets/config/button/ButtonSettings.json"; };
        static const std::string CONFIG_QUIT_BUTTON() { return "./client/assets/config/button/ButtonQuit.json"; };
        static const std::string CONFIG_JOIN_ROOM_BUTTON() { return "./client/assets/config/button/ButtonJoinRoom.json"; };
        static const std::string CONFIG_CREATE_ROOM_BUTTON() { return "./client/assets/config/button/ButtonCreateRoom.json"; };
        static const std::string CONFIG_LIST_ROOM_BUTTON() { return "./client/assets/config/button/ButtonListRoom.json"; };
        static const std::string CONFIG_REFRESH_BUTTON() { return "./client/assets/config/button/ButtonRefresh.json"; };
        static const std::string CONFIG_RETURN_BUTTON() { return "./client/assets/config/button/ButtonReturn.json"; };

        static const std::string CONFIG_TITLE_1() { return "./client/assets/config/text/Title1.json"; };
        static const std::string CONFIG_TITLE_2() { return "./client/assets/config/text/Title2.json"; };
        static const std::string CONFIG_TITLE_LIST_ROOM() { return "./client/assets/config/text/ListRoom.json"; };

        public:
            MainMenu(rtype::common::Manager &);
            ~MainMenu();

            void initEntities() noexcept;
            void removeEntitiesBtnMenu() noexcept;
            void removeEntitiesMenu() noexcept;
            void removeEntitiesText() noexcept;

            void initSystems() noexcept;

            void initRoomMenu(rtype::client::TcpClient &, rtype::common::Event &) noexcept;

            void initJoinRoomMenu(rtype::client::TcpClient &, rtype::common::Event &, std::vector<std::pair<int, int>> &) noexcept;

            void refreshRoomMenu(rtype::client::TcpClient &, rtype::common::Event &, std::vector<std::pair<int, int>> &) noexcept;

            bool displayMenu(rtype::common::Window &, rtype::client::TcpClient &, rtype::common::Event &) noexcept;

            void checkRoom(rtype::client::TcpClient &client, std::vector<std::pair<int, int>> &dataRoom) noexcept;
            
            bool EventMenu(rtype::common::Window &, rtype::client::TcpClient &, rtype::common::Event &, std::vector<std::pair<int, int>> &, const std::string &) noexcept;

            void playMusic() noexcept;

        protected:
        private:
            rtype::common::Manager _manager;
            rtype::common::SystemRender _sysRender;
            rtype::common::SystemClick _sysClick;
            rtype::common::SystemMusic _sysMusic;
            rtype::common::SystemStopMusic _sysStopMusic;
            rtype::common::SystemRenderText _sysTxt;
            rtype::common::SystemInteractifBtn _sysIBtn;
            rtype::common::SystemEnterRoom _sysRoom;
    };
}

#endif /* !MAINMENU_HPP_ */
