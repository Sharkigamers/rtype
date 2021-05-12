/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** CText
*/

#ifndef CTEXT_HPP_
#define CTEXT_HPP_

#include <map>
#include <string>

#include "OpenConfigFile.hpp"

#include "Manager.hpp"

#include "TextComponent.hpp"

namespace rtype::common {
    class CText {
        public:

            static void initCText(
                std::map<std::string, std::string> params,
                rtype::common::Manager &manager,
                std::string newTextValue = ""
            ) noexcept
            {
                std::uint32_t txt = manager.createEntity();

                if (newTextValue.compare("") == 0) {
                    manager.addComponent<rtype::common::TextComponent>(
                        txt,
                        COMP_TEXT,
                        params[rtype::common::TEXT_STRING],
                        (unsigned char)std::stoi(params[rtype::common::TEXT_COLOR]),
                        std::stoi(params[rtype::common::TEXT_SIZE]),
                        std::stof(params[rtype::common::TEXT_POSX]),
                        std::stof(params[rtype::common::TEXT_POSY]),
                        params[rtype::common::FONT_PATH]
                    );
                } else {
                    manager.addComponent<rtype::common::TextComponent>(
                        txt,
                        COMP_TEXT,
                        newTextValue,
                        (unsigned char)std::stoi(params[rtype::common::TEXT_COLOR]),
                        std::stoi(params[rtype::common::TEXT_SIZE]),
                        std::stof(params[rtype::common::TEXT_POSX]),
                        std::stof(params[rtype::common::TEXT_POSY]),
                        params[rtype::common::FONT_PATH]
                    );
                }
            }

        protected:
        private:
    };
}

#endif /* !CTEXT_HPP_ */
