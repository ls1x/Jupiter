#include <iostream>
#include <string>
#include "../include/panel.hpp"
#include "../include/hex.hpp"
#include "../include/payload.hpp"

int main(){
	//int result {0};
	//Panel p1("PayloadGen");
	//while (true){
	//	result = p1.panelCore();
	//	if (result != 0){
	//		break;
	//	}
	//}
	Hex h1(0x6c756b65, 4);
	std::string test = h1.hexBuild();
	std::cout << test << "\n";
	Payload p1;
	p1.loadAddress(0x656b756c, "lukeAddr");
	p1.loadAddress(0x656b756c, "lukeAddr");
	p1.loadAddress(0x656b756c, "lukeAddr");
	p1.loadAddress(0x656b756c, "lukeAddr");
	p1.loadAddress(0x656b756c, "lukeAddr");
	p1.addOffset(0,1, "NewSum");
	p1.showAddresses();
	std::cout << "[+] Testing Deletion of index 3\n";
	p1.deleteAddress(3);
	p1.showAddresses();
	p1.print();
	return 0;
}   
