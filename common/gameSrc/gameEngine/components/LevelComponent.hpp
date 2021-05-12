/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** LevelComponent
*/

#pragma once
#include "Component.hpp"

namespace rtype::common {
    class LevelComponent : public rtype::common::Icomponent
    {
        public:
            int level = 1;
    };
}