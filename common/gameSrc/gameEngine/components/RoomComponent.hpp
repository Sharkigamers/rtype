/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** RoomComponent
*/

#pragma once
#include "Component.hpp"

namespace rtype::common {
    class RoomComponent: public rtype::common::Icomponent {
         public:
            RoomComponent(const int &port = 0) : _port(_port) {}
            ~RoomComponent() override = default;
            int _port = 0;
    };
}
