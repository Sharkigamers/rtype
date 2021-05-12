/*
** EPITECH PROJECT, 2020
** ButtonComponent.hpp
** File description:
** ButtonComponent
*/

#ifndef BUTTONCOMPONENT_HPP_
#define BUTTONCOMPONENT_HPP_
#include "Component.hpp"

// typedef enum button_type {
//     NONE = -1,
//     START = 0,
//     SETTINGS = 1,
//     QUIT = 2,
// } button_type_t;

namespace rtype::common {
    typedef enum button_type {
        BUTTON_PLAY = 0,
        BUTTON_SETTINGS = 1,
        BUTTON_QUIT = 2,
        BUTTON_CREATE_ROOM = 3,
        BUTTON_LIST_ROOM = 4,
        BUTTON_ENTER_ROOM = 5,
        BUTTON_REFRESH = 6,
        BUTTON_RETURN = 7,
    } button_type_t;

    class ButtonComponent : public Icomponent {
        public:
            ButtonComponent(button_type_t mButton)
            : button(mButton) {};
            ~ButtonComponent() = default;
            
            button_type_t button;
            bool _checkActifBtn = false;

    };
}

#endif /* !BUTTONCOMPONENT_HPP_ */
