/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SystemMusic
*/

#ifndef SYSTEMMUSIC_HPP_
#define SYSTEMMUSIC_HPP_

#include "Systems.hpp"
#include "Manager.hpp"
#include "Types.hpp"
#include "MusicComponent.hpp"

#include "Sound.hpp"


namespace rtype::common  {
    class SystemMusic : Isystem {
        public:
            SystemMusic() = default;
            ~SystemMusic() override = default;

            void update(rtype::common ::Manager &manager) {
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities();
                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_MUSIC))) {
                        auto music = manager.getComponent<MusicComponent>(x);
                        music->sound.playMusic();
                    }
                }
            }
    };
}

#endif /* !SYSTEMMUSIC_HPP_ */
