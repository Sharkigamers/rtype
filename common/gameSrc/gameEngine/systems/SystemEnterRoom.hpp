/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SystemEnterRoom
*/

#ifndef SYSTEMENTERROOM_HPP_
#define SYSTEMENTERROOM_HPP_

#include "Systems.hpp"
#include "Manager.hpp"
#include "Types.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "ButtonComponent.hpp"
#include "RoomComponent.hpp"
#include "Mouse.hpp"
#include "Event.hpp"
#include "Types.hpp"
#include <tuple>


namespace rtype::common {
    class SystemEnterRoom : public Isystem {
        public:
            SystemEnterRoom() = default;
            ~SystemEnterRoom() override = default;
            
            int update(rtype::common::Manager &manager) noexcept
            {
                rtype::common::Mouse mouse;
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities();

                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_ROOM))) {
                        auto room = manager.getComponent<RoomComponent>(x);
                            return room->_port;
                        }
                    }
            }
        protected:
        private:
    };
}
#endif /* !SYSTEMENTERROOM_HPP_ */
