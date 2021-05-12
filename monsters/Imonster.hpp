/*
** EPITECH PROJECT, 2020
** IMonster.hpp
** File description:
** Imonster
*/

#ifndef IMONSTER_HPP_
#define IMONSTER_HPP_
#include <string>

namespace rtype::API {
    class Imonster {
        public:
            virtual ~Imonster() = default;

            virtual std::string getPath() const = 0;

            virtual void setPath(const std::string &path) = 0;

        protected:
        private:
    };
}
#endif /* !IMONSTER_HPP_ */
