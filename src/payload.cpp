#include <string>
#include <vector>
#include <fstream>
#include "../include/payload.hpp"
#include "../include/hex.hpp"

void Payload::loadAddress(long unsigned int value, std::string name){
	payloadList.push_back(value);
	nameList.push_back(name);
	listSize++;
}

void Payload::showAddresses() const{
	for (unsigned int i {}; i < listSize; i++){
		std::cout << "Id: " << i << " | Address: 0x" << std::hex << payloadList[i] << " | Name: " << nameList[i] << "\n";
	}
}

void Payload::addOffset(unsigned int id1, unsigned int id2, std::string name){
	unsigned long int result {};
	result = payloadList[id1] + payloadList[id2];
	payloadList.push_back(result);
	nameList.push_back(name);
	listSize++;	
}

void Payload::loadInitialOffset(unsigned int size){
	initialOffset = size;
}

void Payload::deleteAddress(unsigned int index){
	payloadList.erase(payloadList.begin() + index);
	nameList.erase(nameList.begin() + index);
	listSize--;
}

void Payload::print() const{
	if (payload == ""){
		std::cout << "[INFO] Payload empty.\n";
		std::cout << "[INFO] Try to use 'generate' first.\n";
	} else {
		std::cout << "[+] " << payload << "\n";
	}
}

void Payload::generatePayload(){
	std::string fullPayload {};
	if (initialOffset > 0){
		char * arr = new char[initialOffset + 1];
		//arr[initialOffset + 1] = '\0';
		for (unsigned int i{}; i < initialOffset; i++){
			arr[i] = 'a';
		}
		arr[initialOffset] = '\0';
		std::string initial {}; 
		initial = std::string(arr);
		fullPayload += initial;
		delete[] arr;
	}
	if (listSize > 0){
		std::string answer1 {};
		std::cout << "[INFO] You have "  << listSize << " addresses stored.\n";
		std::cout << "[+] Do you want to inject all of them in order?\n";
		std::cout << "[+] Use command 'show' to see the current order.\n";
		std::cout << "[+] Y/N? ";
		while (true){
			std::cin >> answer1;
			if (answer1 == "y" || answer1 == "Y"){
				std::string * arrHex = new std::string[listSize];
				for (unsigned int i {}; i < listSize; i++){
					arrHex[i] = Hex::hexBuild(4, (unsigned int)payloadList[i]);
					fullPayload += arrHex[i];
				}
				delete[] arrHex;
				payload = fullPayload;
				std::cout << "[+] Payload generated. Use 'print' to see the results.\n";
				std::cout << "[+] You can also use 'output' to output it to a file.\n";
				break;
			} else if (answer1 == "n" || answer1 == "N"){
				std::cout << "[+] You chose to not continue.\n";
				break;
			} else {
				std::cout << "[+] Invalid answer. Type Y/N.\n";
			}
		}
	} else {
		std::cout << "[+] Payload generated. Use 'print' to see the results.\n";
		std::cout << "[+] You can also use 'output' to output it to a file.\n";
		payload = fullPayload;
	}
	// Essa função é bem mais complexa, eu tenho que antes escolher
	// quais endereços serão utilizados e qual ordem.
}

void Payload::output(std::string filename) const{
	std::fstream PTR_file(filename, PTR_file.binary | PTR_file.out);
	if (!PTR_file.is_open()){
		std::cerr << "[ERR]: Unable to open file!\n";
	} else {
		PTR_file << payload;
		std::cout << "[+] The payload was successfully output to the file " << filename << "\n";
	}
}

unsigned int Payload::checkSize() const{
	return listSize;
}


// Comandos:
// - [X] loadAddress() - carrega um endereço
// - [X] showAddress() - mostra os endereços armazenados
// - [X] addOffset() - soma dois endereçoss
// - [X] loadInitialOffset() - carrega o buffer inicial
// - [X] deleteAddress() - deleta um endereço do vetor
// - [X] printPayload() - mostra o payload gerado no stdout
// - [ ] outputPayload() - cria um arquivo com o payload gerado
