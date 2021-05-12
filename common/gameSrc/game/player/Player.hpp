/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <map>
#include <string>

#include "OpenConfigFile.hpp"

#include "Manager.hpp"

#include "VelocityComponent.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "AnimationComponent.hpp"
#include "ClockComponent.hpp"
#include "PlayerTagComponent.hpp"

namespace rtype::common {
    class Player {
        public:

            static uint32_t initPlayer(
                std::map<std::string, std::string> params,
                rtype::common::Manager &manager
            ) noexcept
            {
                std::uint32_t player = manager.createEntity();

                manager.addComponent<rtype::common::SpriteComponent>(
                    player,
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
                    player,
                    COMP_POSITION,
                    std::stoi(params[rtype::common::SPRITE_POSX]),
                    std::stoi(params[rtype::common::SPRITE_POSY])
                );
                manager.addComponent<rtype::common::VelocityComponent>(
                    player,
                    COMP_VELOCITY,
                    std::stoi(params[rtype::common::VELOCITY_POSX]),
                    std::stoi(params[rtype::common::VELOCITY_POSY]),
                    (bool)std::stoi(params[rtype::common::STAY_IN_SCREEN]) != 0,
                    (unsigned short)std::stoi(params[rtype::common::WIDTH_MAX_SCREEN]),
                    (unsigned short)std::stoi(params[rtype::common::HEIGHT_MAX_SCREEN]),
                    (bool)std::stoi(params[rtype::common::IS_CONTROLLABLE]) != 0
                );
                manager.addComponent<rtype::common::ClockComponent>(
                    player,
                    COMP_CLOCK
                );
                manager.addComponent<rtype::common::AnimationComponent>(
                    player,
                    COMP_ANIM,
                    std::stoi(params[rtype::common::ANIMATION_WIDTH]),
                    std::stoi(params[rtype::common::ANIMATION_OFFSET]),
                    std::stof(params[rtype::common::ANIMATION_SECOND]),
                    std::stoi(params[rtype::common::TEXTURE_LEFT])
                );
                manager.addComponent<rtype::common::PlayerTagComponent>(
                    player,
                    COMP_PLAYER
                );

                return player;
            }

        protected:
        private:
    };
}

#endif /* !PLAYER_HPP_ */
