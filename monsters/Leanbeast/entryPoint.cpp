/*
** EPITECH PROJECT, 2020
** entryPoint
** File description:
** entryPoint
*/

#include "Imonster.hpp"
#include "Leanbeast.hpp"
#if defined(_WIN32)
#include <windows.h>
#endif

rtype::API::Imonster *ret = nullptr;

#if defined(_WIN32)
__declspec(dllexport) void enter()
{
	ret = new rtype::API::Leanbeast("path/to/configFile/");
}

__declspec(dllexport) void out()
{
	delete ret;
}

extern "C" __declspec(dllexport) rtype::API::Imonster *entryPoint()
{
	return ret;
}
#endif

__attribute__((constructor))
void enter()
{
	ret = new rtype::API::Leanbeast("path/to/configFile/");
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