/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** DirectoryLoader
*/

#ifndef DIRECTORYLOADER_HPP_
#define DIRECTORYLOADER_HPP_

#include <functional>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <iostream>

namespace rtype {
    namespace server {
        class IServer;
    };

    namespace api {
        class DirectoryLoader {
            public:
                #if defined(_WIN32)
                    public:
                        explicit DirectoryLoader(rtype::server::IServer *server, const std::wstring &path, bool isForLibs)
                            : _serverInstance(server), _path(path)
                        {

                        }

                        static inline bool isALib(const std::wstring &path)
                        {
                            bool res = false;

                            res = (path.find(L".dll", 0) != std::wstring::npos);
                            if (res == true)
                                return true;
                            res = (path.find(L".so", 0) != std::wstring::npos);
                            return res;
                        }
                    
                        bool isANewEntry(const std::wstring &entry) const
                        {
                            if (std::find(_entries.begin(), _entries.end(), entry) == _entries.end())
                                return true;
                            return false;
                        }
                    
                    private:
                        rtype::server::IServer *_serverInstance;
                        std::wstring _path;
                        std::vector<std::wstring> _entries;
                #else
                    public:
                        explicit DirectoryLoader(rtype::server::IServer *server, const std::string &path)
                            : _serverInstance(server), _path(path)
                        {

                        }

                        static inline bool isALib(const std::string &path)
                        {
                            bool res = false;

                            res = (path.find(".dll", 0) != std::string::npos);
                            if (res == true)
                                return true;
                            res = (path.find(".so", 0) != std::string::npos);
                            return res;
                        }
                        
                        bool isANewEntry(const std::string &entry) const
                        {
                            if (std::find(_entries.begin(), _entries.end(), entry) == _entries.end())
                                return true;
                            return false;
                        }

                        std::vector<std::string> getEntries() const
                        {
                            return _entries;
                        }

                    private:
                        rtype::server::IServer *_serverInstance;
                        std::string _path;
                        std::vector<std::string> _entries;   
                #endif

            public:
                ~DirectoryLoader();

                void openAndRead();
                void openAndRead(bool);
                void print() const
                {
                    for (const auto &x : _entries) {
                        std::cout << x << std::endl;
                    }
                }
            private:
                bool hasNewEntry;
        };

    }
}

#endif /* !DIRECTORYLOADER_HPP_ */
