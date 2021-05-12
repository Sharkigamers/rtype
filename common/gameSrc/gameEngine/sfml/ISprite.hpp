/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** ISprite
*/

#ifndef ISPRITE_HPP_
#define ISPRITE_HPP_

#include <string>

#include <utility>
#include <tuple>

namespace rtype {
    namespace common {

        /* Interface for Sprite Class */

        class ISprite {
            public:
                ~ISprite() = default;

                virtual void setSpriteScale(float const &x, float const &y) noexcept = 0;

                virtual std::pair<float, float> getSpriteScale() const noexcept = 0;

                virtual void setSpritePosition(float const &x, float const &y) noexcept = 0;

                virtual std::pair<float, float> getSpritePosition() const noexcept = 0;

                virtual void setSpriteOrigin(float const &x, float const &y) noexcept = 0;

                virtual std::pair<float, float> getSpriteOrigin() const noexcept = 0;

                virtual void setSpriteAngularRotation(float const &angularRotation) noexcept = 0;

                virtual float getSpriteAngularRotation() const noexcept = 0;

                virtual void setSpriteTextureRect(float const &left, float const &top, float const &width, float const &height) noexcept = 0;

                virtual std::tuple<float, float, float, float> getSpriteTextureRect() const noexcept = 0;

                virtual bool setSpriteFromFile(std::string const &filePath, bool const &makeSmooth) = 0;

            protected:
            private:
        };
    }
}

#endif /* !ISPRITE_HPP_ */
