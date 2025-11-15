#ifndef PANEL_HPP
#define PANEL_HPP

#include <string>
#include "../include/payload.hpp"

class Panel {

private:
	std::string name {};
	void showName(std::string n) const;
	void Help() const;

public:
	Panel(std::string n);
	int panelCore(Payload * p1) const;
};

#endif
