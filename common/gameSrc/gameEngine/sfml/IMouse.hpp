/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** IMouse
*/

#ifndef IMOUSE_HPP_
#define IMOUSE_HPP_

#include <utility>

namespace rtype {
    namespace common {

        /* Interface for Mouse Class */

        class IMouse {
            public:
                ~IMouse() = default;

                virtual bool buttonMousePressed(char const &button) noexcept = 0;

                virtual void setMousePosition(float const &x, float const &y) noexcept = 0;

                virtual std::pair<float, float>getMousePosition() noexcept = 0;

            protected:
            private:
        };
    }
}

#endif /* !IMOUSE_HPP_ */
