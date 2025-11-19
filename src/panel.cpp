#include <iostream>
#include <string>
#include <limits>
#include "../include/panel.hpp"
#include "../include/payload.hpp"

#define CANCEL_OPERATION 0

Panel::Panel(std::string n){
	name = n;
}

void Panel::Help() const{
	std::cout << "[+] Available Commands:\n";
	std::cout << "[C] offset    - Choose initial payload offset.\n";
	std::cout << "[C] load      - Loads an address.\n";
	std::cout << "[C] add       - Adds two addresses or offsets.\n";
	std::cout << "[C] show      - Show stored addresses.\n";
	std::cout << "[C] delete    - Deletes an address.\n";
	std::cout << "[C] generate  - Generate the payload.\n";
	std::cout << "[C] print     - Prints the payload on stdout.\n";
	std::cout << "[C] output    - Outputs the payload to file.\n";
	std::cout << "[C] cancel    - Cancels any command.\n";
	std::cout << "[C] exit      - Leave the application.\n";
	std::cout << "[C] help      - Prints this.\n";
}

void Panel::showName(std::string n) const{
	std::cout << "\n";
	std::cout << n << "❯ ";
}

int Panel::inputLoop(std::string n, std::string mode, unsigned long int * out) const{
	std::string stringVal {};
	unsigned long int val {};
	while (true){
		this->showName(n);
		std::cin >> stringVal;
		if (stringVal == "cancel"){
			std::cout << "[+] You cancelled the operation.\n";
			return 0;
		}
		try {
			if (mode == "integer"){
				val = std::stoul(stringVal, 0, 10);
			} else {
				val = std::stoul(stringVal, 0, 16);
			}
			break;
		} catch (const std::invalid_argument&){
			std::cout << "[ERR] Invalid input. Please enter a " << mode << " number.\n";
		} catch (const std::out_of_range&){
			std::cout << "[ERR] Number too big. Please enter a smaller " << mode << " number.\n";
		}
	}
	*out = val;
	return 1;
}

int Panel::Offset(Payload * p1) const{
	unsigned long int offsetSize {};
	std::cout << "[+] Choose an offset size.\n";
	if (this->inputLoop("Offset", "integer", &offsetSize) == 0){
		// User cancelled the operation
		return 0;
	}
	if (offsetSize > 200){
		std::cout << "[INFO] You have set an offset size higher than 200 characters.\n";
		std::cout << "[INFO] If this value was set by mistake please type 'offset' and correct the value.\n";
	}
	p1->loadInitialOffset((unsigned int)offsetSize);
	std::cout << "[+] Set offset of " << offsetSize << " bytes.\n";
	return 0;
}

int Panel::Load(Payload * p1) const{
	std::string address {};
	std::string addressName {};
	unsigned long int addr {0};
	std::cout << "[+] Enter an address, format: '656b756c'.\n";
	if (this->inputLoop("LoadAddress", "hex", &addr) == 0){
		// User cancelled the operation
		return 0;
	}
	std::cout << "[+] Enter an address name.\n";
	this->showName("AddressName");
	std::cin >> addressName;
	p1->loadAddress(addr, addressName);
	std::cout << "[+] Added address " << addressName << " - 0x" << std::hex << addr << ".\n";
	return 0;
}

int Panel::Delete(Payload * p1) const{
	unsigned long int index {};
	std::cout << "[+] Enter the index of the address you want to delete.\n";
	if (this->inputLoop("DeleteAddress", "integer", &index) == 0){
		// User cancelled the operation
		return 0;
	}
	if (p1->checkSize() <= 0){
		std::cout << "[ERR]: There are no addresses stored currently.\n";
		return 0;
	} 
	if (index > p1->checkSize() - 1){
		std::cout << "[ERR] There is no address stored in index " << index << "\n";
		std::cout << "[ERR] Operation cancelled.\n";
		index = 0;
		return 0;
	}
	p1->deleteAddress((unsigned int)index);
	std::cout << "[+] Address index " << index << " deleted.\n";
	std::cout << "[INFO] Type 'show' to see the current stored addresses.\n";
	return 0;
}

int Panel::Add(Payload * p1) const{
	unsigned long int index1 {};
	unsigned long int index2 {};
	std::string addressName;
	std::cout << "[+] Enter the first index you want to add.\n";
	if (this->inputLoop("FirstIndex", "integer", &index1) == 0){
		// User cancelled the operation
		return 0;
	}
	std::cout << "[+] Enter the second index you want to add.\n";
	if (this->inputLoop("SecondIndex", "integer", &index2) == 0){
		// User cancelled the operation
		return 0;
	}
	if (p1->checkSize() <= 0){
		std::cout << "[ERR] There are no addresses stored currently. Operation Impossible.\n";
		std::cout << "[ERR] Operation cancelled.\n";
		return 0;
	}
	if (index1 > p1->checkSize() - 1 || index2 > p1->checkSize()){
		std::cout << "[ERR] One or both of your selected indexes does not have an address stored.\n";
		std::cout << "[ERR] Operation cancelled.\n";
		return 0;
	}
	std::cout << "[+] Enter a name for this new address.\n";
	this->showName("AddressName");
	std::cin >> addressName;
	p1->addOffset((unsigned int)index1, (unsigned int)index2, addressName);
	std::cout << "[+] Added address " << addressName << ".\n";
	std::cout << "[+] Type show to see the newly added address.\n";
	return 0;
}

int Panel::Output(Payload * p1) const{
	std::string filename {};
	std::cout << "[+] Enter the name of the file that will receive the payload.\n";
	this->showName("Output");
	std::cin >> filename;
	p1->output(filename);
	return 0;
}

int Panel::panelCore(Payload * p1) const{
	std::string command {};
	this->showName("Jupiter");
	std::cin >> command;
	if (command == "exit"){
		return 1;
	} else if (command == "offset"){
		this->Offset(p1);
	} else if (command == "load"){
		this->Load(p1);	
	} else if (command == "delete"){
		this->Delete(p1);	
	} else if (command == "add"){
		this->Add(p1);
	} else if (command == "output"){
		this->Output(p1);
	} else if (command == "show"){
		p1->showAddresses();
	} else if (command == "generate"){
		p1->generatePayload();
	} else if (command == "print"){
		p1->print();
	} else if (command == "help"){
		this->Help();
	} else if (command == "debug"){
		unsigned int testSize = p1->checkSize();
		std::cout << "[+] ListSize: " << testSize << "\n";
	} else if (command == "cancel"){
		std::cout << "[INFO] No command got cancelled.\n";
	} else {
		std::cout << "[ERR]: Unrecognized command. Try command 'help'.\n";
	} 
	return 0;
}
