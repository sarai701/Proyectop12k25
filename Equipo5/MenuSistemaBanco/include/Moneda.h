//Jonathan Samuel Gonzalez
#ifndef MONEDA_H
#define MONEDA_H

#include <string>

class Moneda {
public:
    static std::string moneda;       // Almacenará "GTQ", "USD" o "EUR"
    static std::string getSimbolo(); // Devuelve el símbolo correspondiente
};

#endif
