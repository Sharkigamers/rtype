/*
** EPITECH PROJECT, 2020
** EntityManager.hpp
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <vector>
#include <algorithm>
#include <array>
#include <queue>
#include "Types.hpp"
#include "Entity.hpp"


namespace rtype {
    namespace common {
        class EntityManager {
            public:
                EntityManager()
                {
                    for (std::uint32_t i = 0; i <= MAX_ENTITIES; ++i) {
                        _listId.push(i);
                    }    
                };
                EntityManager(EntityManager &other)
                {
                    if (&other != this)
                    {
                        this->_listId = other._listId;
                        this->_entityArray = other._entityArray;
                        this->_livingEntities = other._livingEntities;
                    }
                }
                ~EntityManager() = default;

                EntityManager &operator=(const EntityManager &other)
                {
                    if (&other != this)
                    {
                        this->_listId = other._listId;
                        this->_entityArray = other._entityArray;
                        this->_livingEntities = other._livingEntities;
                    }
                    return (*this);
                }

                std::uint32_t createEntity()
                {
                    EntityEcs tmpEcs;
                    rtype::common::Cuuid tmp;
                    std::uint32_t id = _listId.front();
                    tmpEcs.id = id;
                    tmpEcs.uuid = tmp; 
                    Entity ent = Entity(tmpEcs);
                    
                    _entityArray[id] = ent;
                    _livingEntities.push_back(id);
                    _listId.pop();
                    return(id);
                };
                void destroyEntity(std::uint32_t id)
                {
                    if ((std::find(_livingEntities.begin(), _livingEntities.end(), id)) != _livingEntities.end()
                    && (std::find(_entityArray.begin(), _entityArray.end(), id)) != _entityArray.end()) {
                        _livingEntities.erase(std::find(_livingEntities.begin(), _livingEntities.end(), id));
                        _listId.push(id);
                    }
                };

                std::vector<std::uint32_t> getLivingEntities() const noexcept
                {
                    return (_livingEntities);
                }

                rtype::common::Cuuid getUuidById(uint32_t id) const {
                    return (_entityArray[id].getEntityUuid());
                }
                
                std::array<Entity, MAX_ENTITIES>_entityArray;
            protected:
            private:
                std::queue<std::uint32_t>_listId;
                std::vector<std::uint32_t>_livingEntities;
        };
    }
}

#endif /* !ENTITYMANAGER_HPP_ */
