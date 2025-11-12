#include <iostream>
#include <string>
#include "../include/panel.hpp"
#include "../include/payload.hpp"

Panel::Panel(std::string n){
	name = n;
}

void Panel::Help() const{
	std::cout << "[+] Available Commands:\n";
	std::cout << "[C] offset  - Adds initial offset.\n";
	std::cout << "[C] load    - Loads an address.\n";
	std::cout << "[C] add     - Adds two addresses or offsets.\n";
	std::cout << "[C] show    - Show stored addresses.\n";
	std::cout << "[C] delete  - Deletes an address.\n";
	std::cout << "[C] print   - Prints the payload on stdout.\n";
	std::cout << "[C] output  - Outputs the payload to file.\n";
	std::cout << "[C] exit    - Leave the application.\n";
	std::cout << "[C] help    - Prints this.\n";
}

void Panel::showName() const{
	std::cout << "\n";
	std::cout << name << "❯ ";
}

int Panel::panelCore(Payload * p1) const{
	std::string command {};
	this->showName();
	std::cin >> command;
	if (command == "exit"){
		return 1;
	} else if (command == "offset"){
		unsigned int offsetSize {};
		std::cout << "[+] Enter an offset size.\n";
		this->showName();
		while (!(std::cin >> offsetSize)){
			std::cout << "[ERR] Invalid input. Please enter an integer: ";
			// Tenho que arrumar aqui!
			//std::cin.clear(); 
			//std::cin.ignore(std::numeric_limits<std::streamsize>::std::max(), '\n');
		}
		p1->loadInitialOffset(offsetSize);
		std::cout << "[+] Added offset of " << offsetSize << " bytes.\n";
	} else if (command == "help"){
		this->Help();
	} else {
		std::cout << "[ERR]: Unrecognized command. Try command 'help'.\n";
	} 
	return 0;
}
