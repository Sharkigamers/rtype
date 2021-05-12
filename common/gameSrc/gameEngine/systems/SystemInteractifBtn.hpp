/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SystemInteractifBtn
*/

#ifndef SYSTEMINTERACTIFBTN_HPP_
#define SYSTEMINTERACTIFBTN_HPP_

#include "Systems.hpp"
#include "Manager.hpp"
#include "Types.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "ButtonComponent.hpp"
#include "Mouse.hpp"
#include "Event.hpp"
#include "Types.hpp"
#include <tuple>


namespace rtype::common  {
    class SystemInteractifBtn : public Isystem{
        public:
            SystemInteractifBtn() = default;
            ~SystemInteractifBtn() override = default;
            
            void update(rtype::common ::Manager &manager, rtype::common ::Event &event) noexcept
            {
                rtype::common::Mouse mouse;
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities();

                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_IBUTTON))) {
                        auto sprite = manager.getComponent<SpriteComponent>(x);
                        auto button = manager.getComponent<ButtonComponent>(x);
                        if (isMouseInRect(mouse.getMousePosition(), sprite->img.getSpriteTextureRect()
                        , sprite->img.getSpritePosition())) {
                            if (button->_checkActifBtn == false) {
                            sprite->img.setSpriteFromFile("./client/assets/sprite/button_open.png", 1);
                            button->_checkActifBtn = true;
                            } else
                                button->_checkActifBtn = true;
                        } else if (button->_checkActifBtn == true){
                            sprite->img.setSpriteFromFile("./client/assets/sprite/button_close.png", 1);
                            button->_checkActifBtn = false;
                        }
                    }
                }
            }
        protected:
        private:
            bool isMouseInRect(std::pair<float, float> mousePos, std::tuple<int, int, int, int> spriteRect, std::pair<int, int> spritePos)
            {
                if (spritePos.first <= mousePos.first && mousePos.first <= spritePos.first + std::get<2>(spriteRect) &&
                    spritePos.second <= mousePos.second && mousePos.second <= spritePos.second + std::get<3>(spriteRect))
                    return true;
                return false;
            }
    };
}

#endif /* !SYSTEMINTERACTIFBTN_HPP_ */
