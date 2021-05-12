/*
** EPITECH PROJECT, 2020
** Leanbeast
** File description:
** Leanbeast
*/

#ifndef LEANBEAST_HPP_
#define LEANBEAST_HPP_

#include "Imonster.hpp"

namespace rtype::API {
    class Leanbeast : public Imonster {
        public:
            Leanbeast(const std::string &path);

            std::string getPath() const final;
            
            void setPath(const std::string &path) final;
           
        private:
            std::string _path;
    };
}

#endif /* !LEANBEAST_HPP_ */
