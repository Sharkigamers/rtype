/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** MusicMenuComponent
*/

#pragma once
#include "Component.hpp"
#include "Sound.hpp"

namespace rtype::common {
    class MusicComponent : public Icomponent {
        public:
            Sound sound;

            MusicComponent(
                std::string const &path,
                bool const &loop,
                size_t const &volume = 50
            ): sound(path)
            {
                sound.makeMusicLoop(loop);
                sound.setMusicVolume(volume);
            }
            ~MusicComponent() override = default;
    };
}