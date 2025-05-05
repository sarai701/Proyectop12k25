#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>

class Usuario {
public:
    static void registrarUsuario(const std::string& nombre, const std::string& contrasena);
    static bool iniciarSesion(const std::string& nombre, const std::string& contrasena);
};

#endif
