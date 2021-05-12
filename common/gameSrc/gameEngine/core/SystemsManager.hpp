/*
** EPITECH PROJECT, 2020
** systemsManager.hpp
** File description:
** SystemsManager
*/

#ifndef SYSTEMSMANAGER_HPP_
#define SYSTEMSMANAGER_HPP_
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "Types.hpp"
#include "Systems.hpp"

namespace rtype {
    namespace common {
        class SystemsManager {
            public:
                SystemsManager() = default;
                SystemsManager(std::array<rtype::common ::Entity, MAX_ENTITIES> entityArray,std::vector<std::uint32_t>livingEntities): 
                _entityArray(entityArray),
                _livingEntities(livingEntities){};
                SystemsManager(const SystemsManager &other)
                {
                    if (&other != this)
                    {
                        this->_entityArray = other._entityArray;
                        this->_livingEntities = other._livingEntities;
                        this->_systemList = other._systemList;
                    }
                }
                ~SystemsManager() = default;
                
                SystemsManager operator=(const SystemsManager &other)
                {
                   if (&other != this)
                    {
                        this->_entityArray = other._entityArray;
                        this->_livingEntities = other._livingEntities;
                        this->_systemList = other._systemList;
                    }
                    return (*this);
                }
                
                void update(systemSignature sig)
                {
                    Signature tmp = flagTosignature(sig);
                    for (auto x:_livingEntities) {
                        std::cout << _entityArray[x].getSignature() << std::endl;
                        if (_entityArray[x].getSignature() == tmp) {
                            std::cout << "ECS Should be working" << std::endl;
                        }
                    }
                }

                void addSystem(Isystem &system) noexcept
                {
                    if (std::find(_systemList.begin(), _systemList.end(), system) != _systemList.end()) {
                        _systemList.push_back(system);
                    }
                }

                void removeSystem(Isystem &system) noexcept
                {
                    if (std::find(_systemList.begin(), _systemList.end(), system) != _systemList.end()) {
                        _systemList.erase(std::find(_systemList.begin(), _systemList.end(), system));
                    }
                }

                void signatureChange(Entity &ent, Signature entSig) noexcept
                {
                    _entityArray[ent.getEntityId()].setSignature(entSig);
                }
                
                void setEntityArray(std::array<rtype::common ::Entity, MAX_ENTITIES> arr) noexcept
                {
                    _entityArray = arr;
                }

                void setLivingEntities(std::vector<std::uint32_t> vec) noexcept
                {
                    _livingEntities = vec;
                }

                bool checkSignature(std::uint32_t ent, systemSignature_e sysSig)
                {
                    return (_entityArray[ent].getSignature() == flagTosignature(sysSig));
                }
            protected:
            private:
                std::array<rtype::common ::Entity, MAX_ENTITIES> _entityArray;
                std::vector<std::uint32_t>_livingEntities;
                std::vector<Isystem> _systemList;
        };
    }
}
#endif /* !SYSTEMSMANAGER_HPP_ */