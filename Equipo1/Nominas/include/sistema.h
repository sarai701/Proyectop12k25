#ifndef SISTEMA_H
#define SISTEMA_H

#include <fstream>
#include <vector>
#include "usuarios.h"

using namespace std;

class sistema //clase sistema la cual es encargada del proceso de registrar logear y mostrar usuarios-ANGEL ROQUEL
{
public:
    sistema();
    virtual ~sistema();
//Se declaran los metodos para sistemas de seguridad
    void registrarUsuario();
    void ingresarUsuario();
    void mostrarUsuarios();

private:
    string archivoUsuarios = "usuarios.txt";
};

#endif // SISTEMA_H
