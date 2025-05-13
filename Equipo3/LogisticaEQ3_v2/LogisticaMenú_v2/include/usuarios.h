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
    int nivelAcceso; // Añade esta línea
public:
    usuarios();
    ~usuarios();
    bool loginUsuarios();
    void registrarUsuario();
    bool buscarUsuario(const std::string& user, const std::string& pass);
    std::string getNombre() const;
    std::string getId() const;
    int getNivelAcceso() const; // Asegúrate de que esté declarado
    void setNivelAcceso(int nivel); // Añade este setter
    void setNombre(const std::string& nombre);
    void menuUsuarios();
    void consultarUsuarios();
    void eliminarUsuario();
    void modificarUsuario();
};

#endif // USUARIOS_H
