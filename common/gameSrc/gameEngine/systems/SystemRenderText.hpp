/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SystemRenderText
*/

#pragma once

#include <iostream>

#include "Systems.hpp"
#include "Manager.hpp"
#include "Types.hpp"
#include "TextComponent.hpp"

#include "Window.hpp"

namespace rtype::common  {
    class SystemRenderText : public Isystem {
        public:
            SystemRenderText() = default;
            ~SystemRenderText() override = default;

            void update(rtype::common ::Manager &manager, rtype::common ::Window &Window) {
                auto entities = manager.getEntitiesList();
                auto living = manager.getLivingEntities();    
                for (auto x:living) {
                    if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_RDR_TXT))) {
                        auto text = manager.getComponent<TextComponent>(x);
                        Window.drawText(text->text);
                    }
                }
            }
    };
}