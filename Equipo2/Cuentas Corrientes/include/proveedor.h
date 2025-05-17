//Clase para mantenimiento de Proveedores
//Programado por Britany Hernandez 04/05/25

//Actualizacion y correcciones
//Programado por Britany Hernandez 11/05/25

#ifndef PROVEEDOR_H
#define PROVEEDOR_H

#include<iostream>
using namespace std;

class proveedor {

private:
    string id, nombreProveedor, telefono, numCuenta, banco;
public:
    void menu();
    void insertar();
    void desplegar();
    void modificar();
    void buscar();
    void borrar();
    void reporte();
};
#endif
