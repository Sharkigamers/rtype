/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** main
*/

#include <iostream>

#include "OpenConfigFile.hpp"
#include "Server.hpp"
#include "UdpServer.hpp"
#include "Room.hpp"

int main(int ac, char **av)
{
    rtype::server::Server server("./monsters/");

    try
    {
        server.init();
        server.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return EXIT_SUCCESS;
}