/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** ClockGame
*/

#ifndef CLOCKGAME_HPP_
#define CLOCKGAME_HPP_

#include <map>
#include <string>

#include "OpenConfigFile.hpp"

#include "Manager.hpp"

#include "ClockComponent.hpp"

#include "SystemMusic.hpp"

namespace rtype::common {
    class ClockGame {
        public:

            static void initClock(
                std::map<std::string, std::string> params,
                rtype::common::Manager &manager
            ) noexcept
            {
                std::uint32_t clock = manager.createEntity();

                manager.addComponent<rtype::common::ClockComponent>(
                    clock,
                    COMP_CLOCK
                );
            }

        protected:
        private:
    };
}

#endif /* !CLOCKGAME_HPP_ */
