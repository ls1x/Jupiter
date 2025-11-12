#include <iostream>
#include <string>
#include "../include/panel.hpp"
#include "../include/hex.hpp"

Panel::Panel(std::string n){
	name = n;
}

void Panel::Help() const{
	std::cout << "Available Commands:\n";
	std::cout << "exit - Leave the application.\n";
	std::cout << "help - Prints this.\n";
	return; 
}

int Panel::panelCore() const{
	std::string command {};
	std::cout << name << "> ";
	std::cin >> command;
	if (command == "exit"){
		return 1;
	} else if (command == "help"){
		this->Help();
	} else {
		std::cout << "[ERR]: Unrecognized command. Try command 'help'.\n";
	} 
	return 0;
}
