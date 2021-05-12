/*
** EPITECH PROJECT, 2020
** client
** File description:
** AUser
*/

#ifndef AUser_HPP_
#define AUser_HPP_

#include <string>

namespace rtype {
    namespace common {
        class AUser {
            public:
                AUser(const std::string &username, const std::string &password);
                AUser();
                ~AUser();

                std::string getUsername() const;
                std::string getPassword() const;
                
                void operator=(const AUser &);

                void authentificate(const std::string &, const std::string &);
            protected:
            private:
                void setUsername(const std::string &);
                void setPassword(const std::string &);

                std::string _username;
                std::string _password;
        };
    }
}

#endif /* !AUser_HPP_ */
