/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SystemControl
*/

#pragma once
#include "Systems.hpp"
#include "Manager.hpp"
#include "VelocityComponent.hpp"

#include "Event.hpp"

static const unsigned short UP = 73;
static const unsigned short DOWN = 74;
static const unsigned short LEFT = 71;
static const unsigned short RIGHT = 72;

namespace rtype::common  {
    class SystemControl : Isystem {
        public:
            SystemControl() = default;
            ~SystemControl() override = default;

            void update(rtype::common ::Manager &manager, rtype::common ::Event &event) {
            auto entities = manager.getEntitiesList();
            auto living = manager.getLivingEntities();  

            for (auto x:living) {
                if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_CTRL))) {
                    auto velocity = manager.getComponent<VelocityComponent>(x);
                    if (velocity->isContrallable) {
                        if (event.isKeyPressed()) {
                            switch (event.eventKeyCode())
                            {
                            case LEFT :
                                velocity->posX = -velocity->saveVelocityX;
                                break;
                            case RIGHT :
                                velocity->posX = velocity->saveVelocityX;
                                break;
                            case UP :
                                velocity->posY = -velocity->saveVelocityY;
                                break;
                            case DOWN :
                                velocity->posY = velocity->saveVelocityY;
                                break;
                            default:
                                break;
                            }
                        } else {
                            velocity->posX = 0;
                            velocity->posY = 0;
                        }
                    } else {
                        if (velocity->isFromLeftToRight) {
                            velocity->posX = -velocity->saveVelocityX;
                        } else {
                            velocity->posX = +velocity->saveVelocityX;
                        }
                    }
                }
            }
        }
    };
}