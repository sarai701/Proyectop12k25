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
public:
    usuarios();
    ~usuarios();
    bool loginUsuarios();
    void registrarUsuario(); // Movido a público para acceso desde login
    bool buscarUsuario(const std::string& user, const std::string& pass);
    std::string getNombre();
    void setNombre(const std::string& nombre);
    void menuUsuarios();
    void consultarUsuarios();
    void eliminarUsuario();
};

#endif // USUARIOS_H
