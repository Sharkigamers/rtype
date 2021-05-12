/*
** EPITECH PROJECT, 2020
** ComponentManager
** File description:
** ComponentManager
*/

#ifndef COMPONENTMANAGER_HPP_
#define COMPONENTMANAGER_HPP_
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <any>
#include <typeindex>
#include "Types.hpp"
#include "Entity.hpp"
#include "Component.hpp"

namespace rtype {
    namespace common {
        class ComponentManager {
            public:
                ComponentManager() = default;
                ComponentManager(const ComponentManager &other)
                {
                    if (&other != this) {
                        this->_componentMap = other._componentMap;
                        this->_typeMap = other._typeMap;
                    }
                }
                ~ComponentManager()
                {
                    for (auto x:_componentMap) {
                        for (auto z: x.second)
                            delete z;
                    }
                };

                ComponentManager &operator=(const ComponentManager &other)
                {
                    if (&other != this) {
                        this->_componentMap = other._componentMap;
                        this->_typeMap = other._typeMap;
                    }
                    return (*this);
                }

                void addComponent(Entity &ent, Icomponent *component, std::type_index type)
                {
                    if (_componentMap.count(ent.getEntityId())) {
                        if (std::find(_componentMap[ent.getEntityId()].begin(), _componentMap[ent.getEntityId()].end(), component) == _componentMap[ent.getEntityId()].end()) {
                            _componentMap[ent.getEntityId()].push_back(component);
                            _typeMap[ent.getEntityId()].push_back(type);
                        }
                    } else {
                        _componentMap[ent.getEntityId()] = std::vector<Icomponent *>();
                        _typeMap[ent.getEntityId()] = std::vector<std::type_index>();
                        addComponent(ent, component, type);
                    }
                }

                void removeComponent(Entity &ent, Icomponent *component, std::type_index type) noexcept
                {
                    (void)type;
                    if (_componentMap.count(ent.getEntityId())) {
                        _componentMap[ent.getEntityId()].erase(std::find(_componentMap[ent.getEntityId()].begin(), _componentMap[ent.getEntityId()].end(), component));
                    }
                }

                template<typename T>
                T *getComponent(std::uint32_t ent) noexcept
                {
                    if (_componentMap.count(ent)) {
                       for (size_t i = 0; i < _typeMap[ent].size(); ++i) {
                            if (_typeMap[ent][i] == std::type_index(typeid(T)))
                                return(static_cast<T *>(_componentMap[ent][i]));
                       }
                    }
                }
     
            protected:
            private:
                std::unordered_map<std::uint32_t, std::vector<Icomponent *>> _componentMap;
                std::unordered_map<std::uint32_t, std::vector<std::type_index>> _typeMap;
        };
    }
}

#endif /* !COMPONENTMANAGER_HPP_ */
