/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <map>
#include <string>

#include "OpenConfigFile.hpp"

#include "Manager.hpp"

#include "MusicComponent.hpp"

#include "SystemMusic.hpp"

namespace rtype::common {
    class Music {
        public:

            static void initMusic(
                std::map<std::string, std::string> params,
                rtype::common::Manager &manager
            ) noexcept
            {
                std::uint32_t mus = manager.createEntity();

                manager.addComponent<rtype::common::MusicComponent>(
                    mus,
                    COMP_MUSIC,
                    params[rtype::common::MUSIC_PATH],
                    std::stoi(params[rtype::common::MUSIC_LOOPER]) != 0,
                    std::stoi(params[rtype::common::MUSIC_VOLUME])
                );
            }

        protected:
        private:
    };
}

#endif /* !MUSIC_HPP_ */
