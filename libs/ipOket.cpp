#include "ipOket.h"

std::ostream& operator<< (std::ostream& out, const Ip4Okets& StringAdress)
{

	out << (StringAdress.ip4_address >> OKET3) << '.';
	out << (StringAdress.ip4_address << OKET1 >> OKET3) << '.';
	out << (StringAdress.ip4_address << OKET2 >> OKET3) << '.';
	out << (StringAdress.ip4_address << OKET3 >> OKET3) << std::endl;

	return out;
}

Ip4Okets::Ip4Okets(const std::string & in)
{
	ip4_address = 0;
	uint8_t size(in.size());
	for (uint8_t i = 0, buff = 0; i<=size; ++i)
		if (in[i] == '.' || in[i] == '\t' || in[i] == '\n' || in[i] == '\0')
		{
			ip4_address = ip4_address << OKET_SIZE_IN_BITS;
			ip4_address += buff;
			buff = 0;
			if (in[i] == '\t' || in[i] == '\n')
				break;
		}
		else
			if (std::isdigit(in[i]))
			{
				buff *= 10;
				buff += in[i] - '0';
			}
}

bool operator < (Ip4Okets const& a, Ip4Okets const& b)
{
	return a.ip4_address < b.ip4_address;
}

bool Ip4Okets::check_mask(const uint8_t & mask, const uint8_t & shift)
{
	return mask==((ip4_address << (OKET3-shift)) >> (OKET3));
}
