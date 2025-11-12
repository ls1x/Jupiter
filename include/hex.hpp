#ifndef HEX_HPP
#define HEX_HPP

#include <string>

class Hex {

private:
	unsigned int hexValue {};
	unsigned int hexSize {};

public:
	Hex(unsigned int hValue, unsigned int hSize);
	std::string hexBuild() const;
};

#endif
