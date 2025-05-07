#include "Cliente.h"

Cliente::Cliente(const std::string& nombre, const std::string& email)
    : nombre(nombre), email(email) {}

std::string Cliente::getNombre() const {
    return nombre;
}

std::string Cliente::getEmail() const {
    return email;
}
