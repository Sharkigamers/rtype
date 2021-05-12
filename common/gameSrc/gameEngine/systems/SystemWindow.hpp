/*
** EPITECH PROJECT, 2020
** Window.hpp
** File description:
** Window
*/

#ifndef SYSTEMWINDOW_HPP_
#define SYSTEMWINDOW_HPP_
#include "Systems.hpp"
#include "Window.hpp"

class SystemWindow : public rtype::common ::Isystem {
    public:
        SystemWindow() 
        {};
        ~SystemWindow() = default;

        void update() const noexcept
        {
           Window lopes;
           while (1) {
               lopes.displayWindow();
           }
        }

    protected:
    private:
};

#endif /* !SYSTEMWINDOW_HPP_ */
