/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** ClockComponent
*/

#ifndef CLOCKCOMPONENT_HPP_
#define CLOCKCOMPONENT_HPP_

#include "Component.hpp"

#include "Clock.hpp"

namespace rtype::common {
    class ClockComponent : public rtype::common::Icomponent
    {
        public:
            ClockComponent() {};
            ~ClockComponent() override = default; 

            rtype::common::Clock clock;
    };
}
#endif /* !CLOCKCOMPONENT_HPP_ */
