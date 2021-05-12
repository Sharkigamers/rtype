/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <SFML/System.hpp>

#include "IClock.hpp"

namespace rtype {
    namespace common {

        /* Clock Class */

        class Clock : public IClock {
            public:
                Clock() = default;
                ~Clock() noexcept = default;

                float getElapsedTime() const noexcept
                {
                    return _clock.getElapsedTime().asSeconds();
                };

                float restartClock() noexcept
                {
                    return _clock.restart().asSeconds();
                };

            protected:
            private:
                sf::Clock _clock;
        };
    }
}

#endif /* !CLOCK_HPP_ */
