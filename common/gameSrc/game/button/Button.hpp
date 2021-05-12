/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <map>
#include <string>

#include "OpenConfigFile.hpp"

#include "Manager.hpp"

#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "ButtonComponent.hpp"
#include "TextComponent.hpp"

namespace rtype::common {
    class Button {
        public:

            static void initButtons(
                std::map<std::string, std::string> params,
                button_type const &buttonType,
                rtype::common::Manager &manager
            ) noexcept
            {
                std::uint32_t ent = manager.createEntity();

                manager.addComponent<rtype::common::SpriteComponent>(
                    ent,
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
                    ent,
                    COMP_POSITION,
                    std::stoi(params[rtype::common::SPRITE_POSX]),
                    std::stoi(params[rtype::common::SPRITE_POSY])
                );
                manager.addComponent<rtype::common::ButtonComponent>(
                    ent,
                    COMP_BUTTON,
                    buttonType
                );
                manager.addComponent<rtype::common::ButtonComponent>(
                    ent,
                    COMP_MENU,
                    buttonType
                );
                manager.addComponent<rtype::common::TextComponent>(
                    ent,
                    COMP_TEXT,
                    params[rtype::common::TEXT_STRING],
                    (unsigned char)std::stoi(params[rtype::common::TEXT_COLOR]),
                    std::stoi(params[rtype::common::TEXT_SIZE]),
                    std::stof(params[rtype::common::TEXT_POSX]),
                    std::stof(params[rtype::common::TEXT_POSY]),
                    params[rtype::common::FONT_PATH]
                );

            }

        protected:
        private:
    };
}

#endif /* !BUTTON_HPP_ */
