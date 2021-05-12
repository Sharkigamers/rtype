/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Sprite
*/

#ifndef Sprite_HPP_
#define Sprite_HPP_

#include <memory>
#include <SFML/Graphics.hpp>

#include "Utils.hpp"

#include "ISprite.hpp"

namespace rtype {
    namespace common {

        /* Error Sprite Class */

        class SpriteError : public std::exception {

            public:
                SpriteError(const std::string &message) : _errorMessage(message) {};
                ~SpriteError() = default;

                const char *what() const throw() { return _errorMessage.c_str(); }

            private:
                std::string _errorMessage;
        };

        /* Sprite Class */

        class Sprite : public Utils, ISprite {
            public:
                inline static const std::string UNLOADABLE_SPRITE(std::string const &path) { return "Unloadable sprite located at: '" + path + "'"; };

            public:
                Sprite(std::string const &pathFile, bool const &makeSmooth)
                {
                    setSpriteFromFile(pathFile, makeSmooth);
                    setSpritePosition(0, 0);
                };
                ~Sprite() noexcept = default;

    
                void setSpriteScale(float const &x, float const &y) noexcept final
                {
                    _sprite.setScale(x, y);
                };

                std::pair<float, float> getSpriteScale() const noexcept final
                {
                    return std::make_pair(_sprite.getScale().x, _sprite.getScale().y);
                };


                void setSpritePosition(float const &x, float const &y) noexcept final
                {
                    _sprite.setPosition(x, y);
                };

                std::pair<float, float> getSpritePosition() const noexcept final
                {
                    return std::make_pair(_sprite.getPosition().x, _sprite.getPosition().y);
                };


                void setSpriteOrigin(float const &x, float const &y) noexcept final
                {
                    _sprite.setOrigin(x, y);
                };

                std::pair<float, float> getSpriteOrigin() const noexcept final
                {
                    return std::make_pair(_sprite.getOrigin().x, _sprite.getOrigin().y);
                };


                void setSpriteAngularRotation(float const &angularRotation) noexcept final
                {
                    _sprite.setRotation(angularRotation);
                };

                float getSpriteAngularRotation() const noexcept final
                {
                    return _sprite.getRotation();
                };


                void setSpriteTextureRect(float const &left, float const &top, float const &width, float const &height) noexcept final
                {
                    sf::IntRect rect(left, top, width, height);

                    _sprite.setTextureRect(rect);
                }

                std::tuple<float, float, float, float> getSpriteTextureRect() const noexcept final
                {
                    return std::make_tuple(
                        _sprite.getTextureRect().left,
                        _sprite.getTextureRect().top,
                        _sprite.getTextureRect().width,
                        _sprite.getTextureRect().height
                    );
                }


                bool setSpriteFromFile(std::string const &filePath, bool const &makeSmooth) final
                {
                    if (doesFileExist(filePath)) {
                        try {
                            _texture.loadFromFile(filePath);
                        } catch(const std::exception& e) {
                            throw SpriteError(UNLOADABLE_SPRITE(filePath));
                        }
                        _texture.setSmooth(makeSmooth);
                        _sprite.setTexture(_texture);
                        return true;
                    }
                    return false;
                };

                sf::Sprite getSprite() const noexcept
                {
                    return _sprite;
                }


            protected:
            private:
                sf::Sprite _sprite;
                sf::Texture _texture;
        };
    }
}

#endif /* !Sprite_HPP_ */
