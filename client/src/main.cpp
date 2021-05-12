/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** main
*/

#include <iostream>
#include "UdpClientNetwork.hpp"

#include "MainLoop.hpp"

int main(int ac, char **av)
{
    rtype::client::MainLoop mainLoop;
    
    if (ac != 2)
        return 84;
    mainLoop.run(std::string(av[1]));
    //rtype::client::TcpClient client("127.0.0.1", 42424);
    // // rtype::client::UdpClientNetwork clientUdp("91.160.124.183", 42423);
    // bool lopes = false;

    // while (1) {
    //     if (client.hasNewMessage() == true) {
    //         std::shared_ptr<rtype::protocol::Message> message = client.getLastMessage();

    //         const std::map<std::string, std::string> headerInfo = message->parseHeader();
    
    //         uint16_t type = rtype::protocol::messageTypeMap.at(headerInfo.at("TYPE"));

    //         if (type == rtype::protocol::START_FILE_DOWNLOAD) {
    //             uint32_t nbPackets = 0;
    //             std::map<std::string, std::string> body = message->parseBody();
                
    //             std::vector<std::string> data = rtype::protocol::unformatData(body["DATA"]);
    //             client.startDownload("bigga.png", static_cast<uint32_t>(std::stoi(data[0])));
    //         }

    //         if (type == rtype::protocol::DATA_CHUNK || type == rtype::protocol::END_FILE_DOWNLOAD) {
    //             client.getFileDownload()->addNewMessage(message);
    //         }

    //         // if (lopes == false) {
    //         //     client.downloadRessource("lopes.png");
    //         //     lopes = true;
    //         // }
            
    //     }
            
    // }
    return 0;
}