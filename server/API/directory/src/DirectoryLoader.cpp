/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** DirectoryLoader
*/

#include "DirectoryLoader.hpp"

#include "Server.hpp"

rtype::api::DirectoryLoader::~DirectoryLoader()
{
}

void rtype::api::DirectoryLoader::openAndRead()
{
    std::filesystem::path dirPath(_path);

    if (std::filesystem::is_directory(dirPath)) {
        std::filesystem::directory_iterator dir(dirPath);
        for (const auto &x : dir) {
            
            #if defined(_WIN32)
                if (!isALib(x.path().generic_wstring())) continue;
                if (isANewEntry(x.path().generic_wstring())) {
                    _entries.push_back(x.path().generic_string());
                    reinterpret_cast<rtype::server::Server*>(_serverInstance)->createMonsterFromPath(*_entries.end());
                }
            #else
                if (!isALib(x.path().generic_string())) continue;
                if (isANewEntry(x.path().generic_string())) {
                    _entries.push_back(x.path().generic_string());
                    reinterpret_cast<rtype::server::Server*>(_serverInstance)->createMonsterFromPath(x.path().generic_string());
                }
            #endif
        }
    } else {
        throw std::runtime_error(_path + " is not a directory.\n");
    }
}

void rtype::api::DirectoryLoader::openAndRead(bool all)
{
    std::filesystem::path dirPath(_path);

    if (std::filesystem::is_directory(dirPath)) {
        std::filesystem::directory_iterator dir(dirPath);
        for (const auto &x : dir) {
            
            #if defined(_WIN32)
                if (!all && !isALib(x.path().generic_wstring())) continue;
                if (isANewEntry(x.path().generic_wstring())) {
                    _entries.push_back(x.path().generic_string());
                }
            #else
                if (!all && !isALib(x.path().generic_string())) continue;
                if (isANewEntry(x.path().generic_string())) {
                    _entries.push_back(x.path().generic_string());
                }
            #endif
        }
    } else {
        throw std::runtime_error(_path + " is not a directory.\n");
    }
}
