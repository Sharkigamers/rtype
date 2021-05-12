/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** ButtonListRoom
*/

#ifndef BUTTONLISTROOM_HPP_
#define BUTTONLISTROOM_HPP_


#include <map>
#include <string>

#include <boost/lexical_cast.hpp>  

#include "OpenConfigFile.hpp"

#include "Manager.hpp"

#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "ButtonComponent.hpp"
#include "TextComponent.hpp"
#include "RoomComponent.hpp"

namespace rtype::common {
    class ButtonListRoom {
        public:

            static void initButtonListRoom(
                std::map<std::string, std::string> params,
                button_type const &buttonType,
                rtype::common::Manager &manager,
                const int &port,
                const int &nbPerson,
                const int &id,
                const int &posX,
                const int &posY
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
                    posX,
                    posY
                );
                manager.addComponent<rtype::common::ButtonComponent>(
                    ent,
                    COMP_BUTTON,
                    buttonType
                );
                manager.addComponent<rtype::common::TextComponent>(
                    ent,
                    COMP_TEXT,
                    "Room " +  boost::lexical_cast<std::string>(id) + "     Player " + boost::lexical_cast<std::string>(nbPerson) + "\nPort " +  boost::lexical_cast<std::string>(port),
                    (unsigned char)std::stoi(params[rtype::common::TEXT_COLOR]),
                    std::stoi(params[rtype::common::TEXT_SIZE]),
                    posX + 50,
                    posY + 40,
                    params[rtype::common::FONT_PATH]
                );
                manager.addComponent<rtype::common::RoomComponent>(
                    ent,
                    COMP_ROOM,
                    port
                );

            }

        protected:
        private:
    };
}


#endif /* !BUTTONLISTROOM_HPP_ */
