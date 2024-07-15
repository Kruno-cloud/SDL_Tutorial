#pragma once
//#ifndef INPUTHANDLER_H
//#define INPUTHANDLER_H

//Ne koristi "" include, ja ga koristim jer nisi podesio dobar include path u project settings
#include "Calculator.h"
#include <cstdlib>
#include <sstream>

template <typename T>
struct UserInput 
{
	T Left;
	T Right;
	Operation Operation;
};

template <typename T>
UserInput<T> GetInput()
{
    UserInput<T> userInput;
    char operation;
    std::string left;
    std::string right;

    std::string input;
    std::cout << "Unesite operaciju (npr. 5+5), x za izlaz: ";
    std::cin >> input;

    // Provjera je li korisnik unio 'x' za izlaz
    if (input == "x") {
        std::cout << "Izlaz iz programa." << std::endl;
        exit(0); // Izlazak iz programa
    }

    // Pretvaranje unosa u string stream radi jednostavnijeg pariranja
    std::stringstream ss(input);
    ss >> userInput.Left >> operation >> userInput.Right;

    //napisi ovo za sve operacije
    if (operation == '+')
    {
        userInput.Operation = Operation::Add;
    }

    return userInput;
}

//#endif 


