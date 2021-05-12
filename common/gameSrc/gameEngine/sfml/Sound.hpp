/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <SFML/Audio.hpp>

#include "Utils.hpp"

#include "ISound.hpp"

namespace rtype {
    namespace common {

        /* Error Sound Class */

        class SoundError : public std::exception {

            public:
                SoundError(const std::string &message) : _errorMessage(message) {};
                ~SoundError() = default;

                const char *what() const throw() { return _errorMessage.c_str(); }

            private:
                std::string _errorMessage;
        };

        /* Sound Class */

        class Sound : public Utils, ISound {
            public:
                inline static const std::string UNOPENABLE_SOUND(std::string const &path) { return "Unopenable sprite located at: '" + path + "'"; };

            public:
                Sound(std::string const &filePath, bool const &isLoop = false, float const &volume = 50)
                {
                    setMusicFromPath(filePath, isLoop, volume);
                };
                ~Sound() noexcept = default;

                void playMusic() noexcept final
                {
                    _music.play();
                }

                void pauseMusic() noexcept final
                {
                    _music.pause();
                }

                void stopMusic() noexcept final
                {
                    _music.stop();
                }

                void makeMusicLoop(bool const &isLoop) noexcept final
                {
                    _music.setLoop(isLoop);
                }

                void setMusicVolume(float const &volume) noexcept final
                {
                    _music.setVolume(volume);
                }

                bool setMusicFromPath(std::string const &filePath, bool const &isLoop, float const &volume) final
                {
                    if (doesFileExist(filePath)) {
                        try {
                            _music.openFromFile(filePath);
                        } catch(const std::exception& e) {
                            throw SoundError(UNOPENABLE_SOUND(filePath));
                        }
                        makeMusicLoop(isLoop);
                        setMusicVolume(volume);
                        return true;
                    }
                    return false;
                };

            protected:
            private:
                sf::Music _music;
        };
    }
}

#endif /* !SOUND_HPP_ */
