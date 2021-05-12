/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** FightComponent
*/

#pragma once
#include "Component.hpp"

namespace rtype::common
{
    class FightComponent : public Icomponent {
        public:

            FightComponent(
                unsigned short const &attackPower,
                unsigned short const &healPoint
            ): attack(attackPower), hp(healPoint) {};
            ~FightComponent() = default;

            int attack = 0;
            int hp = 0;
    };
} // namespace rtype::common
