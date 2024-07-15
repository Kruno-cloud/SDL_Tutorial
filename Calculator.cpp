#include "Calculator.h"
#include <cassert>
template <typename T>
T Calculate(T a, Operation operation, T b)
{
	switch (operation)
	{
	case Operation::Add: return a + b;
	case Operation::Subtract: return a - b;
	case Operation::Multiply: return a * b;
	//Nisi provjerio divide by 0
	case Operation::Divide: return a / b;
	//Bolje crash-at program nego vratiti cudni return value, isto pogledaj optional ako zelis signalizirati da funkcija moze a i ne mora vratiti vrijednost
	default:
		{
			assert(false, "Not implemented");
			return T(0);
		}
	}
}
