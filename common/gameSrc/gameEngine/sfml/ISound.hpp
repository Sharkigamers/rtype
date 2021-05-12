/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** ISound
*/

#ifndef ISOUND_HPP_
#define ISOUND_HPP_

#include <string>

namespace rtype {
    namespace common {

        /* Interface for Sound Class */

        class ISound {
            public:
                ~ISound() = default;

                virtual void playMusic() noexcept = 0;

                virtual void pauseMusic() noexcept = 0;

                virtual void stopMusic() noexcept = 0;

                virtual void makeMusicLoop(bool const &isLoop) noexcept = 0;

                virtual void setMusicVolume(float const &volume) noexcept = 0;

                virtual bool setMusicFromPath(std::string const &filePath, bool const &isLoop, float const &volume) = 0;

            protected:
            private:
        };
    }
}

#endif /* !ISOUND_HPP_ */
