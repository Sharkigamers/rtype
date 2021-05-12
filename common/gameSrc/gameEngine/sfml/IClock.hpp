/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** IClock
*/

#ifndef ICLOCK_HPP_
#define ICLOCK_HPP_

namespace rtype {
    namespace common {

        /* Interface for Clock Class */

        class IClock {
            public:
                virtual ~IClock() = default;

                virtual float getElapsedTime() const noexcept = 0;

                virtual float restartClock() noexcept = 0;

            protected:
            private:
        };
    }
}

#endif /* !ICLOCK_HPP_ */
