#ifndef USUARIOS_H
#define USUARIOS_H
#include<iostream>

using std::string;

class usuarios //Clase usuarios-ANGEL ROQUEL
{
public:
    usuarios(string, string);
    virtual ~usuarios();
    string getNombre();
    string getContrasenia();
    bool verificarContrasenia(string);

private:
    string nombre;
    string contrasenia;
};

#endif // USUARIOS_H
