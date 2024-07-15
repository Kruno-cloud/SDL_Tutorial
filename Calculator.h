//Ili pragama once, ili
#pragma once
//ovo, oboje rade istu stvar
//#ifndef CALCULATOR_H
//#define CALCULATOR_H
//No ne moj koristiti ifdefs jer je pragma once napravljena da to ne radis
#include <cassert>
//Enum je bolji nacin da izrazis koje operacije podrzava Calculate funkcija
enum class Operation {
	Add,
	Subtract,
	Multiply,
	Divide
};

//Ako klasa ne sadrži podatke, ne trebas klasu, mozda namespace, no ja preferiram samo cistu funkciju
/*
class Calculator 
{
public: 
	double Calculate(double a, Operation operation, double b);
};
*/

//Templates for the win
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

//#endif	


