#include <iostream>
#include <string>
#include <limits>
#include "../include/panel.hpp"
#include "../include/payload.hpp"

Panel::Panel(std::string n){
	name = n;
}

void Panel::Help() const{
	std::cout << "[+] Available Commands:\n";
	std::cout << "[C] offset  - Choose initial payload offset.\n";
	std::cout << "[C] load    - Loads an address.\n";
	std::cout << "[C] add     - Adds two addresses or offsets.\n";
	std::cout << "[C] show    - Show stored addresses.\n";
	std::cout << "[C] delete  - Deletes an address.\n";
	std::cout << "[C] print   - Prints the payload on stdout.\n";
	std::cout << "[C] output  - Outputs the payload to file.\n";
	std::cout << "[C] exit    - Leave the application.\n";
	std::cout << "[C] help    - Prints this.\n";
}

void Panel::showName(std::string n) const{
	std::cout << "\n";
	std::cout << n << "❯ ";
}

int Panel::panelCore(Payload * p1) const{
	std::string command {};
	this->showName("Jupiter");
	std::cin >> command;
	if (command == "exit"){
		return 1;
	} else if (command == "offset"){
		unsigned int offsetSize {};
		std::cout << "[+] Choose an offset size.\n";
		this->showName("Offset");
		while (!(std::cin >> offsetSize)){
			std::cout << "[ERR] Invalid input. Please enter an integer.\n";
			this->showName("Offset");
			// Tenho que arrumar aqui!
			std::cin.clear(); 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}
		if (offsetSize > 200){
			std::cout << "[INFO] You have set an offset size higher than 200 characters.\n";
			std::cout << "[INFO] If this value was set by mistake please type 'offset' and correct the value.\n";
		}
		p1->loadInitialOffset(offsetSize);
		std::cout << "[+] Set offset of " << (int)offsetSize << " bytes.\n";
	} else if (command == "load"){
		std::string address {};
		std::string addressName {};
		unsigned long int addr {0};
		std::cout << "[+] Enter an address, format: 'ff12ff34'.\n";
		while (true){
			this->showName("LoadAddress");
			std::cin >> address;
			try {
				addr = std::stoul(address, 0, 16);
				break;
			} catch (const std::invalid_argument&){
				std::cout << "[ERR] Invalid input. Please enter a Hex number.\n";
			} catch (const std::out_of_range&){
				std::cout << "[ERR] Number too big. Please enter a smaller hex number.\n";
			}
		}
		std::cout << "[+] Enter an address name.\n";
		this->showName("AddressName");
		std::cin >> addressName;
		p1->loadAddress(addr, addressName);
		std::cout << "[+] Added address " << addressName << " - 0x" << std::hex << addr << ".\n";
	} else if (command == "delete"){
		unsigned int index {};
		std::cout << "[+] Enter the index of the address you want to delete.\n";
		this->showName("DeleteAddress");
		while (!(std::cin >> index) || index > p1->checkSize()){
			std::cout << "[ERR] There is no address stored in index" << index << "\n";
			this->showName("DeleteAddress");
			std::cin.clear(); 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}
		p1->deleteAddress(index);
		std::cout << "[+] Address index " << index << " deleted.\n";
		std::cout << "[INFO] Type 'show' to see the current stored addresses.\n";	
	} else if (command == "add"){
		unsigned int index1 {};
		unsigned int index2 {};
		std::string addressName;
		std::cout << "[+] Enter the first index you want to add.\n";
		this->showName("FirstIndex");
		std::cin >> index1;
		std::cout << "[+] Enter the second index you want to add.\n";
		this->showName("SecondIndex");
		std::cin >> index2;
		std::cout << "[+] Enter a name for this new address.\n";
		this->showName("AddressName");
		std::cin >> addressName;
		p1->addOffset(index1, index2, addressName);
		std::cout << "[+] Added address " << addressName << ".\n";
		std::cout << "[+] Type show to see the newly added address.\n";
	} else if (command == "output"){
		p1->output();
	} else if (command == "show"){
		p1->showAddresses();
	} else if (command == "print"){
		p1->print();
	} else if (command == "help"){
		this->Help();
	} else {
		std::cout << "[ERR]: Unrecognized command. Try command 'help'.\n";
	} 
	return 0;
}
