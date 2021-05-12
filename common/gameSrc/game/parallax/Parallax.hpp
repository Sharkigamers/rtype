/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Parallax
*/

#ifndef PARALLAX_HPP_
#define PARALLAX_HPP_

#include <map>
#include <string>

#include "OpenConfigFile.hpp"

#include "Manager.hpp"

#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "ClockComponent.hpp"
#include "AnimationComponent.hpp"

namespace rtype::common {
    class Parallax {
        public:

            static void initParallax(
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
            std::stoi(params[rtype::common::SPRITE_POSY])
        );
        manager.addComponent<rtype::common::ClockComponent>(
            back,
            COMP_CLOCK
        );
        manager.addComponent<rtype::common::AnimationComponent>(
            back,
            COMP_ANIM,
            std::stoi(params[rtype::common::ANIMATION_WIDTH]),
            std::stoi(params[rtype::common::ANIMATION_OFFSET]),
            std::stof(params[rtype::common::ANIMATION_SECOND]),
            std::stoi(params[rtype::common::TEXTURE_LEFT])
        );
            }

        protected:
        private:
    };
}


#endif /* !PARALLAX_HPP_ */
