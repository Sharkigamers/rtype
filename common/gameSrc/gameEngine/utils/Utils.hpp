/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <fstream>

namespace rtype {
    namespace common {

        /* Utils Class */

        class Utils {
            public:
                Utils() {};
                ~Utils() noexcept {};

                bool doesFileExist(std::string const &filePath)
                {
                    std::ifstream fileExist(filePath);

                    if (fileExist)
                        return true;
                    return false;
                }

            protected:
            private:
        };
    }
}

#endif /* !UTILS_HPP_ */
