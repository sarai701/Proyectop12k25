//Karina Alejandra Arriaza Ortiz 9959-24-14190
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
    bool buscarUsuario(const std::string& user, const std::string& pass);
    std::string getNombre();
    void registrarUsuario();
    void setNombre(const std::string& nombre);
    void menuUsuarios();
    void consultarUsuarios();
    void eliminarUsuario();
    void modificarUsuario();
    void gestorInventario();
};

#endif // USUARIOS_H
