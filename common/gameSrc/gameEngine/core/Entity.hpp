/*
** EPITECH PROJECT, 2020
** Entity
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include "Types.hpp"
#include "Cuuid.hpp"

namespace rtype {
    namespace common {
        class Entity {
            public:
                Entity(){};
                Entity(EntityEcs ent) : _entity(ent) {};
                ~Entity() = default;

               
                Entity &operator=(const Entity &other)
                {
                    if (&other != this) {
                    _entity = other._entity;
                    _entitySignature = other._entitySignature;
                    }
                    return *this;
                }

                void addComponent(componentSignature_e compSig)
                {
                    _entitySignature.set(compSig);
                };
                
                void removeComponent(componentSignature_e compSig)
                {
                    _entitySignature.reset(compSig);
                };

                std::uint32_t getEntityId() const noexcept 
                {
                    return (_entity.id);
                }
                rtype::common::Cuuid getEntityUuid() const noexcept 
                {
                    return (_entity.uuid);
                }

                EntityEcs getEntityEcs() const noexcept 
                {
                    return (_entity);
                }
                
                bool operator==(const std::uint32_t id) {
                    return(getEntityId()==id);
                }

                bool operator==(const rtype::common::Cuuid &Cuuid) {
                    return(getEntityUuid()==Cuuid);
                }

                Signature getSignature() const noexcept {
                    return (_entitySignature);
                }

                void setSignature(Signature sig) noexcept {
                    _entitySignature = sig;
                }                
                bool operator==(const rtype::common::Entity &ent) {
                    return(_entitySignature==ent.getSignature());
                }

            protected:
            private:
                EntityEcs _entity;
                Signature _entitySignature;
        };
    }
}

#endif /* !ENTITY_HPP_ */
