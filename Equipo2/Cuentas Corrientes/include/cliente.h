//Clase para mantenimiento de clientes
//Programado por Dulce Martìnez 02/05/25

#ifndef CLIENTE_H
#define CLIENTE_H
#include<iostream>

using namespace std;

class cliente
{
    private:
		string nombre, telefono, nit;
		string id;
	public:
		void menu();
		void insertar();
		void desplegar();
		void modificar();
		void buscar();
		void borrar();
};

#endif // CLIENTE_H
