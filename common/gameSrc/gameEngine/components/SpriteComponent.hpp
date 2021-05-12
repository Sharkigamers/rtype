/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SpriteComponent
*/

#pragma once
#include "Component.hpp"
#include "Sprite.hpp"

namespace rtype::common {
    class SpriteComponent : public Icomponent {
        
        public:
            Sprite img;

            SpriteComponent(
                std::string const &path,
                size_t const &textureLeft = 0,
                size_t const &textureTop = 0,
                size_t const &textureWidth = 0,
                size_t const &textureHeight = 0,
                float const &scaleX = 1,
                float const &scaleY = 1,
                bool isRender = true
            ) : img(path, true), _isRender(isRender) {
                img.setSpriteTextureRect(
                    textureLeft,
                    textureTop,
                    textureWidth,
                    textureHeight
                );
                img.setSpriteScale(
                    scaleX,
                    scaleY
                );
            }
            ~SpriteComponent() override = default;
            bool _isRender;
    };
}