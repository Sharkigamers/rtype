/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Transform
*/

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "Vector2.hpp"
#include "Component.hpp"

class Transform : public rtype::common::Icomponent
{
	public:
		Vector2 position;
		Vector2 rotation;
		Vector2 scale;
};

#endif /* !TRANSFORM_HPP_ */