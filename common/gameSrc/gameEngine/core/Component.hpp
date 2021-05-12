/*
** EPITECH PROJECT, 2020
** Component
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_
#include "Types.hpp"

namespace rtype {
    namespace common {
        class Icomponent {
            public:
                virtual ~Icomponent() = default;

                bool operator==(const Icomponent &lopes) {
                    return(&lopes == this);
                }
        };
    }
}

#endif /* !COMPONENT_HPP_ */
