#include <iostream>
#include "InputHandler.h"
#include <cstdlib>
#include <sstream>
void InputHandler::GetInput(double& a, char& oper, double& b)
{
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
    ss >> a >> oper >> b;

}


