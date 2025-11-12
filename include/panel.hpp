#ifndef PANEL_HPP
#define PANEL_HPP

#include <string>

class Panel {

private:
	std::string name {};
	void Help() const;

public:
	Panel(std::string n);
	int panelCore() const;
};

#endif
