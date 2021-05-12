/*
** EPITECH PROJECT, 2020
** LoadMonster
** File description:
** LoadMonster
*/

#ifndef LOADMONSTER_HPP_
#define LOADMONSTER_HPP_
#include "Imonster.hpp"
#include <dlfcn.h>
#include <stdlib.h> 
#include <locale>
#include <codecvt>
#if defined(_WIN32)
    #include <windows.h>
#endif

namespace rtype::API {
    class LoadMonster {
        public:
            LoadMonster() = default;
            ~LoadMonster() = default;
            
            #if defined(_WIN32)
            rtype::API::Imonster *load(const std::wstring &path) 
            {
                using convert_typeX = std::codecvt_utf8<wchar_t>;
                std::wstring_convert<convert_typeX, wchar_t> converterX;
                std::string tmp = converterX.to_bytes(path);
                
                HINSTANCE hinstLib; 
                rtype::API::Imonster *create;
                rtype::API::Imonster *enter;
                rtype::API::Imonster *out;
                hinstLib = LoadLibrary(TEXT(path)); 
            
                if (hinstLib != NULL) { 
                    create = (rtype::API::Imonster *) GetProcAddress(hinstLib, "entryPoint");
                    enter = (void (*)(rtype::API::Imonster*)) GetProcAddress(hinstLib, "enter")
                    out = (void (*)(rtype::API::Imonster*)) GetProcAddress(hinstLib, "out")
                    fFreeResult = FreeLibrary(hinstLib); 
                }
                enter();
                
                return (rtype::API::Imonster *)create();
            }
            #else
            rtype::API::Imonster *load(const std::string &path) 
            {
                void *handle = dlopen(path.c_str(), RTLD_LAZY);
                rtype::API::Imonster* (*create)();

                create = (rtype::API::Imonster* (*)())dlsym(handle, "entryPoint");
                rtype::API::Imonster* ret = (rtype::API::Imonster*)create();
                dlclose(handle);
                return ret;
            }
            #endif
        protected:
        private:
    };
}

#endif /* !LOADMONSTER_HPP_ */
