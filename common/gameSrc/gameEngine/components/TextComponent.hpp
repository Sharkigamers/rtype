/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** TextComponent
*/

#pragma once
#include "Component.hpp"
#include "Text.hpp"

namespace rtype::common {
    class TextComponent : public Icomponent {
        public:
            Text text;

            TextComponent(
                std::string const &txt,
                unsigned char const &color = 0,
                size_t const &size = 20,
                float const &posX = 0,
                float const &posY = 0,
                std::string const &font = "./client/assets/fonts/spacebar/SPACEBAR.ttf"
            ): text(font, txt, size) {
                text.setTextColor(color);
                text.setTextPosition(posX, posY);
            }
            ~TextComponent() override = default;
    };
}