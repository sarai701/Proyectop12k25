#ifndef BITACORA_H
#define BITACORA_H
#include<iostream>

using std::string;

class bitacora
{
    public:
        void menu();
        void insertar(string nombre, string aplicacion, string accion);
        void desplegar();
    protected:

    private:
		string nombre, aplicacion, accion;

};
#endif // BITACORA_H
