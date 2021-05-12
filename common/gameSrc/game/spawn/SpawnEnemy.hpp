/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SpawnEnemy
*/

#ifndef SPAWNENEMY_HPP_
#define SPAWNENEMY_HPP_

#include <map>
#include <string>

#include "OpenConfigFile.hpp"

#include "Manager.hpp"

#include "ClockComponent.hpp"
#include "EnemyTagComponent.hpp"
#include "SpawnComponent.hpp"

namespace rtype::common {
class SpawnEnemy {
    public:
        SpawnEnemy();
        ~SpawnEnemy();

        static uint16_t initSpawn(
                std::map<std::string, std::string> params,
                rtype::common::Manager &manager
            ) noexcept
            {
                std::uint32_t spawn = manager.createEntity();

                manager.addComponent<rtype::common::ClockComponent>(
                    spawn,
                    COMP_CLOCK
                );
                manager.addComponent<rtype::common::EnemyTagComponent>(
                    spawn,
                    COMP_ENEMY
                );
                manager.addComponent<rtype::common::SpawnComponent>(
                    spawn,
                    COMP_SPAWN,
                    std::stoi(params[rtype::common::SPAWN_ENEMY]),
                    std::stoi(params[rtype::common::SPAWN_SEC]),
                    std::stoi(params[rtype::common::SPAWN_ENEMY_SEC])
                );
                return (spawn);
            }
    protected:
    private:
};
}

#endif /* !SPAWNENEMY_HPP_ */
