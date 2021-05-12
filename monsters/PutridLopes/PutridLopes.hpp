/*
** EPITECH PROJECT, 2020
** PutridLopes
** File description:
** PutridLopes
*/

#ifndef PUTRIDLOPES_HPP_
#define PUTRIDLOPES_HPP_

#include "Imonster.hpp"

namespace rtype::API {
    class PutridLopes : public Imonster {
        public:
            PutridLopes(const std::string &path);

            std::string getPath() const final;
            
            void setPath(const std::string &path) final;
           
        private:
            std::string _path;
    };
}

#endif /* !PUTRIDLOPES_HPP_ */
