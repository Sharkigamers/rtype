/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <memory>
#include <SFML/Window.hpp>

#include "IWindow.hpp"

static const unsigned short LOW_FPS = 30;
static const unsigned short MEDIUM_FPS = 60;
static const unsigned short HIGHT_FPS = 120;
static const unsigned short ULTRA_FPS = 240;

namespace rtype {
    namespace common {

        /* Window Class */

        class Window : public IWindow {
            public:
                Window(
                    unsigned short const &width = 1920,
                    unsigned short const &height = 1080,
                    unsigned short const &bitsPerPixel = 32,
                    std::string const &windowName = "R-lopes - Alpha 1.0",
                    bool const &isFullScreen = true
                ) noexcept
                {
                    if (isFullScreen)
                        _window.create(sf::VideoMode(width, height, bitsPerPixel), windowName, sf::Style::Fullscreen | sf::Style::Close);
                    else
                        _window.create(sf::VideoMode(width, height, bitsPerPixel), windowName, sf::Style::Resize | sf::Style::Close);
                };
                ~Window() = default;

                void closeWindow() noexcept final
                {
                    if (isWindowOpen())
                        _window.close();
                }

                bool isWindowOpen() const noexcept final
                {
                    return _window.isOpen();
                }

                void makeCursorVisible(bool const &makeVisible) noexcept final
                {
                    _window.setMouseCursorVisible(makeVisible);
                }

                void setFrameRateSecond(unsigned short const &fps) noexcept final
                {
                    _window.setFramerateLimit(fps);
                }

                void displayWindow() noexcept final
                {
                    _window.display();
                }

                void drawSprite(rtype::common ::Sprite sprite) noexcept final
                {
                    _window.draw(sprite.getSprite());
                }

                void drawText(rtype::common ::Text txt) noexcept final
                {
                    _window.draw(txt.getText());
                }
                
                void clearWindow() noexcept final
                {
                    _window.clear();
                }

                bool pollEventFromRenderWindow(rtype::common ::Event &event) final
                {
                    sf::Event windowEvent = event.getEvent();
                    bool res = _window.pollEvent(windowEvent);
                    
                    event.setEvent(windowEvent);
                    return res;
                }

            protected:
            private:
                sf::RenderWindow _window;
        };
    }
}

#endif /* !WINDOW_HPP_ */
