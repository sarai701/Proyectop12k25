#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
public:
    static bool registrarUsuario(const std::string& usuario, const std::string& contrasena);
    static bool iniciarSesion(const std::string& usuario, const std::string& contrasena);

    // ✅ Declaración agregada para evitar el error del linker
    static std::string leerContrasenaOculta(bool mostrar = false, char caracter = '*');

private:
    static const std::string ARCHIVO_USUARIOS;
    static bool usuarioExiste(const std::string& usuario);
};

#endif
