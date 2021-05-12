/*
** EPITECH PROJECT, 2020
** OOP_babel_2019
** File description:
** Server
*/

#include "Server.hpp"
#include <iostream>

rtype::server::Server::Server(const std::string &monsterDirectory)
    : _signalHandler(), _roomManager(), _directoryLoader(this, monsterDirectory), _threadDirectoryMonster([this]() {
        _isActive = true;

        while (_isActive) {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            _globalMutex.lock();
            try
            {
                _directoryLoader.openAndRead();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            _globalMutex.unlock();
        }
    })
{
}

rtype::server::Server::~Server()
{
    _isActive = false;
    _threadDirectoryMonster.join();
}

void rtype::server::Server::init()
{
    boost::property_tree::ptree root;

    try
    {
        boost::property_tree::read_json(RTYPE_CONFIG_PATH, root);
        _port = root.get<unsigned short>("PORT");
        // bool isIpV4 = root.get<bool>("PREFER_IP_V4");
        _debugPath = root.get<std::string>("LOG.DEBUG_PATH");
        _tcpServer = std::make_unique<rtype::server::TcpServer>(true, _port, getInstance());
    }
    catch(const std::exception& e)
    {
        throw e;
    }
}

bool rtype::server::Server::popClientFromQueue()
{
    if (_tcpServer->isNewClientAvailable() == true) {
        std::shared_ptr<rtype::server::ServerClient> lastClient = _tcpServer->getLastClient();
        _clients.push_back(lastClient);
        std::cout << "Oui" << std::endl;
        return true;
    }
    return false;
}

void rtype::server::Server::handleNewMessage(rtype::server::ServerClient* client)
{
    std::shared_ptr<rtype::protocol::Message> incomingMessage = client->getLastMessage();

    handleCommand(*client, *incomingMessage);
}

void rtype::server::Server::run()
{
    _tcpServer->waitClient();
    _tcpServer->getIoService().run();
}

void noop()
{}

void rtype::server::Server::createMonsterFromPath(const std::string &path)
{
    rtype::API::LoadMonster monsterLoader;

    std::cout << "heerrreee" << path << std::endl;

    _monsterList.push_back(monsterLoader.load(path));
}

#if defined(_WIN32)
void rtype::server::Server::createMonsterFromPath(const std::wstring &path)
{
    rtype::API::LoadMonster monsterLoader;

    _monsterList.push_back(monsterLoader.load(path));
}
#endif

void rtype::server::Server::onClientConnection(rtype::server::ServerClient &client)
{
    onGetRooms(client);
}

void rtype::server::Server::onClientDisconnect(rtype::server::ServerClient &client)
{
}

void rtype::server::Server::onCreateRoom(rtype::server::ServerClient &client)
{
    uint16_t port = findAvailablePort();
    if (!port)
        throw std::runtime_error("No available ports");
    _roomManager.createRoom(port, _monsterList);
    std::vector<rtype::room::RoomInfo> rooms = _roomManager.getListRoomInfo();
    const std::vector<std::string> data {std::to_string(rooms[rooms.size() - 1].Port()), std::to_string(rooms[rooms.size() - 1].nbPlayers()), rooms[rooms.size() - 1].Id().getUuidString()};
    
    const std::map<std::string, std::string> header = rtype::protocol::createHeader("GET_ROOMS");
    const std::map<std::string, std::string> body = rtype::protocol::createBody(data, rtype::protocol::emptyPos, rtype::protocol::emptyId);
    const std::shared_ptr<rtype::protocol::Message> message = rtype::protocol::AProtocol::createMessage(0, rtype::common::JsonUtility::mapToJson(header), rtype::common::JsonUtility::mapToJson(body), rtype::protocol::messageType::RESPONSE_OK);

    client.writeToClient(*message, [this](const boost::system::error_code& error, const long unsigned int read){ (void)error;(void)read;});
}

void rtype::server::Server::onGetRooms(rtype::server::ServerClient &client)
{
    const std::pair<uint32_t, uint32_t> pos = {0, 0};

    for (const auto &x : _roomManager.getListRoomInfo()) {
        const std::vector<std::string> data = {std::to_string(x.Port()), std::to_string(x.nbPlayers())};
        const std::map<std::string, std::string> header = rtype::protocol::createHeader("GET_ROOMS");
        const std::map<std::string, std::string> body = rtype::protocol::createBody(data, pos, x.Id());

        const std::shared_ptr<rtype::protocol::Message> message = rtype::protocol::AProtocol::createMessage(1, rtype::common::JsonUtility::mapToJson(header), rtype::common::JsonUtility::mapToJson(body), rtype::protocol::messageType::RESPONSE_OK);

        client.writeToClient(*message, [this](const boost::system::error_code &error, const long unsigned int read){(void)error; (void)read;});
    }
}

void rtype::server::Server::onFileList(rtype::server::ServerClient &client)
{
    rtype::api::DirectoryLoader loader(this, "./assets");

    // True pour spécifier qu'on prend tous les fichiers du directory
    loader.openAndRead(true);
    const std::vector<std::string> data = loader.getEntries();

    const std::map<std::string, std::string> header = rtype::protocol::createHeader("FILE_LIST");
    const std::map<std::string, std::string> body = rtype::protocol::createBody(data, rtype::protocol::emptyPos, rtype::protocol::emptyId);
    const std::shared_ptr<rtype::protocol::Message> message = rtype::protocol::AProtocol::createMessage(1, rtype::common::JsonUtility::mapToJson(header), rtype::common::JsonUtility::mapToJson(body), rtype::protocol::messageType::RESPONSE_OK);

    client.writeToClient(*message, [this](const boost::system::error_code &error, const long unsigned int read){(void)error; (void)read;});
}

void rtype::server::Server::onFileDownload(rtype::server::ServerClient &client, const rtype::protocol::Message &message)
{
    std::map<std::string, std::string> body = message.parseBody();
    const std::vector<std::string> data = rtype::protocol::unformatData(body["DATA"]);
    const std::string fileName = data[0];

    if (fileExist(fileName)) {
        std::ifstream ifs(fileName);
        std::string rawData((std::istreambuf_iterator<char>(ifs)),
                       (std::istreambuf_iterator<char>()));
        
        const std::string encoded = rtype::common::Base64::base64_encode(rawData);

        const std::vector<std::string> newData = rtype::common::Base64::splitString(encoded, 1024);
        const std::vector<std::string> initData {std::to_string(newData.size()), fileName};
        const std::map<std::string, std::string> newHeader = rtype::protocol::createHeader("START_FILE_DOWNLOAD");
        const std::map<std::string, std::string> newBody = rtype::protocol::createBody(newData, rtype::protocol::emptyPos, rtype::protocol::emptyId);

        const std::shared_ptr<rtype::protocol::Message> newMessage = rtype::protocol::AProtocol::createMessage(1, rtype::common::JsonUtility::mapToJson(newHeader), rtype::common::JsonUtility::mapToJson(newBody), rtype::protocol::messageType::START_FILE_DOWNLOAD);
        _tcpServer->writeToClient(client, *newMessage, [this](const boost::system::error_code &error, const long unsigned int read){(void)error;(void)read;});
        sendFile(fileName, newData, client);
    } else {
        onError(client, "Unknown file.");
    }
}

void rtype::server::Server::onError(rtype::server::ServerClient &client, const char *error)
{
    const std::vector<std::string> data {error};
    const std::map<std::string, std::string> header = rtype::protocol::createHeader("RESPONSE_KO");
    const std::map<std::string, std::string> body = rtype::protocol::createBody(data, rtype::protocol::emptyPos, rtype::protocol::emptyId);

    const std::shared_ptr<rtype::protocol::Message> message = rtype::protocol::AProtocol::createMessage(1, rtype::common::JsonUtility::mapToJson(header), rtype::common::JsonUtility::mapToJson(body), rtype::protocol::messageType::RESPONSE_KO);

    client.writeToClient(*message, [this](const boost::system::error_code &error, const long unsigned int read){(void)error;(void)read;});
}

void rtype::server::Server::handleCommand(rtype::server::ServerClient &client, const rtype::protocol::Message &message)
{
    const std::map<std::string, std::string> headerInfo = message.parseHeader();
    
    try
    {
        switch (rtype::protocol::messageTypeMap.at(headerInfo.at("TYPE")))
        {
            case rtype::protocol::messageType::CREATE_ROOM:
                onCreateRoom(client);
                break;
            case rtype::protocol::messageType::GET_ROOMS:
                onGetRooms(client);
                break;
            case rtype::protocol::messageType::FILE_DOWNLOAD:
                onFileDownload(client, message);
                break;
            case rtype::protocol::messageType::FILE_LIST:
                onFileList(client);
                break;
            default:
                break;
        }
    }
    catch(const std::exception& e)
    {
        onError(client, e.what());
        std::cerr << e.what() << '\n';
    }   
}
