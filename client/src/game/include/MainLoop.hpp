/*
** EPITECH PROJECT, 2020
** MainLoop
** File description:
** MainLoop
*/

#ifndef MAINLOOP_HPP_
#define MAINLOOP_HPP_

#include "Manager.hpp"
#include "Window.hpp"
#include "Clock.hpp"
#include "Types.hpp"

#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"

#include "SystemRender.hpp"
#include "SystemControl.hpp"

#include "MainMenu.hpp"
#include "MainGame.hpp"
#include <vector>

namespace rtype::client {
    class MainLoop {
        public:
            MainLoop();
            ~MainLoop();

            void run(const std::string &);

        protected:
        private:
              rtype::common::Window _mainWindow;
              rtype::common::Manager _manager;
    };
}

#endif /* !MAINLOOP_HPP_ */
