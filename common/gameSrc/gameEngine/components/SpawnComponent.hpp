/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SpawnComponent
*/

#ifndef SPAWNCOMPONENT_HPP_
#define SPAWNCOMPONENT_HPP_
#include "Component.hpp"

namespace rtype::common
{
    class SpawnComponent : public Icomponent {
        public:
            SpawnComponent(const int &enemy = 0, const int &sec = 1, const int &spwn = 1)
            {
                _nbSpawn = enemy;
                _nbSecSpawn = sec;
                _nbSpawnEnm = spwn;

            }
            ~SpawnComponent() override = default;

            int _nbSpawn = 0;
            int _nbSecSpawn;
            int _nbSpawnEnm;
    
        protected:
        private:
    };
}

#endif /* !SPAWNCOMPONENT_HPP_ */
