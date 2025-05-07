#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

class Cliente {
public:
    Cliente(const std::string& nombre, const std::string& email);
    std::string getNombre() const;
    std::string getEmail() const;

private:
    std::string nombre;
    std::string email;
};

#endif // CLIENTE_H
