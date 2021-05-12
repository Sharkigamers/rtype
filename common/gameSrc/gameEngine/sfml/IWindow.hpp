/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** IWindow
*/

#ifndef IWINDOW_HPP_
#define IWINDOW_HPP_

#include "Sprite.hpp"
#include "Text.hpp"
#include "Event.hpp"

class IWindow {
    public:
        virtual ~IWindow() = default;

        virtual void closeWindow() noexcept = 0;

        virtual bool isWindowOpen() const noexcept = 0;

        virtual void makeCursorVisible(bool const &makeVisible) noexcept = 0;

        virtual void setFrameRateSecond(unsigned short const &fps) noexcept = 0;

        virtual void displayWindow() noexcept = 0;

        virtual void drawSprite(rtype::common ::Sprite sprite) noexcept = 0;

        virtual void drawText(rtype::common ::Text txt) noexcept = 0;

        virtual void clearWindow() noexcept = 0;

        virtual bool pollEventFromRenderWindow(rtype::common ::Event &event) = 0;

    protected:
    private:
};

#endif /* !IWINDOW_HPP_ */
