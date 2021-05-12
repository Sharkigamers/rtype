/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** AnimationComponent
*/

#ifndef ANIMATIONCOMPONENT_HPP_
#define ANIMATIONCOMPONENT_HPP_

#include "Component.hpp"

namespace rtype::common {
    class AnimationComponent : public rtype::common::Icomponent
    {
        public:
            AnimationComponent(const int &max = 0, const int &offset = 0, const float &sec = 1, const int &oldLeft = 0) : _maxW(max), _offset(offset), _sec(sec), _oldLeft(oldLeft) {};
            ~AnimationComponent() override = default; 

            int _oldLeft;
            int _maxW;
            int _offset;
            float _sec;
    };
}

#endif /* !ANIMATIONCOMPONENT_HPP_ */
