#ifndef PAYLOAD_HPP
#define PAYLOAD_HPP

#include <iostream>
#include <string>
#include <vector>

class Payload {

private:
	unsigned int listSize {};
	unsigned int initialOffset {};
	std::vector<unsigned long int> payloadList {};
	std::vector<std::string> nameList {};
	std::string payload {};

public:
	void loadAddress(long unsigned int value, std::string name);
	void showAddresses() const;
	void addOffset(unsigned int id1, unsigned int id2, std::string name);
	void loadInitialOffset(unsigned int size);
	void deleteAddress(unsigned int index);
	void generatePayload();
	void print() const;
	void output(std::string filename) const;
	unsigned int checkSize() const;
};

#endif
