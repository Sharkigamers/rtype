/*
** EPITECH PROJECT, 2020
** Projectiles
** File description:
** Projectiles
*/

#ifndef PROJECTILES_HPP_
#define PROJECTILES_HPP_

#include <map>
#include <string>

#include "OpenConfigFile.hpp"

#include "Manager.hpp"

#include "VelocityComponent.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "AnimationComponent.hpp"
#include "ClockComponent.hpp"
#include "ProjectilesTagComponent.hpp"

namespace rtype::common {
    class Projectiles {
        public:
            Projectiles();
            ~Projectiles();

            static uint16_t initProjectiles(
                std::map<std::string, std::string> params,
                rtype::common::Manager &manager
            ) noexcept
            {
                std::uint32_t projectiles = manager.createEntity();

                manager.addComponent<rtype::common::SpriteComponent>(
                    projectiles,
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
                    projectiles,
                    COMP_POSITION,
                    std::stoi(params[rtype::common::SPRITE_POSX]),
                    std::stoi(params[rtype::common::SPRITE_POSY])
                );
                manager.addComponent<rtype::common::VelocityComponent>(
                    projectiles,
                    COMP_VELOCITY,
                    std::stoi(params[rtype::common::VELOCITY_POSX]),
                    std::stoi(params[rtype::common::VELOCITY_POSY]),
                    (bool)std::stoi(params[rtype::common::STAY_IN_SCREEN]) != 0,
                    (unsigned short)std::stoi(params[rtype::common::WIDTH_MAX_SCREEN]),
                    (unsigned short)std::stoi(params[rtype::common::HEIGHT_MAX_SCREEN]),
                    (bool)std::stoi(params[rtype::common::IS_CONTROLLABLE]) != 0
                );
                // manager.addComponent<rtype::common::ClockComponent>(
                //     projectiles,
                //     COMP_CLOCK
                // );
                // manager.addComponent<rtype::common::AnimationComponent>(
                //     projectiles,
                //     COMP_ANIM,
                //     std::stoi(params[rtype::common::ANIMATION_WIDTH]),
                //     std::stoi(params[rtype::common::ANIMATION_OFFSET]),
                //     std::stof(params[rtype::common::ANIMATION_SECOND]),
                //     std::stoi(params[rtype::common::TEXTURE_LEFT])
                // );
                manager.addComponent<rtype::common::ProjectilesTagComponent>(
                    projectiles,
                    COMP_PROJECTILES
                );
                return (projectiles);
            }

        protected:
        private:
    };
}

#endif /* !PROJECTILES_HPP_ */
