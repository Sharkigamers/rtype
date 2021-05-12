/*
** EPITECH PROJECT, 2020
** OOP_babel_2019
** File description:
** IProtocol
*/

#ifndef IPROTOCOL_HPP_
#define IPROTOCOL_HPP_

#include <algorithm>
#include <sstream>
#include <string>
#include <map>
#include <string.h>
#include "JsonUtility.hpp"
#include "Cuuid.hpp"

#include <fstream>
#include <boost/serialization/access.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace rtype {
    namespace protocol {

        static const std::string CURRENT_VERSION = "RType: V1";
        static const uint16_t MAX_PATH_LENGTH = 128;

        using rect_t = int[4];

        enum messageType : uint16_t {
            NO_TYPE = 0,

            // Response codes
            RESPONSE_OK = 100,
            RESPONSE_KO = 101,

            // Room codes
            GET_ROOMS = 200,
            CREATE_ROOM = 201,
            ROOM_ERROR = 202,
            JOIN_ROOM = 203,

            // Entity codes
            ENTITY_CREATE = 300,
            ENTITY_DESTROY = 301,
            ENTITY_UPDATE_POSITION = 302,

            // Player codes
            PLAYER_JOINED = 400,
            PLAYER_CREATE = 401,
            PLAYER_DESTROY = 402,
            PLAYER_DISCONNECTED = 403,

            // Player events
            PLAYER_UPDATE_POSITION = 410,
            PLAYER_POWER_UP = 411,
            PLAYER_SHOOT = 412,

            // IA codes
            IA_CREATE = 500,
            IA_DESTROY = 501,

            // IA events
            IA_UPDATE_POSITION = 510,
            IA_POWER_UP = 511,
            IA_SHOOT = 512,

            // File events
            FILE_LIST = 600,
            FILE_DOWNLOAD = 601,
            START_FILE_DOWNLOAD = 602,
            DATA_CHUNK = 603,
            END_FILE_DOWNLOAD = 604
        };
        const std::map<std::string, messageType> messageTypeMap {
            {"NO_TYPE", NO_TYPE},
            {"RESPONSE_OK", RESPONSE_OK},
            {"RESPONSE_KO", RESPONSE_KO},
            {"GET_ROOMS", GET_ROOMS},
            {"CREATE_ROOM", CREATE_ROOM},
            {"ROOM_ERROR", ROOM_ERROR},
            {"ENTITY_CREATE", ENTITY_CREATE},
            {"ENTITY_DESTROY", ENTITY_DESTROY},
            {"ENTITY_UPDATE_POSITION", ENTITY_UPDATE_POSITION},
            {"PLAYER_JOINED", PLAYER_JOINED},
            {"PLAYER_CREATE", PLAYER_CREATE},
            {"PLAYER_DESTROY", PLAYER_DESTROY},
            {"PLAYER_DISCONNECTED", PLAYER_DISCONNECTED},
            {"PLAYER_UPDATE_POSITION", PLAYER_UPDATE_POSITION},
            {"PLAYER_POWER_UP", PLAYER_POWER_UP},
            {"PLAYER_SHOOT", PLAYER_SHOOT},
            {"IA_CREATE", IA_CREATE},
            {"IA_DESTROY", IA_DESTROY},
            {"IA_UPDATE_POSITION", IA_UPDATE_POSITION},
            {"IA_POWER_UP", IA_POWER_UP},
            {"IA_SHOOT", IA_SHOOT},
            {"FILE_LIST", FILE_LIST},
            {"FILE_DOWNLOAD", FILE_DOWNLOAD},
            {"START_FILE_DOWNLOAD", START_FILE_DOWNLOAD},
            {"DATA_CHUNK", DATA_CHUNK},
            {"END_FILE_DOWNLOAD", END_FILE_DOWNLOAD}
        };

        enum messageHeader : uint16_t {
            FRAME = 10,
            VERSION = 11,
            TYPE = 12
        };

        const std::map<messageHeader, std::string> messageHeaderMap {
            {FRAME, "FRAME"},
            {VERSION, "VERSION"},
            {TYPE, "TYPE"},
        };

        enum messageBody : uint16_t {
            DATA = 20,
            POSITION = 21,
            ID = 22,
        };

        const std::map<std::string, messageBody> messageBodyMap {
            {"DATA", DATA},
            {"POSITION", POSITION},
            {"ID", ID}
        };

        static const std::pair<uint32_t, uint32_t> emptyPos = {0, 0};
        static const std::vector<std::string> emptyData;
        static const rtype::common::Cuuid emptyId(true);

        const inline std::map<std::string, std::string> createHeader(const std::string &type, uint32_t frame = 0)
        {
            const std::map<std::string, std::string> objects = {
                {"FRAME", std::to_string(frame)},
                {"VERSION", CURRENT_VERSION},
                {"TYPE", type}
            };

            return objects;
        };

        std::vector<std::string> inline unformatData(std::string &data)
        {
            std::vector<std::string> res;
            std::stringstream stream(data);
            std::string tmp;

            while (std::getline(stream, tmp, ':')) {
                res.emplace_back(tmp);
            }
            return res;
        }

        std::string inline formatData(const std::vector<std::string> &data)
        {
            std::string res;

            for (const auto &x : data)
                res += (x + ":");
            return res;
        }

        const std::string inline formatPosition(const std::pair<uint32_t, uint32_t> &pos)
        {
            const std::string res = std::to_string(pos.first) + ":" + std::to_string(pos.second);

            return res;
        }

        const inline std::map<std::string, std::string> createBody(const std::vector<std::string> &data, std::pair<uint32_t, uint32_t> pos, const rtype::common::Cuuid &cuuid)
        {
            const std::map<std::string, std::string> objects = {
                {"DATA", formatData(data)},
                {"POSITION", formatPosition(pos)},
                {"ID", cuuid.getUuidString()}
            };

            return objects;
        };

        enum InputType : uint8_t {
            NO_INPUT = 0,
            INPUT_UP = 1,
            INPUT_DOWN = 2,
            INPUT_LEFT = 4,
            INPUT_RIGHT = 8,
            INPUT_CLICK = 16
        };
        
        const inline std::map<std::string, std::string> createBody(const std::vector<std::string> &data, std::pair<uint32_t, uint32_t> pos, const std::string &id)
        {
            const std::map<std::string, std::string> objects = {
                {"DATA", formatData(data)},
                {"POSITION", formatPosition(pos)},
                {"ID", id}
            };

            return objects;
        };

        struct RoomMessage {
            public:
                RoomMessage(messageType type, const std::string &entity, uint32_t posX, uint32_t posY, rect_t rect, const std::string &path, uint32_t frame, InputType input = InputType::NO_INPUT)
                {
                    if (entity.length() > 36)
                        throw std::runtime_error("Entity " + entity + " too biiiig");
                    if (path.length() > MAX_PATH_LENGTH)
                        throw std::runtime_error("Path " + path + " too biiiig");
                    _type = type;
                    memcpy(_entity, entity.c_str(), 37);
                    _posX = posX;
                    _posY = posY;
                    memcpy(_rect, rect, sizeof(rect_t));
                    memcpy(_path, path.c_str(), path.length());
                    _currentFrame = frame;
                    _input = input;
                }

                RoomMessage()
                {
                    _type = NO_TYPE;
                    bzero(_entity, 37);
                    _posX = 0;
                    _posY = 0;
                    bzero(_rect, sizeof(rect_t));
                    bzero(_path, MAX_PATH_LENGTH);
                    _currentFrame = 0;
                }

                RoomMessage(const RoomMessage &other)
                {
                    if (&other != this) {
                        _type = other.getType();
                        memcpy(_entity, other.getEntity(), 37);
                        _posX = other.getPosX();
                        _posY = other.getPosY();
                        memcpy(_rect, other.getRect(), sizeof(rect_t));
                        memcpy(_path, other.getPath(), strlen(other.getPath()));
                        _input = other.getInput();
                    }
                }

                RoomMessage &operator=(const RoomMessage &other)
                {
                    if (&other != this) {
                        _type = other.getType();
                        memcpy(_entity, other.getEntity(), 37);
                        _posX = other.getPosX();
                        _posY = other.getPosY();
                        memcpy(_rect, other.getRect(), sizeof(rect_t));
                        memcpy(_path, other.getPath(), strlen(other.getPath()));
                        _input = other.getInput();
                    }
                    return *this;
                }

                messageType getType() const
                {
                    return _type;
                }

                char *getEntity() const
                {
                    char *res = nullptr;

                    memcpy(res, _entity, 37);
                    return res;
                }

                uint32_t getPosX() const
                {
                    return _posX;
                }
                uint32_t getPosY() const
                {
                    return _posY;
                }

                rect_t* getRect() const
                {
                    rect_t *rect;

                    memcpy(rect, _rect, sizeof(rect_t));
                    return rect;
                }

                char *getPath() const
                {
                    char *path;

                    memcpy(path, _path, strlen(_path));
                    return path;
                }

                uint32_t getFrame() const
                {
                    return _currentFrame;
                }

                InputType getInput() const
                {
                    return _input;
                }

                friend class boost::serialization::access;
                template<class Archive>
                void serialize(Archive& ar, const unsigned int version)
                {
                    (void)version;
                    ar & _type & _entity & _posX & _posY & _rect;
                }

            public:
                messageType _type;
                char _entity[37];
                uint32_t _posX;
                uint32_t _posY;
                rect_t _rect;
                char _path[MAX_PATH_LENGTH];
                uint32_t _currentFrame;
                InputType _input;
        };

        inline std::istream& operator>>(std::istream& in, RoomMessage& h) // non-const h
        {
            RoomMessage values; // use extra instance, for setting result transactionally
            in.read( reinterpret_cast<char*>(&values), sizeof(RoomMessage) );
            
            h = std::move(values);
            return in;
        };

        class Message {
            public:
                Message(bool isRequest, const std::string &header, const std::string &body, uint16_t status)
                    : _isRequest(isRequest), _header(header), _body(body), _status(status)
                {}

                Message(const Message &other)
                    : _isRequest(other.isRequest()), _header(other.getHeader()), _body(other.getBody()), _status(other.getStatus())
                {}

                Message &operator=(const Message &other)
                {
                    if (&other != this) {
                        _isRequest = other.isRequest();
                        _header = other.getHeader();
                        _body = other.getBody();
                        _status = other.getStatus();
                    }
                    return *this;
                }

                Message()
                    : _isRequest(false), _header(""), _body(""), _status(0)
                {};

                ~Message() {};

                bool isRequest() const
                {
                    return _isRequest;
                };

                std::map<std::string, std::string> parseHeader() const
                {
                    return rtype::common::JsonUtility::jsonToMap(_header);
                }

                std::map<std::string, std::string> parseBody() const
                {
                    return rtype::common::JsonUtility::jsonToMap(_body);
                }

                std::string getHeader() const
                {
                    return _header;
                }

                std::string getBody() const
                {
                    return _body;
                }

                uint16_t getStatus() const noexcept
                {
                    return _status;
                }

                friend class boost::serialization::access;
                template<class Archive>
                void serialize(Archive& ar, const unsigned int version)
                {
                    (void)version;
                    ar & _isRequest & _header & _body & _status;
                }

            private:
                bool _isRequest;
                std::string _header;
                std::string _body;
                uint16_t _status;
        };

    }
};

#endif /* !IPROTOCOL_HPP_ */
