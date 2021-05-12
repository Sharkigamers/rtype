/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SystemeRender
*/

#pragma once
#include "Systems.hpp"
#include "Manager.hpp"
#include "Types.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "TextComponent.hpp"

#include "Window.hpp"

namespace rtype::common  {
    class SystemRender : public Isystem {
        public:
            SystemRender() = default;
            ~SystemRender() override = default;

            void update(rtype::common ::Manager &manager, rtype::common ::Window &Window) {
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities();    
                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_RDR))) {
                        auto position = manager.getComponent<PositionComponent>(x);
                        auto sprite = manager.getComponent<SpriteComponent>(x);
                        //auto text = manager.getComponent<TextComponent>(x);

                        if (sprite->_isRender) {
                            sprite->img.setSpritePosition(static_cast<float>(position->posX), static_cast<float>(position->posY));
                            Window.drawSprite(sprite->img);
                        }
                       // Window.drawText(text->_text);
                    }
                }
            }
    };
}