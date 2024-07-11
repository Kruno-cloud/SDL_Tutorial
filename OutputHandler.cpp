#include <iostream>
#include "OutputHandler.h"

void OutputHandler::PrintResult(double a, char oper, double b, double result)
{
	std::cout << "Rezultat " << a << " " << oper << " " << b << "je: " << result << std::endl;
}

