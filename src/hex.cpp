#include <iostream>
#include <string>
#include <vector>
#include "../include/hex.hpp"

std::string Hex::hexBuild(unsigned int hexSize, unsigned int hexValue){
	unsigned char * arr = new unsigned char[hexSize];
	for (unsigned int i {}; i < hexSize; i++){
		arr[i] = (unsigned char)((hexValue >> i * 8) & 0xFF);
	}
	std::string output = std::string(reinterpret_cast<char const* >(arr), hexSize);
	delete[] arr;
	return output;
}
