/*
** EPITECH PROJECT, 2020
** Manager
** File description:
** Manager
*/

#ifndef MANAGER_HPP_
#define MANAGER_HPP_
#include <memory>
#include <typeindex>
#include "Types.hpp"
#include "ComponentManager.hpp"
#include "SystemsManager.hpp"
#include "EntityManager.hpp"

#include "PositionComponent.hpp"

namespace rtype {
    namespace common {
        class Manager {
            public:
                Manager()
                {
                    _entityManager = std::make_shared<rtype::common ::EntityManager>();
                    _componentManager = std::make_shared<rtype::common ::ComponentManager>();
                };
                ~Manager() = default;

                using posEntities_t = std::vector<std::pair<std::string, std::pair<uint16_t, uint16_t>>>;
                
                // Manager(const Manager &other)
                // {
                //     if (this != &other) {
                //         this->_componentManager = other._componentManager;
                //         this->_systemManager = other._systemManager;
                //         this->_entityManager = other._entityManager;
                //     }
                // }
                
                Manager &operator=(const Manager &other)
                {
                    if (this != &other) {
                        this->_componentManager = other._componentManager;
                        this->_entityManager = other._entityManager;
                    }
                    return *this;
                }
                std::uint32_t createEntity() 
                {
                    std::uint32_t res = _entityManager->createEntity();
                    return (res);
                }

                void removeEntity(std::uint32_t ent)
                {
                    _entityManager->destroyEntity(ent);
                }

                template<typename T, typename... _Args>
                void addComponent(std::uint32_t ent, componentSignature_e compSig, _Args&&... args)
                {
                    if (std::find(_entityManager->_entityArray.begin(), _entityManager->_entityArray.end(), _entityManager->_entityArray[ent])) {
                        _entityManager->_entityArray[ent].addComponent(compSig);
                        T *tmpComp = new T(std::forward<_Args>(args)...);
                        T typeName(std::forward<_Args>(args)...);
                        _componentManager->addComponent(_entityManager->_entityArray[ent], tmpComp, std::type_index(typeid(T)));
                    }
                }

                template<typename T>
                T *getComponent(std::uint32_t ent)
                {
                    return (_componentManager->getComponent<T>(ent));
                }

                template<typename T>
                void addSystem(systemSignature_e sysSig)
                {
                    rtype::common ::Systems<T> tmpSys;
                    T lopes;
                    tmpSys.createSystem(sysSig, lopes);
                }

                std::array<Entity, MAX_ENTITIES> getEntitiesList() const noexcept
                {
                    return (_entityManager->_entityArray);
                }

                std::vector<std::uint32_t> getLivingEntities() const noexcept
                {
                    return (_entityManager->getLivingEntities());
                }

                // std::vector<std::pair<std::string, std::pair<uint16_t, uint16_t>>>
                posEntities_t getEntitiesInfo() noexcept
                {
                    auto living = getLivingEntities();
                    auto entities = getEntitiesList();

                    posEntities_t res;
                    for (auto x:living) {
                        if (checkIfComponent(entities[x].getSignature(), COMP_POSITION)) {
                            auto position = this->getComponent<rtype::common ::PositionComponent>(x);
                            std::pair<std::string, std::pair<uint16_t, uint16_t>> positionByUuid = std::make_pair<std::string, std::pair<uint16_t, uint16_t>>(
                                entities[x].getEntityUuid().getUuidString(),
                                std::make_pair<uint16_t, uint16_t>(position->posX, position->posY)
                            );
                            res.push_back(positionByUuid);
                        }
                    }
                    return (res);
                }

                rtype::common::Cuuid getUuidById(uint32_t id) const {
                    return (_entityManager->getUuidById(id));
                }

            protected:
            private:
            std::shared_ptr<rtype::common ::EntityManager>_entityManager;
            std::shared_ptr<rtype::common ::ComponentManager> _componentManager;
        };
    }
}
#endif /* !MANAGER_HPP_ */
