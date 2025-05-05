#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

class Cliente {
public:
    std::string nombre;
    std::string email;

    Cliente(std::string n, std::string e);
};

#endif // CLIENTE_H
