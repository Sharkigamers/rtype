/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Rigidbody
*/

#ifndef RIGIDBODY_HPP_
#define RIGIDBODY_HPP_

#include "Vector2.hpp"
#include "Component.hpp"

class Rigidbody : public rtype::common::Icomponent
{
    public:
        float mass = 1;
        bool useGravity;
        Vector2 velocity;
        Vector2 acceleration;
};

#endif /* !RIGIDBODY_HPP_ */
