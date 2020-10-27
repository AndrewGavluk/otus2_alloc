#pragma once

#include <cstdint>
#include <iostream>
#include <string>


// #include "Config.h"
struct Ip4Okets;

constexpr uint8_t numbers_in_ip4address = 4;
constexpr uint8_t OKET_SIZE_IN_BITS = 8;
constexpr uint8_t OKET4_SIZE = OKET_SIZE_IN_BITS * numbers_in_ip4address;
constexpr uint8_t OKET0 = 0;
constexpr uint8_t OKET1 = OKET_SIZE_IN_BITS;
constexpr uint8_t OKET2 = OKET_SIZE_IN_BITS * 2;
constexpr uint8_t OKET3 = OKET_SIZE_IN_BITS * 3;


struct Ip4Okets
{
	Ip4Okets(const std::string &);
	friend std::ostream& operator<< (std::ostream& out, const Ip4Okets& point);
	friend bool operator < (Ip4Okets const& a, Ip4Okets const& b);
	bool check_mask (const uint8_t& mask, const uint8_t& shift);

	uint32_t ip4_address;
};



