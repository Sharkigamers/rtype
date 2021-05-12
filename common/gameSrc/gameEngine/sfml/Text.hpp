/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Utils.hpp"
#include "IText.hpp"

namespace rtype {
    namespace common {

        /* Error Text class */

        class TextError : public std::exception {

            public:
                TextError(const std::string &message) : _errorMessage(message) {};
                ~TextError() = default;

                const char *what() const throw() { return _errorMessage.c_str(); }

            private:
                std::string _errorMessage;
        };

        /* Text Class */

        class Text : public Utils, IText {
            public:
                inline static const std::string UNOPENABLE_FONT(std::string const &path) { return "Unopenable font located at: '" + path + "'"; };

                static const unsigned char black = 0;
                static const unsigned char white = 1;
                static const unsigned char red = 2;
                static const unsigned char green = 3;
                static const unsigned char blue = 4;
                static const unsigned char yellow = 5;
                static const unsigned char magenta = 6;
                static const unsigned char cyan = 7;
                static const unsigned char transparent = 8;

            public:
                Text(
                    std::string const &filePath,
                    std::string const &string = "empty",
                    unsigned short const &textSize = 30
                )
                {
                    setTextString(string);
                    setTextSize(textSize);
                    setTextFont(filePath);
                    setTextPosition(0, 0);
                    setTextBlack();
                };
                ~Text() noexcept = default;

                void setTextString(std::string const &text) noexcept final
                {
                    _text.setString(text);
                }

                std::string getTextString() const noexcept final
                {
                    return _text.getString();
                }

                bool setTextFont(std::string const &fontPath) final
                {
                    if (doesFileExist(fontPath)) {
                        try {
                            _font.loadFromFile(fontPath);
                        } catch(const std::exception& e) {
                            throw TextError(UNOPENABLE_FONT(fontPath));
                        }
                        _text.setFont(_font);
                        return true;
                    }
                    return false;
                }

                void setTextSize(unsigned short const &size) noexcept final
                {
                    _text.setCharacterSize((unsigned int)size);
                }

                unsigned int getTextSize() const noexcept final
                {
                    return _text.getCharacterSize();
                }

                void setTextLineSpace(float const &height) noexcept final
                {
                    _text.setLineSpacing(height);
                }

                float getTextLineSpace() const noexcept final
                {
                    return _text.getLineSpacing();
                }

                void setTextCharacterSpace(float const &width) noexcept final
                {
                    _text.setLetterSpacing(width);
                }

                float getTextCharacterSpace() const noexcept final
                {
                    return _text.getLetterSpacing();
                }

                void setTextStyle(unsigned int const &style) noexcept final
                {
                    _text.setStyle(style);
                }

                unsigned int getTextStyle() const noexcept final
                {
                    return _text.getStyle();
                }

                void setTextColor(unsigned char const &color) noexcept final
                {
                    switch (color) {
                    case black:
                        setTextBlack();
                        break;
                    case white:
                        setTextWhite();
                        break;
                    case red:
                        setTextRed();
                        break;
                    case green:
                        setTextGreen();
                        break;
                    case blue:
                        setTextBlue();
                        break;
                    case yellow:
                        setTextYellow();
                        break;
                    case magenta:
                        setTextMagenta();
                        break;
                    case cyan:
                        setTextCyan();
                        break;
                    case transparent:
                        setTextTransparent();
                        break;
                    default:
                        break;
                    }
                }

                void setTextBlack() noexcept final
                {
                    _text.setFillColor(sf::Color::Black);
                    _color = black;
                }

                void setTextWhite() noexcept final
                {
                    _text.setFillColor(sf::Color::White);
                    _color = white;
                }

                void setTextRed() noexcept final
                {
                    _text.setFillColor(sf::Color::Red);
                    _color = red;
                }

                void setTextGreen() noexcept final
                {
                    _text.setFillColor(sf::Color::Green);
                    _color = green;
                }

                void setTextBlue() noexcept final
                {
                    _text.setFillColor(sf::Color::Blue);
                    _color = blue;
                }

                void setTextYellow() noexcept final
                {
                    _text.setFillColor(sf::Color::Yellow);
                    _color = yellow;
                }

                void setTextMagenta() noexcept final
                {
                    _text.setFillColor(sf::Color::Magenta);
                    _color = magenta;
                }

                void setTextCyan() noexcept final
                {
                    _text.setFillColor(sf::Color::Cyan);
                    _color = cyan;
                }

                void setTextTransparent() noexcept final
                {
                    _text.setFillColor(sf::Color::Transparent);
                    _color = transparent;
                }

                unsigned char getTextColor() const noexcept final
                {
                    return _color;
                }

                void setTextPosition(float const &x, float const &y) noexcept final
                {
                    _text.setPosition(x, y);
                }

                std::pair<float, float> getTextPosition() const noexcept final
                {
                    return std::make_pair(_text.getPosition().x, _text.getPosition().y);
                }

                void setTextAngularRotation(float const &angularRotation) noexcept final
                {
                    _text.setRotation(angularRotation);
                }

                float getTextAngularRotation() const noexcept final
                {
                    return _text.getRotation();
                }

                void setTextScale(float const &x, float const &y) noexcept final
                {
                    _text.setScale(x, y);
                }

                std::pair<float, float> getTextScale() const noexcept final
                {
                    return std::make_pair(_text.getScale().x, _text.getScale().y);
                }

                void setTextOrigin(float const &x, float const &y) noexcept final
                {
                    _text.setOrigin(x, y);
                }

                std::pair<float, float> getTextOrigin() const noexcept final
                {
                    return std::make_pair(_text.getOrigin().x, _text.getOrigin().y);
                }

                void setTextMoving(float const &x, float const &y) noexcept final
                {
                    _text.move(x, y);
                }

                void setTextRotating(float const &rotation) noexcept final
                {
                    _text.rotate(rotation);
                }

                void setTextScaling(float const &x, float const &y) noexcept final
                {
                    _text.scale(x, y);
                }
                sf::Text getText() const noexcept
                {
                    return _text;
                }

            protected:
            private:
                sf::Text _text;
                sf::Font _font;
                unsigned char _color = 0;
        };
    }
}

#endif /* !TEXT_HPP_ */
