#include <iostream>
#include "Calculator.h"
#include "InputHandler.h"
#include "OutputHandler.h"
using namespace std;

int main()
{
	double x = 0.0, y = 0.0, result = 0.0;
	char oper = '+';

	Calculator calculator;
	InputHandler inputHandler;
	OutputHandler outputHandler;

	while (true)
	{
		inputHandler.GetInput(x, oper, y);
		result = calculator.Calculate(x, oper, y);
		outputHandler.PrintResult(x, oper, y, result);
	}
	return 0;
}
