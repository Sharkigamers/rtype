/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SystemStopMusic
*/

#ifndef SYSTEMSTOPMUSIC_HPP_
#define SYSTEMSTOPMUSIC_HPP_

#include "Systems.hpp"
#include "Manager.hpp"
#include "Types.hpp"
#include "MusicComponent.hpp"

#include "Sound.hpp"


namespace rtype::common  {
    class SystemStopMusic : Isystem {
        public:
            SystemStopMusic() = default;
            ~SystemStopMusic() override = default;

            void update(rtype::common ::Manager &manager) {
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities();
                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_MUSIC))) {
                        auto music = manager.getComponent<MusicComponent>(x);
                        music->sound.stopMusic();
                    }
                }
            }
    };
}

#endif /* !SYSTEMSTOPMUSIC_HPP_ */
