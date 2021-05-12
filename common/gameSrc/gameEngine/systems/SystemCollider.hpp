/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SystemCollider
*/

#ifndef SYSTEMCOLLIDER_HPP_
#define SYSTEMCOLLIDER_HPP_

#include <cmath>

#include "Systems.hpp"
#include "Manager.hpp"
#include "Types.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "PowerUp.hpp"

#include "Window.hpp"

namespace rtype::common {
    class SystemCollider : public Isystem {
        public:
            SystemCollider() = default;
            ~SystemCollider() override = default;

            static const std::string CONFIG_POWER_UP() { return "./client/assets/config/powerUp/powerUp.json"; }

            void update(rtype::common ::Manager &manager) {
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities(); 
                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_COLLIDER))) {
                        colMonsterPlayer(manager);
                        colMonsterProjectile(manager);
                        colPlayerPowerUp(manager);
                    }
                }
            }
            std::tuple<float, float, float, float> getPosEnt(rtype::common ::Manager &manager, const uint32_t ent)
            {
                auto sprite = manager.getComponent<SpriteComponent>(ent);
                return  std::make_tuple(std::get<0>(sprite->img.getSpritePosition()),
                std::get<1>(sprite->img.getSpritePosition()),
                std::get<2>(sprite->img.getSpriteTextureRect()) * sprite->img.getSpriteScale().first,
                std::get<3>(sprite->img.getSpriteTextureRect()) * sprite->img.getSpriteScale().second);
                    
                
            }
            using hitbox_t = std::tuple<float, float, float, float>;
            bool isCollider(const hitbox_t &hitbox1, const hitbox_t &hitbox2)
            {
                if (std::get<0>(hitbox1) < std::get<0>(hitbox2) + std::get<2>(hitbox2) &&
                    (std::get<0>(hitbox1) + std::get<2>(hitbox1)) > std::get<0>(hitbox2) &&
                    std::get<1>(hitbox1) < std::get<1>(hitbox2) + std::get<3>(hitbox2) &&
                    (std::get<1>(hitbox1) + std::get<3>(hitbox1)) > std::get<1>(hitbox2) &&
                    std::get<0>(hitbox1) != 0 && std::get<0>(hitbox2) != 0)
                    {
                        return true;    
                    }
                return false;
            }

            void colMonsterPlayer(rtype::common ::Manager &manager)
            {
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities(); 

                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_PLAYER))) {
                       for (auto y:living) {
                            if (checkSignature(entities[y].getSignature(), flagTosignature(SYS_ENEMY))) {
                                if (isCollider(getPosEnt(manager, x), getPosEnt(manager, y))) {
                                    manager.removeEntity(x);
                                }
                            }
                        }

                    }
                }
            }
            void colMonsterProjectile(rtype::common ::Manager &manager)
            {
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities(); 

                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_FIRE))) {
                       for (auto y:living) {
                            if (checkSignature(entities[y].getSignature(), flagTosignature(SYS_ENEMY))) {
                                auto monsterPosition = manager.getComponent<PositionComponent>(y);
                                if (isCollider(getPosEnt(manager, x), getPosEnt(manager, y))) {
                                    manager.removeEntity(y);
                                    manager.removeEntity(x);
                                    hasShot--;
                                    auto powerUpIndex = rtype::common ::PowerUp::initPowerUp(
                                        rtype::common::OpenConfigFile(CONFIG_POWER_UP()).getData(),
                                        manager
                                    );
                                    auto powerUpPos = manager.getComponent<PositionComponent>(powerUpIndex);
                                    powerUpPos->posX = monsterPosition->posX;
                                    powerUpPos->posY = monsterPosition->posY;
                                    return;
                                }
                            }
                        }

                    }
                }
            }

            void colPlayerPowerUp(rtype::common ::Manager &manager)
            {
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities(); 

                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_PLAYER))) {
                       for (auto y:living) {
                            if (checkSignature(entities[y].getSignature(), flagTosignature(SYS_POWER_UP))) {
                                if (isCollider(getPosEnt(manager, x), getPosEnt(manager, y))) {
                                    manager.removeEntity(y);
                                    return;
                                }
                            }
                        }

                    }
                }
            }
        protected:
        private:
    };
}
#endif /* !SYSTEMCOLLIDER_HPP_ */
