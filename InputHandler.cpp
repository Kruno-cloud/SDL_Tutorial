#include <iostream>
#include "InputHandler.h"

void InputHandler::	GetInput(double& a, char& oper, double& b) 
{
	std::cout << "Unesite operaciju (npr. 5+5): ";
	std::cin >> a >> oper >> b;
}

