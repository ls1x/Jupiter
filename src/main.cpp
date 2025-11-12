#include <iostream>
#include <string>
#include "../include/panel.hpp"
#include "../include/hex.hpp"
#include "../include/payload.hpp"

int main(){
	int result {0};
	Panel panelJupiter("Jupiter");
	Payload payload;
	while (true){
		result = panelJupiter.panelCore(&payload);
		if (result != 0){
			break;
		}
	}
	return 0;
}   
