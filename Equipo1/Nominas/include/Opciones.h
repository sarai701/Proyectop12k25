#ifndef OPCIONES_H
#define OPCIONES_H
#include <iostream>

using std::string;

class Opciones//Clase la cual muestra el menú-ANGEL ROQUEL
{
    private:
		string id, nombre, estatus;
	public:
		void menu();
		void insertar();
		void desplegar();
		void modificar();
		void buscar();
		void borrar();

    protected:

    private:
};

#endif // OPCIONES_H
