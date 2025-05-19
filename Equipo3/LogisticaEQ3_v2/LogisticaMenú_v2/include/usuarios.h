//Karina Alejandra Arriaza Ortiz
#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>
#include "bitacora.h"

class usuarios {
private:
    std::string id;
    std::string nombre;
    std::string contrasena;
    int nivelAcceso;

    bool esNumero(const std::string& str);
    bool usuarioExiste(const std::string& nombreUsuario);
    std::string leerPasswordSegura();

public:
    usuarios();
    ~usuarios();

    bool loginUsuarios();
    void registrarUsuario();
    bool buscarUsuario(const std::string& user, const std::string& pass);

    std::string getNombre() const;
    std::string getId() const;
    int getNivelAcceso() const;
    void setNivelAcceso(int nivel);

    void menuUsuarios();
    void consultarUsuarios();
    void modificarUsuario();
    void eliminarUsuario();
};

#endif // USUARIOS_H
