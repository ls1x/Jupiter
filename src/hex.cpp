#include <iostream>
#include <string>
#include <vector>
#include "../include/hex.hpp"

Hex::Hex(unsigned int hValue, unsigned int hSize){
        hexValue = hValue;
	hexSize = hSize;
}

std::string Hex::hexBuild() const {
	unsigned char * arr = new unsigned char[hexSize];
	for (unsigned int i {}; i < hexSize; i++){
		arr[i] = (unsigned char)((hexValue >> i * 8) & 0xFF);
	}
	//std::string output = std::string(vector);
	std::string output = std::string(reinterpret_cast<char const* >(arr), hexSize);
	delete[] arr;
	return output;
}
