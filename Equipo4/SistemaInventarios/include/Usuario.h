#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class usuarios {
public:
    usuarios();
    ~usuarios();
    bool loginUsuarios();
    void menuUsuarios();
    bool buscar(std::string user, std::string passw);
    std::string getNombre();
    void setNombre(std::string nombre);
    void consultarUsuarios(); // Nueva declaración

private:
    int id;
    std::string name;
    std::string pass;
};

#endif
