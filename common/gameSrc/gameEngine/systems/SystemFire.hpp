/*
** EPITECH PROJECT, 2020
** SystemFire
** File description:
** SystemFire
*/

#ifndef SYSTEMFIRE_HPP_
#define SYSTEMFIRE_HPP_
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
    class SystemFire {
        public:
            SystemFire() = default;
            ~SystemFire() = default;

            static const std::string CONFIG_SHOT() { return "./client/assets/config/projectiles/playerShot1.json"; };
            void update(rtype::common ::Manager &manager, rtype::common ::Event &event) {
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities();
                rtype::common::Mouse mouse;
                
                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_CTRL))) {
                        auto playerPosition = manager.getComponent<PositionComponent>(x);
                        auto sprite = manager.getComponent<SpriteComponent>(x);
                        auto velocity = manager.getComponent<VelocityComponent>(x);
                        if (event.isMousePressed() &&  hasShot != 0 && velocity->isContrallable) {
                            auto projectileIndex = rtype::common ::Projectiles::initProjectiles(
                            rtype::common::OpenConfigFile(CONFIG_SHOT()).getData(),
                            manager
                            );
                            auto projectilePos = manager.getComponent<PositionComponent>(projectileIndex);
                            hasShot--;
                            projectilePos->posX = playerPosition->posX;
                            projectilePos->posY = playerPosition->posY;
                        }
                    }
                }
            }
        protected:
        private:
    };
}

#endif /* !SYSTEMFIRE_HPP_ */
