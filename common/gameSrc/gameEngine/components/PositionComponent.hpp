/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** PositionComponent
*/

#pragma once
#include "Component.hpp"

namespace rtype::common {
    class PositionComponent : public rtype::common::Icomponent
    {
        public:
            PositionComponent(int positionX = 0, int positionY = 0) : posX(positionX), posY(positionY) {};
            ~PositionComponent() override = default; 
            int posX = 0;
            int posY = 0;
    };
}