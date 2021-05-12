/*
** EPITECH PROJECT, 2020
** entryPoint
** File description:
** entryPoint
*/

#include "Imonster.hpp"
#include "PutridLopes.hpp"

rtype::API::Imonster *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new rtype::API::PutridLopes("./client/assets/config/monster/monster1.json");
}

__attribute__((destructor))
void out()
{
	delete ret;
}


extern "C" rtype::API::Imonster *entryPoint()
{
	return ret;
}