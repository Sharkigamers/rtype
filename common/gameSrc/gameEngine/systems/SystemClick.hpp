/*
** EPITECH PROJECT, 2020
** SystemClick
** File description:
** SystemClick
*/

#ifndef SYSTEMCLICK_HPP_
#define SYSTEMCLICK_HPP_
#include <tuple>

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

#include "UdpClientNetwork.hpp"


namespace rtype::common {
    class SystemClick : public Isystem {
        public:
            SystemClick() = default;
            ~SystemClick() override = default;
            
            button_type update(rtype::common::Manager &manager, rtype::common::Event &event, const std::string &ip) noexcept
            {
                rtype::common::Mouse mouse;
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities();

                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_ROOM))) {
                        auto sprite = manager.getComponent<SpriteComponent>(x);
                        auto button = manager.getComponent<ButtonComponent>(x);
                        auto room = manager.getComponent<RoomComponent>(x);

                        if (event.isMousePressed() && isMouseInRect(mouse.getMousePosition(), sprite->img.getSpriteTextureRect()
                        , sprite->img.getSpritePosition(), sprite->img.getSpriteScale())) {
                            rtype::client::UdpClientNetwork clientUdp(ip, room->_port);
                            return button->button;
                        }
                    }
                }

                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_BUTTON))) {
                        auto sprite = manager.getComponent<SpriteComponent>(x);
                        auto button = manager.getComponent<ButtonComponent>(x);

                        if (event.isMousePressed() && isMouseInRect(mouse.getMousePosition(), sprite->img.getSpriteTextureRect()
                        , sprite->img.getSpritePosition(), sprite->img.getSpriteScale())) {
                            return button->button;
                        }
                    }
                }
            }
        protected:
        private:
            bool isMouseInRect(std::pair<float, float> mousePos, std::tuple<int, int, int, int> spriteRect, std::pair<int, int> spritePos,std::pair<float, float> spriteScale)
            {
                if (spritePos.first <= mousePos.first && mousePos.first <= spritePos.first + std::get<2>(spriteRect) * spriteScale.first &&
                    spritePos.second <= mousePos.second && mousePos.second <= spritePos.second + std::get<3>(spriteRect) * spriteScale.second)
                    return true;
                return false;
            }
    };
}
#endif /* !SYSTEMCLICK_HPP_ */
