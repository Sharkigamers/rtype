/*
** EPITECH PROJECT, 2020
** Systems
** File description:
** Systems
*/

#ifndef SYSTEMS_HPP_
#define SYSTEMS_HPP_
#include "Types.hpp"

namespace rtype {
    namespace common {
        class Isystem {
            public:
                virtual ~Isystem() = default;
                bool operator==(const Isystem &lopes) {
                    return(&lopes == this);
                }
        };
    }
} 

namespace rtype {
    namespace common {
        template<typename T>
        class Systems : public Isystem {
            public:
                Systems() = default;
                ~Systems() = default;

                void createSystem(systemSignature_e sysSig, T &system) noexcept
                {
                    _systemData = std::make_pair(sysSig, system);
                }

                std::pair<systemSignature_e, T> getSystemData() const noexcept
                {
                    return (_systemData);
                }

            protected:
            private:
                std::pair<systemSignature_e, T> _systemData;
        };
    }
}

#endif /* !SYSTEMS_HPP_ */
