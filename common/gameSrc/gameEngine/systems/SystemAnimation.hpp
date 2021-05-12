/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SystemAnimation
*/

#ifndef SYSTEMANIMATION_HPP_
#define SYSTEMANIMATION_HPP_

#include "Systems.hpp"
#include "Manager.hpp"
#include "Types.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "ClockComponent.hpp"
#include "AnimationComponent.hpp"

#include "Window.hpp"

namespace rtype::common {
    class SystemAnimation : public Isystem {
        public:
            SystemAnimation() = default;
            ~SystemAnimation() override = default;

            void update(rtype::common::Manager &manager) {
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities();    
                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_ANIM))) {
                        auto sprite = manager.getComponent<SpriteComponent>(x);
                        auto clock = manager.getComponent<ClockComponent>(x);
                        auto anim = manager.getComponent<AnimationComponent>(x);

                        float leftSprite = std::get<0>(sprite->img.getSpriteTextureRect());
                        if (clock->clock.getElapsedTime() > anim->_sec) {
                            leftSprite += anim->_offset;
                            if (leftSprite >= anim->_maxW) {
                                leftSprite = anim->_oldLeft;
                            }
                            sprite->img.setSpriteTextureRect(
                                leftSprite,
                                std::get<1>(sprite->img.getSpriteTextureRect()),
                                std::get<2>(sprite->img.getSpriteTextureRect()),
                                std::get<3>(sprite->img.getSpriteTextureRect())
                            );
                            clock->clock.restartClock();
                        }
                    }
                }
            }
    };
}

#endif /* !SYSTEMANIMATION_HPP_ */
