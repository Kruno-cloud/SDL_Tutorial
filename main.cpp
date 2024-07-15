#include <iostream>
//ne koristi "" include
#include "Calculator.h"
#include "InputHandler.h"
#include "OutputHandler.h"

int main()
{
	double x = 0.0, y = 0.0, result = 0.0;
	Operation oper = Operation::Add;

	while (true)
	{
		UserInput<double> userInput = GetInput<double>();
		result = Calculate<double>(userInput.Left, oper, userInput.Right);
		PrintResult(x, oper, y, result);
	}
	return 0;
}
