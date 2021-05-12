/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Monster
*/

#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include <map>
#include <string>
#include <cstdlib>
#include <ctime>

#include "OpenConfigFile.hpp"

#include "Manager.hpp"

#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "VelocityComponent.hpp"
#include "EnemyTagComponent.hpp"
#include "ClockComponent.hpp"

namespace rtype::common {
    class Monster {
        public:

            static void initMonster(
                std::map<std::string, std::string> params,
                rtype::common::Manager &manager
            ) noexcept
            {
                std::uint32_t back = manager.createEntity();

                manager.addComponent<rtype::common::SpriteComponent>(
                    back,
                    COMP_SPRITE,
                    params[rtype::common::TEXTURE_PATH],
                    std::stoi(params[rtype::common::TEXTURE_LEFT]),
                    std::stoi(params[rtype::common::TEXTURE_TOP]),
                    std::stoi(params[rtype::common::TEXTURE_WIDTH]),
                    std::stoi(params[rtype::common::TEXTURE_HEIGHT]),
                    std::stof(params[rtype::common::SPRITE_SCALEX]),
                    std::stof(params[rtype::common::SPRITE_SCALEY]),
                    (bool)std::stoi(params[rtype::common::IS_RENDER]) != 0

                );
                manager.addComponent<rtype::common::PositionComponent>(
                    back,
                    COMP_POSITION,
                    std::stoi(params[rtype::common::SPRITE_POSX]),
                    1 + std::rand()/((RAND_MAX + 1u)/1080)
                );
                manager.addComponent<rtype::common::VelocityComponent>(
                    back,
                    COMP_VELOCITY,
                    std::stoi(params[rtype::common::VELOCITY_POSX]),
                    std::stoi(params[rtype::common::VELOCITY_POSY]),
                    (bool)std::stoi(params[rtype::common::STAY_IN_SCREEN]) != 0,
                    (unsigned short)std::stoi(params[rtype::common::WIDTH_MAX_SCREEN]),
                    (unsigned short)std::stoi(params[rtype::common::HEIGHT_MAX_SCREEN]),
                    (bool)std::stoi(params[rtype::common::IS_CONTROLLABLE]) != 0,
                    (bool)std::stoi(params[rtype::common::IS_FROM_RIGHT_TO_LEFT]) != 0
                );
                manager.addComponent<rtype::common::ClockComponent>(
                    back,
                    COMP_CLOCK
                );
                manager.addComponent<rtype::common::EnemyTagComponent>(
                    back,
                    COMP_ENEMY
                );
            }

        protected:
        private:
    };
}

#endif /* !MONSTER_HPP_ */
