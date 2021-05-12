/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** IColor
*/

#ifndef ICOLOR_HPP_
#define ICOLOR_HPP_

namespace rtype {
    namespace common {

        /* Interface for Color Class */

        class IColor {
            public:
                virtual ~IColor() = default;

                virtual void setColor(
                    unsigned short red,
                    unsigned short green,
                    unsigned short blue,
                    unsigned short alpha
                ) noexcept = 0;

                virtual unsigned short getRed() const noexcept = 0;

                virtual unsigned short getGreen() const noexcept = 0;

                virtual unsigned short getBlue() const noexcept = 0;

                virtual unsigned short getAlpha() const noexcept = 0;

            protected:
            private:
        };
    }
}

#endif /* !ICOLOR_HPP_ */
