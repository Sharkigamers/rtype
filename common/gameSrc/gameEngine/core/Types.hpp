/*
** EPITECH PROJECT, 2020
** Types.hpp
** File description:
** Types
*/

#ifndef TYPES_HPP_
#define TYPES_HPP_

#include <bitset>
#include <cstdint>
#include <iostream>
#include "Cuuid.hpp"


// ECS
typedef struct EntityEcs
{
    rtype::common::Cuuid uuid;
    std::uint32_t id;
} EntityEcs_t;

typedef enum componentSignature {
    COMP_RENDER = 0,
    COMP_TRANSFORM = 1,
    COMP_RIGIDBODY = 2,
    COMP_PLAYER = 3,
    COMP_POSITION = 4,
    COMP_VELOCITY = 5,
    COMP_SPRITE = 6,
    COMP_BUTTON = 7,
    COMP_MUSIC = 8,
    COMP_TEXT = 9,
    COMP_CLOCK = 10,
    COMP_ANIM = 11,
    COMP_PROJECTILES = 12,
    COMP_ENEMY = 13,
    COMP_POWER_UP = 14,
    COMP_SPAWN = 15,
    COMP_ROOM = 16,
    COMP_MENU = 17
} componentSignature_e;

typedef enum systemSignature {
    SYS_BUTTON = 1 << COMP_POSITION | 1 << COMP_SPRITE | 1 << COMP_BUTTON,
    SYS_IBUTTON = 1 << COMP_POSITION | 1 << COMP_SPRITE | 1 << COMP_BUTTON | 1 << COMP_MENU,
    SYS_ROOM = 1 << COMP_POSITION | 1 << COMP_SPRITE | 1 << COMP_ROOM,
    SYS_TEST = 1 << COMP_TRANSFORM | 1 << COMP_RIGIDBODY,
    SYS_CTRL = 1 << COMP_VELOCITY,
    SYS_PLAYER = 1 << COMP_PLAYER,
    SYS_MVM = 1 << COMP_VELOCITY | 1 << COMP_POSITION,
    SYS_MUSIC = 1 << COMP_MUSIC,
    SYS_RDR = 1 << COMP_POSITION | 1 << COMP_SPRITE,
    SYS_RDR_TXT = 1 << COMP_TEXT,
    SYS_ANIM = 1 << COMP_SPRITE | 1 << COMP_CLOCK | 1 << COMP_ANIM,
    SYS_FIRE = 1 << COMP_PROJECTILES,
    SYS_ENEMY = 1 << COMP_ENEMY | 1 << COMP_SPRITE,
    SYS_COLLIDER = 1 << COMP_SPRITE | 1 << COMP_POSITION | 1 << COMP_VELOCITY,
    SYS_POWER_UP = 1 << COMP_POWER_UP,
    SYS_SPAWN = 1 << COMP_CLOCK | 1 << COMP_ENEMY | 1 << COMP_SPAWN,
} systemSignature_e;

//Entities related
static const std::uint32_t MAX_ENTITIES = 500;
static const std::uint32_t MAX_SHOT = 5;
using ComponentType = std::uint8_t;
static const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;
static const std::uint32_t MAX_BUTTONS = 3;
static bool isDown = false;
static uint8_t hasShot = MAX_SHOT;


Signature flagTosignature(systemSignature sig);
bool checkSignature(Signature entSig, Signature sysSig);
bool checkIfComponent(const Signature &entSig, const componentSignature &compSig);

#endif /* !TYPES_HPP_ */
