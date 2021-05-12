/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** PowerUpComponent
*/

#pragma once
#include "Component.hpp"

namespace rtype::common {
    class PowerUpComponent : public rtype::common::Icomponent {
        public:
            int power = 0;
    };
}
