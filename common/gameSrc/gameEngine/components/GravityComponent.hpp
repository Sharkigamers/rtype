/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** GravityComponent
*/

#pragma once
#include "Component.hpp"

namespace rtype::common
{
    class GravityComponent : public Icomponent {
        public:
        int posX = 0;
        int posY = 0;
    };
} // namespace rtype::common
