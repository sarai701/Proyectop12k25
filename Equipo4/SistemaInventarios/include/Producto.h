//Implementacion Marco H. 03/04/2025
#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

class Producto {
public:
    int codigo;
    std::string nombre;
    float precio;
    int stock;
    std::string tipo;

    Producto(int _codigo, std::string _nombre, float _precio, int _stock, std::string _tipo);
};
#endif
