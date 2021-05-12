/*
** EPITECH PROJECT, 2020
** Cuuid.hpp
** File description:
** Cuuid
*/

#ifndef CUUID_HPP_
#define CUUID_HPP_

#if defined (_WIN32)
	#include <rpc.h>
#else
	#include <uuid/uuid.h>
#endif

#include <string>
#include <memory>
#include <iostream>

// Encapsulation de la lib uuid.

namespace rtype {
    namespace common {
        
#if defined (_WIN32)
		class Cuuid {
		public:
			Cuuid()
			{
				char *tmp;

				UuidCreate(&_newId);
				UuidToString(&_newId, (RPC_CSTR*)(tmp));
				_strId = std::string(tmp);
				RpcStringFreeA((RPC_CSTR*)&tmp);
			};

			Cuuid(bool isEmpty)
			{
				(void)isEmpty;
				_strId = "0";
			}

			Cuuid(const std::string &id)
				: _strId(id)
			{
				UuidFromStringA((RPC_CSTR)id.c_str(), &_newId);
			}

			Cuuid(const Cuuid &other)
			{
				if (&other != this) {
					_strId = other.getUuidString();
					UuidFromStringA((RPC_CSTR)_strId.c_str(), &_newId);
				}
			}

			~Cuuid() = default;
			std::string getUuidString() const noexcept {
				return (_strId);
			};

			Cuuid &operator=(const Cuuid &other)
			{
				if (&other != this) {
					_strId = other.getUuidString();
					UuidFromString((RPC_CSTR)_strId.c_str(), &_newId);
				}
				return *this;
			}

			UUID *getUuid() {
				return &_newId;
			}

			bool operator==(Cuuid &uuid) {
				return(UuidCompare(&_newId, uuid.getUuid(), nullptr));
			}

			bool operator==(const std::string &strId) {
				return(_strId == strId);
			}
		protected:
		private:
			UUID _newId;
			std::string _strId;
		};
#else
		class Cuuid {
		public:
			Cuuid()
			{
				char *tmp = new char[37];

				uuid_generate(_newId);
				uuid_unparse_upper(_newId, tmp);
				_strId = std::string(tmp);
				delete[] tmp;
			};

			Cuuid(bool isEmpty)
			{
				(void)isEmpty;
				_strId = "0";
			}

			Cuuid(const std::string &id)
				: _strId(id)
			{
				uuid_parse(id.c_str(), _newId);
			}

			Cuuid(const Cuuid &other)
			{
				if (&other != this) {
					_strId = other.getUuidString();
					uuid_parse(_strId.c_str(), _newId);
				}
			}

			~Cuuid() = default;
			std::string getUuidString() const noexcept {
				return (_strId);
			};

			Cuuid &operator=(const Cuuid &other)
			{
				if (&other != this) {
					_strId = other.getUuidString();
					uuid_copy(_newId, *(other.getUuid()));
				}
				return *this;
			}

			const uuid_t *getUuid() const {
				return &_newId;
			}

			bool operator==(const Cuuid &uuid) {
				return(uuid_compare(_newId, *(uuid.getUuid())));
			}

			bool operator==(const std::string &strId) {
				return(_strId == strId);
			}
		protected:
		private:
			uuid_t _newId;
			std::string _strId;
	};
#endif
		
    }
}

#endif /* !CUUID_HPP_ */
