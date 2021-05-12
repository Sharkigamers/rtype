/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** IText
*/

#ifndef ITEXT_HPP_
#define ITEXT_HPP_

#include <string>

#include <utility>

namespace rtype {
    namespace common {

        /* Interface for Text Class */

        class IText {
            public:
                ~IText() = default;

                virtual void setTextString(std::string const &text) noexcept = 0;

                virtual std::string getTextString() const noexcept = 0;

                virtual bool setTextFont(std::string const &fontPath) = 0;

                virtual void setTextSize(unsigned short const &size) noexcept = 0;

                virtual unsigned int getTextSize() const noexcept = 0;

                virtual void setTextLineSpace(float const &height) noexcept = 0;

                virtual float getTextLineSpace() const noexcept = 0;

                virtual void setTextCharacterSpace(float const &width) noexcept = 0;

                virtual float getTextCharacterSpace() const noexcept = 0;

                virtual void setTextStyle(unsigned int const &style) noexcept = 0;

                virtual unsigned int getTextStyle() const noexcept = 0;

                virtual void setTextColor(unsigned char const &color) noexcept = 0;

                virtual void setTextBlack() noexcept = 0;

                virtual void setTextWhite() noexcept = 0;

                virtual void setTextRed() noexcept = 0;

                virtual void setTextGreen() noexcept = 0;

                virtual void setTextBlue() noexcept = 0;

                virtual void setTextYellow() noexcept = 0;

                virtual void setTextMagenta() noexcept = 0;

                virtual void setTextCyan() noexcept = 0;

                virtual void setTextTransparent() noexcept = 0;

                virtual unsigned char getTextColor() const noexcept = 0;

                virtual void setTextPosition(float const &x, float const &y) noexcept = 0;

                virtual std::pair<float, float> getTextPosition() const noexcept = 0;

                virtual void setTextAngularRotation(float const &angularRotation) noexcept = 0;

                virtual float getTextAngularRotation() const noexcept = 0;

                virtual void setTextScale(float const &x, float const &y) noexcept = 0;

                virtual std::pair<float, float> getTextScale() const noexcept = 0;

                virtual void setTextOrigin(float const &x, float const &y) noexcept = 0;

                virtual std::pair<float, float> getTextOrigin() const noexcept = 0;

                virtual void setTextMoving(float const &x, float const &y) noexcept = 0;

                virtual void setTextRotating(float const &rotation) noexcept = 0;

                virtual void setTextScaling(float const &x, float const &y) noexcept = 0;

            protected:
            private:
        };
    }
}

#endif /* !ITEXT_HPP_ */
