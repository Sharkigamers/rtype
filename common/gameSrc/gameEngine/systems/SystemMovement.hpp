/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SystemMovement
*/

#ifndef SYSTEMMOVEMENT_HPP_
#define SYSTEMMOVEMENT_HPP_

#include "Systems.hpp"
#include "Manager.hpp"
#include "VelocityComponent.hpp"
#include "PositionComponent.hpp"

#include "Event.hpp"

namespace rtype::common  {
    class SystemMovement : Isystem {
        public:
            SystemMovement() = default;
            ~SystemMovement() override = default;

            void update(rtype::common ::Manager &manager) {
            auto entities = manager.getEntitiesList();
            auto living = manager.getLivingEntities();

            for (auto x:living) {
                if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_MVM))) {
                    auto velocity = manager.getComponent<VelocityComponent>(x);
                    auto position = manager.getComponent<PositionComponent>(x);

                    if (velocity->stayInScreen) {
                        unsigned short newPosX = position->posX + velocity->posX;
                        unsigned short newPosY = position->posY + velocity->posY;
                        if (newPosX < velocity->maxWidthScreen && newPosX > 0)
                            position->posX += velocity->posX;
                        if (newPosY < velocity->maxHeightScreen && newPosY > 0)
                            position->posY += velocity->posY;
                    } else {
                        moveMonster(velocity, position);
                    }
                }
            }
        }

        void moveMonster(VelocityComponent *velocity, PositionComponent *position) 
        {
            position->posX -= velocity->saveVelocityX;
            if (position->posY < 800 && !isDown) {
                position->posY += velocity->saveVelocityY;
            }
            else if (position->posY >= 800) {
                isDown = true;
            }
            if (isDown) {
                position->posY -= velocity->saveVelocityY;
            }
            if (position->posY <= 100 && isDown) {
                isDown = false;
            }
        }
    };
}

#endif /* !SYSTEMMOVEMENT_HPP_ */
