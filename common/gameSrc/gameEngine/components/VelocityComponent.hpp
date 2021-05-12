/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** VelocityComponent
*/

#pragma once
#include "Component.hpp"

namespace rtype::common {
    class VelocityComponent : public rtype::common::Icomponent
    {
        public:
            VelocityComponent(
                int const &positionX = 0,
                int const &positionY = 0,
                bool const &inScreen = 0,
                unsigned short const &maxWidth = 1920,
                unsigned short const &maxHeight = 1080,
                bool const &controllable = false,
                bool const &fromLeftToRight = false
            ):
            saveVelocityX(positionX),
            saveVelocityY(positionY),
            stayInScreen(inScreen),
            maxWidthScreen(maxWidth),
            maxHeightScreen(maxHeight),
            isContrallable(controllable),
            isFromLeftToRight(fromLeftToRight)
            {};
            ~VelocityComponent() override = default;

            bool isContrallable;
            bool isFromLeftToRight;
            bool stayInScreen;
            unsigned short maxWidthScreen;
            unsigned short maxHeightScreen;
            int saveVelocityX;
            int saveVelocityY;
            int posX = 0;
            int posY = 0;
    };
}