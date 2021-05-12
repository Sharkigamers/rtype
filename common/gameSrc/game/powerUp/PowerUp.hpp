/*
** EPITECH PROJECT, 2020
** PowerUp.hpp
** File description:
** PowerUp
*/

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

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
#include "PowerUpComponent.hpp"

namespace rtype::common {
class PowerUp {
    public:
        PowerUp();
        ~PowerUp();

        static uint16_t initPowerUp(
                std::map<std::string, std::string> params,
                rtype::common::Manager &manager
            ) noexcept
            {
                std::uint32_t powerUp = manager.createEntity();

                manager.addComponent<rtype::common::SpriteComponent>(
                    powerUp,
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
                    powerUp,
                    COMP_POSITION,
                    std::stoi(params[rtype::common::SPRITE_POSX]),
                    std::stoi(params[rtype::common::SPRITE_POSY])
                );
                manager.addComponent<rtype::common::ClockComponent>(
                    powerUp,
                    COMP_CLOCK
                );
                manager.addComponent<rtype::common::AnimationComponent>(
                    powerUp,
                    COMP_ANIM,
                    std::stoi(params[rtype::common::ANIMATION_WIDTH]),
                    std::stoi(params[rtype::common::ANIMATION_OFFSET]),
                    std::stof(params[rtype::common::ANIMATION_SECOND]),
                    std::stoi(params[rtype::common::TEXTURE_LEFT])
                );

                manager.addComponent<rtype::common::PowerUpComponent>(
                    powerUp,
                    COMP_POWER_UP
                );
                return (powerUp);
            }

    protected:
    private:
};
}

#endif /* !POWERUP_HPP_ */
