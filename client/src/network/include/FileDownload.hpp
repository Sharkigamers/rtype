/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** FileDownload
*/

#ifndef FILEDOWNLOAD_HPP_
#define FILEDOWNLOAD_HPP_

#include <string>
#include <vector>
#include <memory>
#include "IProtocol.hpp"
#include "Base64.hpp"

namespace rtype {
    namespace client {
        class FileDownload {
            public:
                FileDownload(const std::string &fileName, uint32_t nbPackets)
                    : _downloadInProgress(true), _fileName(fileName), _nbPackets(nbPackets)
                {}
                ~FileDownload() = default;

                bool isCompleted() const noexcept { return _downloadInProgress; }
                bool operator==(const std::string &file) const { return _fileName == file; }

                void addNewMessage(const std::shared_ptr<rtype::protocol::Message> &newMessage)
                {
                    using namespace rtype::protocol;
                    
                    uint16_t status = newMessage->getStatus();
                    if (status == DATA_CHUNK) {
                        std::cout << _dataVector.size() << " : " << _nbPackets - 1 << "\n";
                        _dataVector.push_back(newMessage);
                    } if (status == END_FILE_DOWNLOAD) {
                        _downloadInProgress = false;
                        saveFile();
                    }
                }

            private:
                void saveFile()
                {
                    std::string encoded;

                    for (const auto &x : _dataVector) {
                        std::map<std::string, std::string> body = x->parseBody();

                        encoded += rtype::protocol::unformatData(body.at("DATA"))[0];
                    }

                    std::string decoded = rtype::common::Base64::base64_decode(encoded);
                    std::ofstream file("lopes2.png");

                    file << decoded << std::endl;
                    file.close();

                    std::cout << "File : " << _fileName << " downloaded sucessfully !" << std::endl;

                    _downloadInProgress = false;
                    _dataVector.clear();
                }
            private:
                bool _downloadInProgress;
                std::vector<std::shared_ptr<rtype::protocol::Message> > _dataVector;
                std::string _fileName;
                uint32_t _nbPackets;
        };

    }
}

#endif /* !FILEDOWNLOAD_HPP_ */
