#ifndef _NETWORK_HPP
#define _NETWORK_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <iostream>
#include <cstdio>

using namespace std;

namespace motor
{
	class Address
	{
		public:
			unsigned int address;
			unsigned short port;

			Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port);
			Address(unsigned int address, unsigned short port);

			unsigned int getAddress() const;
			unsigned char getA() const;
			unsigned char getB() const;
			unsigned char getC() const;
			unsigned char getD() const;
			unsigned short getPort() const;

			bool operator==(const Address &adr) const;
			bool operator!=(const Address &adr) const;
	};

	class Socket
	{
		private:
			int handle;
		public:
			Socket();
			~Socket();
			bool open(unsigned int port = 0);
			void close();
			bool isOpen() const;
			bool send(const Address &dest, const void* data, int size);
			int receive(Address &from, void *data, int size);
	};
}

#endif
