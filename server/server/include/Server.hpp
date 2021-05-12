/*
** EPITECH PROJECT, 2020
** OOP_babel_2019
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "TcpServer.hpp"
#include "AProtocol.hpp"
#include "RoomManager.hpp"
#include "DirectoryLoader.hpp"

#include <string>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <thread>

#ifndef RTYPE_CONFIG_PATH
    #define RTYPE_CONFIG_PATH "./files/server_config.json"
#endif

#include "IServer.hpp"

#include "JsonUtility.hpp"
#include "UdpServer.hpp"
#include "SignalHandler.hpp"
#include "Base64.hpp"

#include "Imonster.hpp"
#include "LoadMonster.hpp"

#include <fstream>

// #include "CCommandHandler.hpp"

inline bool fileExist(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

namespace rtype {
    namespace server {
        class Server : public rtype::server::IServer {
            public:
                Server(const std::string &);
                ~Server();

                int getPort() const { return _port; }
                std::string getDebugPath() const { return _debugPath; }

                bool popClientFromQueue();
                void handleNewMessage(rtype::server::ServerClient *);

                void init();
                void run();

                std::unique_ptr<rtype::server::TcpServer> &getTcpServer() { return _tcpServer; }
                // std::unique_ptr<rtype::server::CCommandHandler> &getCommandHandler() { return _commandHandler; }

                IServer *getInstance() final
                {
                    return this;
                }

                void sendFile(const std::string &fileName, const std::vector<std::string> &data, rtype::server::ServerClient &client)
                {
                    for (const auto &x : data) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(2));
                        const std::vector<std::string> current {x};
                        const std::map<std::string, std::string> newHeader = rtype::protocol::createHeader("DATA_CHUNK");
                        const std::map<std::string, std::string> newBody = rtype::protocol::createBody(current, rtype::protocol::emptyPos, fileName);

                        const std::shared_ptr<rtype::protocol::Message> newMessage = rtype::protocol::AProtocol::createMessage(1, rtype::common::JsonUtility::mapToJson(newHeader), rtype::common::JsonUtility::mapToJson(newBody), rtype::protocol::messageType::DATA_CHUNK);
                        client.writeToClient(*newMessage, [this](const boost::system::error_code &error, const long unsigned int read){(void)error;(void)read;});
                    }

                    const std::map<std::string, std::string> newHeader = rtype::protocol::createHeader("END_FILE_DOWNLOAD");
                    const std::map<std::string, std::string> newBody = rtype::protocol::createBody(rtype::protocol::emptyData, rtype::protocol::emptyPos, rtype::protocol::emptyId);

                    const std::shared_ptr<rtype::protocol::Message> newMessage = rtype::protocol::AProtocol::createMessage(1, rtype::common::JsonUtility::mapToJson(newHeader), rtype::common::JsonUtility::mapToJson(newBody), rtype::protocol::messageType::END_FILE_DOWNLOAD);
                    _tcpServer->writeToClient(client, *newMessage, [this](const boost::system::error_code &error, const long unsigned int read){(void)error;(void)read;});
                }

                bool isUp() const { return !_signalHandler.hasExited(); }

                void onClientConnection(rtype::server::ServerClient &);
                void onClientDisconnect(rtype::server::ServerClient &);
                void onCreateRoom(rtype::server::ServerClient &);
                void onGetRooms(rtype::server::ServerClient &);
                void onFileList(rtype::server::ServerClient &);
                void onFileDownload(rtype::server::ServerClient &, const rtype::protocol::Message &);
                void onError(rtype::server::ServerClient &, const char *);

                void handleCommand(rtype::server::ServerClient &, const rtype::protocol::Message &);

                void createMonsterFromPath(const std::string &);
                #if defined(_WIN32)
                    void createMonsterFromPath(const std::wstring &);
                #endif

            private:
                unsigned short findAvailablePort() const throw()
                {
                    unsigned short portAvailable = 0;
                    std::vector<unsigned short> copy(_portsAvailable.begin(), _portsAvailable.end());

                    for (const auto &port: _portsAvailable) {
                        for (const auto &serverPort: _roomManager.getListPort()) {
                            if (port == serverPort)
                                copy.erase(std::find(copy.begin(), copy.end(), port));
                        }
                    }
                    if (copy.size() > 0)
                        portAvailable = copy[0];
                    return portAvailable;
                };

                const std::array<unsigned short, 9> _portsAvailable = {
                    42423, 42424, 42425, 42427, 42428, 42429, 42430, 42431, 42432
                };
                
            private:
                std::unique_ptr<rtype::server::TcpServer> _tcpServer;
                std::vector<std::shared_ptr<rtype::server::ServerClient> > _clients;
                unsigned short _port;
                std::string _debugPath;
                rtype::utils::SignalHandler _signalHandler;
                rtype::room::RoomManager _roomManager; 
                
            private:
                rtype::api::DirectoryLoader _directoryLoader;
                std::vector<rtype::API::Imonster *> _monsterList;
                std::thread _threadDirectoryMonster;
                std::mutex _globalMutex;
                bool _isActive;
        };
    }
}

#endif /* !SERVER_HPP_ */
