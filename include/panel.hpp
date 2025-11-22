#ifndef PANEL_HPP
#define PANEL_HPP

#include <string>
#include "../include/payload.hpp"

class Panel {

private:
	std::string name {};
	void showName(std::string n) const;
	void Help() const;
	int inputLoop(std::string n, std::string mode, unsigned long int * out) const;
	int Offset(Payload * p1) const;
	int Load(Payload * p1) const;
	int Delete(Payload * p1) const;
	int Add(Payload * p1) const;
	int Output(Payload * p1) const;
	int Generate(Payload * p1) const;
	int String(Payload * p1) const; 

public:
	Panel(std::string n);
	int panelCore(Payload * p1) const;
};

#endif
