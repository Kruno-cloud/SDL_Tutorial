#pragma once
//#ifndef OUTPUTHANDLER_H
//#define OUTPUTHANDLER_H

#include "Calculator.h"
#include <iostream>
template <typename T>
void PrintResult(T a, Operation oper, T b, T result)
{
	std::string operation;
	//napisi za sve operacije
	if (oper == Operation::Add)
	{
		operation = "+";
	}
	std::cout << "Rezultat " << a << " " << operation << " " << b << "je: " << result << std::endl;
}

//#endif 