#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
public:
    static bool registrarUsuario(const std::string& usuario, const std::string& contrasena);
    static bool iniciarSesion(const std::string& usuario, const std::string& contrasena);

private:
    static const std::string ARCHIVO_USUARIOS;
    static bool usuarioExiste(const std::string& usuario);
};

#endif
