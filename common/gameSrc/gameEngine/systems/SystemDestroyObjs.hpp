/*
** EPITECH PROJECT, 2020
** SystemDestroyObjs
** File description:
** SystemDestroyObjs
*/

#ifndef SystemDestroyObjS_HPP_
#define SystemDestroyObjS_HPP_

#include "Systems.hpp"
#include "Manager.hpp"
#include "Types.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "ClockComponent.hpp"
#include "AnimationComponent.hpp"
#include "Projectiles.hpp"

#include "Window.hpp"

namespace rtype::common  {
    class SystemDestroyObjs {
        public:
            SystemDestroyObjs() = default;
            ~SystemDestroyObjs() = default;

            void update(rtype::common ::Manager &manager) {
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities();

                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_FIRE))) {
                        auto position = manager.getComponent<PositionComponent>(x);
                        auto velocity = manager.getComponent<VelocityComponent>(x);
                        if (position->posX >= velocity->maxWidthScreen - 12) {
                            manager.removeEntity(x);
                            hasShot ++;
                        }
                    }
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_ENEMY))) {
                        auto position = manager.getComponent<PositionComponent>(x);
                        auto velocity = manager.getComponent<VelocityComponent>(x);
                        if (position->posX >= velocity->maxWidthScreen || (position->posX <= -100)) {
                            manager.removeEntity(x);
                        }
                    }
                }
            }
        protected:
        private:
    };
}

#endif /* !SystemDestroyObjS_HPP_ */
