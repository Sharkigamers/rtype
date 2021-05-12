/*
** EPITECH PROJECT, 2020
** SystemTest.hpp
** File description:
** SystemTest
*/

#ifndef SYSTEMTEST_HPP_
#define SYSTEMTEST_HPP_
#include "Systems.hpp"
#include "Manager.hpp"
#include "Types.hpp"
#include "Player.hpp"
#include "Entity.hpp"

class SystemTest : public rtype::common ::Isystem {
    public:
        SystemTest()= default;
        ~SystemTest() = default;

        void update(int life, rtype::common ::Manager &manager) 
        {
            auto entities = manager.getEntitiesList();
            auto living = manager.getLivingEntities();

            for (auto x:living) {
                if (checkSignature(entities[x].getSignature(), flagTosignature(SYS_TEST))) {
                    auto comp = manager.getComponent<Player>(x);

                    int &lifeComp = comp->getLife();
                    lifeComp += life;
                }
            }
        }
    protected:
    private:
};

#endif /* !SYSTEMTEST_HPP_ */
