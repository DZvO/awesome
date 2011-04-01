#include "socket.hpp"

////////////////////////////////////////////////////////////////////////////////
motor::Address::Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port)
{
	this->address = (a << 24) | (b << 16) | (c << 8) | d;
	this->port = port;
}

motor::Address::Address(unsigned int address, unsigned short port)
{
	this->address = address;
	this->port = port;
}

unsigned char motor::Address::getA() const
{
	return (unsigned char)(address >> 24);
}

unsigned char motor::Address::getB() const
{
	return (unsigned char)(address >> 16);
}

unsigned char motor::Address::getC() const
{
	return (unsigned char)(address >> 8);
}

unsigned char motor::Address::getD() const
{
	return (unsigned char)(address);
}

unsigned int motor::Address::getAddress() const
{
	return address;
}

unsigned short motor::Address::getPort() const
{
	return port;
}

bool motor::Address::operator==(const Address &adr) const
{
	return (address == adr.address) && (port == adr.port);
}

bool motor::Address::operator!=(const Address &adr) const
{
	return !(*this == adr);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
bool motor::Socket::isOpen() const
{
	return (handle != -1);
}

bool motor::Socket::open(unsigned int port)
{
	handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if(handle <= 0)
	{
		cout << "couldn't create socket :( [e: " << handle << "]\n";
		perror(NULL);
		return false;
	}

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons((unsigned short)port);

	if(bind(handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
	{
		cout << "couldn't bind socket :( [e: " << handle <<"]\n";
		perror(NULL);
		return false;
	}

	int nonBlocking = 1;
	if(fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
	{
		cout << "couldn't make socket non-blocking :( [e: " << handle <<"]\n";
		perror(NULL);
		return false;
	}

	return true;//finally!
}

bool motor::Socket::send(const Address &dest, const void *data, int size)
{
	if(handle == -1) return false;

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(dest.getAddress());
	address.sin_port = htons((unsigned short)dest.getPort());

	int sentBytes = sendto(handle, (const char*)data, size, 0, (sockaddr*)&address, sizeof(sockaddr_in));

	return sentBytes == size;
}

int motor::Socket::receive(Address &sender, void *data, int size)
{
	if(handle == -1) return false;

	sockaddr_in from;
	socklen_t fromLength = sizeof(from);

	int received_bytes = recvfrom(handle, (char*)data, size, 0, (sockaddr*)&from, &fromLength);

	if(received_bytes <= 0) return 0;

	unsigned int address = ntohl(from.sin_addr.s_addr);
	unsigned int port = ntohs(from.sin_port);

	sender = Address(address, port);
	return received_bytes;
}

motor::Socket::Socket()
{
	handle = -1;
}

motor::Socket::~Socket()
{
	close();
}

void motor::Socket::close()
{
	::close(handle);
}
////////////////////////////////////////////////////////////////////////////////
