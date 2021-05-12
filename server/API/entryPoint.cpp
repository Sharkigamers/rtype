/*
** EPITECH PROJECT, 2020
** entryPoint
** File description:
** entryPoint
*/

#include "Imonster.hpp"

rtype::API::Imonster *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new Rtype::Monster("assets/maps/nibblerMap", "Nils");
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