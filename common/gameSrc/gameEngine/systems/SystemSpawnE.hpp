/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SystemSpawnE
*/

#ifndef SYSTEMSPAWNE_HPP_
#define SYSTEMSPAWNE_HPP_

#include <cstdlib>
#include <ctime>

#include "Systems.hpp"
#include "Manager.hpp"
#include "Types.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "ClockComponent.hpp"
#include "AnimationComponent.hpp"
#include "SpawnComponent.hpp"
#include "Monster.hpp"

#include "Window.hpp"

namespace rtype::common  {
    class SystemSpawnE {
        public:
            SystemSpawnE() = default;
            ~SystemSpawnE() = default;

            static const std::string CONFIG_SPAWN_MONSTER() { return "./client/assets/config/monster/monster1.json"; };
            void update(rtype::common ::Manager &manager) {
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities();
                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_SPAWN))) {
                        auto clock = manager.getComponent<ClockComponent>(x);
                        auto spawn = manager.getComponent<SpawnComponent>(x);
                         auto sec = 1 + std::rand()/((RAND_MAX + 1u)/spawn->_nbSecSpawn);
                        if (clock->clock.getElapsedTime() > sec && spawn->_nbSpawn > 0) {
                            for (size_t i = 0; i < spawn->_nbSpawnEnm; i++) {
                                rtype::common ::Monster::initMonster(
                                rtype::common::OpenConfigFile(CONFIG_SPAWN_MONSTER()).getData(),
                                manager
                                );
                                spawn->_nbSpawn--;
                            }
                        clock->clock.restartClock();
                        }
                    }
                }
            }
        protected:
        private:
    };
}

#endif /* !SYSTEMSPAWNE_HPP_ */
