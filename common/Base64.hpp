/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Base64
*/

#ifndef BASE64_HPP_
#define BASE64_HPP_

#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include <iostream>

namespace rtype {
    namespace common {
        namespace Base64 {
            inline std::string base64_decode(const std::string &val) {
                using namespace boost::archive::iterators;
                using It = transform_width<binary_from_base64<std::string::const_iterator>, 8, 6>;
                return boost::algorithm::trim_right_copy_if(std::string(It(std::begin(val)), It(std::end(val))), [](char c) {
                    return c == '\0';
                });
            }

            inline std::vector<std::string> splitString(const std::string &str, const int index)
            {
                int NumSubstrings = str.length() / index;
                std::vector<std::string> ret;

                for (auto i = 0; i < NumSubstrings; i++)
                {
                        ret.push_back(str.substr(i * index, index));
                }

                // If there are leftover characters, create a shorter item at the end.
                if (str.length() % index != 0)
                {
                        ret.push_back(str.substr(index * NumSubstrings));
                }


                return ret;
            }

            inline std::string base64_encode(const std::string &val) {
                using namespace boost::archive::iterators;
                using It = base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>;
                auto tmp = std::string(It(std::begin(val)), It(std::end(val)));
                return tmp.append((3 - val.size() % 3) % 3, '=');
            }
        }
    }
}

#endif /* !BASE64_HPP_ */
