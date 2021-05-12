/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** IEvent
*/

#ifndef IEVENT_HPP_
#define IEVENT_HPP_

namespace rtype {
    namespace common {

        /* Interface for Event Class */

        class IEvent {
            public:
                virtual ~IEvent() = default;

                virtual bool isMousePressed() const noexcept = 0;
                
                virtual bool isTextEntered() const noexcept = 0;

                virtual unsigned int characterEntered() const noexcept = 0;

                virtual bool isMouseReleased() const noexcept = 0;

                virtual bool isKeyPressed() const noexcept = 0;

                virtual bool isKeyReleased() const noexcept = 0;

                virtual char eventKeyCode() const noexcept = 0;

                virtual bool compareCharWithEventKeyCode(char const &key) const noexcept = 0;

                virtual bool isEscapePressed() const noexcept = 0;

                virtual bool isClosing() const noexcept = 0;

            protected:
            private:
        };
    }
}

#endif /* !IEVENT_HPP_ */
