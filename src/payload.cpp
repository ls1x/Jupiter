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

void Payload::loadOffset(unsigned int size){
	std::string offset {};
	char * arr = new char[size + 1];
	for (unsigned int i{}; i < size; i++){
		arr[i] = 'a';
	}
	arr[size] = '\0';
	std::string initial {}; 
	offset = std::string(arr);
	delete[] arr;
	payload += offset;
}

void Payload::deleteAddress(unsigned int index){
	payloadList.erase(payloadList.begin() + index);
	nameList.erase(nameList.begin() + index);
	listSize--;
}

void Payload::addString(std::string str){
	payload += str;
}

void Payload::print() const{
	if (payload == ""){
		std::cout << "[INFO] Payload empty.\n";
		std::cout << "[INFO] Try to use 'generate' first.\n";
	} else {
		std::cout << "[+] " << payload << "\n";
	}
}

void Payload::cleanPayload(){
	payload = "";
}

void Payload::generatePayload(unsigned int index){
	if (listSize > 0){
		std::string hex =  Hex::hexBuild(4, (unsigned int)payloadList[index]);
		payload += hex;	
		std::cout << "[+] Index " << index << " loaded into the payload.\n";
	} else {
		std::cerr << "[ERR] There are no addresses stored or the index is invalid.\n";
	}
	// Possivelmente temos problemas aqui com o index sendo maior que o listSize
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
