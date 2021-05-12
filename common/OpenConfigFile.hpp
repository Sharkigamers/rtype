/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** OpenConfigFile
*/

#ifndef OPENCONFIGFILE_HPP_
#define OPENCONFIGFILE_HPP_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <iostream>

#include <map>

#include "Utils.hpp"

namespace rtype {
    namespace common {

        static const std::string DEFINED_MAGIC_KEY = "333LOPES333";

        /* List of named parameters */

        static const std::string MAGIC_KEY = "MagicKey";

        static const std::string WINDOW_WIDTH = "WindowWidth";
        static const std::string WINDOW_HEIGHT = "WindowHeight";
        static const std::string WINDOW_BBP = "WindowBitsPerPixel";
        static const std::string WINDOW_NAME = "WindowName";
        static const std::string WINDOW_SCREEN_MODE = "WindowFullscreen";
        static const std::string WINDOW_CURSOR_MODE = "WindowCursorVisible";
        static const std::string WINDOW_FPS = "WindowFrameRate";

        static const std::string MOUSE_POSX = "MousePositionX";
        static const std::string MOUSE_POSY = "MousePositionY";

        static const std::string MUSIC_PATH = "MusicPath";
        static const std::string MUSIC_LOOPER = "MusicLoop";
        static const std::string MUSIC_VOLUME = "MusicVolume";

        static const std::string TEXTURE_PATH = "TexturePath";
        static const std::string MAKE_TEXTURE_SMOOTH = "MakeSmooth";
        static const std::string SPRITE_SCALEX = "SpriteScaleX";
        static const std::string SPRITE_SCALEY = "SpriteScaleY";
        static const std::string SPRITE_POSX = "SpritePositionX";
        static const std::string SPRITE_POSY = "SpritePositionY";
        static const std::string SPRITE_ORIGINX = "SpriteOriginX";
        static const std::string SPRITE_ORIGINY = "SpriteOriginY";
        static const std::string SPRITE_ANG_ROTATIONX = "SpriteAngularRotationX";
        static const std::string SPRITE_ANG_ROTATIONY = "SpriteAngularRotationY";
        static const std::string TEXTURE_LEFT = "TextureLeft";
        static const std::string TEXTURE_TOP = "TextureTop";
        static const std::string TEXTURE_WIDTH = "TextureWidth";
        static const std::string TEXTURE_HEIGHT = "TextureHeight";
        static const std::string IS_RENDER = "IsRender";


        static const std::string TEXT_STRING = "Text";
        static const std::string FONT_PATH = "FontPath";
        static const std::string TEXT_SIZE = "TextSize";
        static const std::string TEXT_LINESPACE = "TextLineSpace";
        static const std::string TEXT_CHARSPACE = "TextCharacterSpace";
        static const std::string TEXT_STYLE = "TextStyle";
        static const std::string TEXT_COLOR = "TextColor";
        static const std::string TEXT_POSX = "TextPositionX";
        static const std::string TEXT_POSY = "TextPositionY";
        static const std::string TEXT_ANG_ROTATIONX = "TextAngularRotationX";
        static const std::string TEXT_ANG_ROTATIONY = "TextAngularRotationY";
        static const std::string TEXT_SCALEX = "TextScaleX";
        static const std::string TEXT_SCALEY = "TextScaleY";
        static const std::string TEXT_ORIGINX = "TextOriginX";
        static const std::string TEXT_ORIGINY = "TextOriginY";
        static const std::string TEXT_MOVING = "TextMoving";
        static const std::string TEXT_ROTATING = "TextRotating";
        static const std::string TEXT_SCALING = "TextScaling";

        static const std::string VELOCITY_POSX = "VelocityX";
        static const std::string VELOCITY_POSY = "VelocityY";

        static const std::string ANIMATION = "Animated";
        static const std::string ANIMATION_WIDTH = "AnimationWidthLimit";
        static const std::string ANIMATION_OFFSET = "AnimationOffset";
        static const std::string ANIMATION_SECOND = "AnimationSecond";

        static const std::string DAMAGES = "Damages";
        static const std::string HP = "Hp";

        static const std::string STAY_IN_SCREEN = "InScreen";
        static const std::string WIDTH_MAX_SCREEN = "WidthMaxScreen";
        static const std::string HEIGHT_MAX_SCREEN = "HeightMaxScreen";

        static const std::string IS_CONTROLLABLE = "isControllable";
        static const std::string IS_FROM_RIGHT_TO_LEFT = "fromRightToLeft";

        static const std::string SPAWN_ENEMY = "SpawnEnemy";
        static const std::string SPAWN_SEC = "SpawnSec";
        static const std::string SPAWN_ENEMY_SEC = "SpawnEnemySec";

        /* Error OpenConfigFile class */

        class OpenConfigFileError : public std::exception {

            public:
                OpenConfigFileError(const std::string &message) : _errorMessage(message) {};
                ~OpenConfigFileError() = default;

                const char *what() const throw() { return _errorMessage.c_str(); }

            private:
                std::string _errorMessage;
        };

        /* OpenConfigFile Class */

        class OpenConfigFile : public rtype::common ::Utils {
            public:
                inline static const std::string UNFOUND_FILE(std::string const &path) { return "Unfound file at path: '" + path + "'"; };
                inline static const std::string UNFOUND_MAGICKEY(std::string const &path) { return "Magic key not found in folder located at path: '" + path + "'"; };
                inline static const std::string UNMAPPABLE_DATA() { return "Unmappable from the config file data"; };

            public:
                OpenConfigFile(std::string const &filePath)
                {
                    openConfigFile(filePath);
                    setMapData();
                };
                ~OpenConfigFile() = default;

                void openConfigFile(std::string const &filePath)
                {
                    if (doesFileExist(filePath)) {
                        try {
                            boost::property_tree::read_json(filePath, _root);

                            if (_root.get<std::string>("MagicKey").compare(DEFINED_MAGIC_KEY) != 0)
                                throw OpenConfigFileError(UNFOUND_MAGICKEY(filePath));
                        } catch(const std::exception& e) {
                            throw OpenConfigFileError(UNFOUND_FILE(filePath));
                        }
                    } else
                        throw OpenConfigFileError(UNFOUND_FILE(filePath));
                }

                void setMapData()
                {
                    try {
                        for (boost::property_tree::ptree::const_iterator it = _root.begin(); it != _root.end(); it++) {
                            _data[it->first] = it->second.get_value<std::string>();
                        }
                    } catch(const std::exception& e) {
                        throw OpenConfigFileError(UNMAPPABLE_DATA());
                    }
                }

                std::map<std::string, std::string> getData() const
                {
                    return _data;
                }

            protected:
            private:
                boost::property_tree::ptree _root;
                std::map<std::string, std::string> _data = {};
        };
    }
}

#endif /* !OPENCONFIGFILE_HPP_ */
