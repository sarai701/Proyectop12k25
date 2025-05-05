#ifndef COMPRAS_H
#define COMPRAS_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Producto {
    string nombre;
    string proveedor;
    double precioCompra;
    int cantidad;
    string fechaCompra;
};

class Compras {
public:
    static void mostrarMenu();
    static void registrarCompra(vector<Producto>& listaCompras);
    static void mostrarHistorial(const vector<Producto>& listaCompras);
    static void buscarPorProveedor(const vector<Producto>& listaCompras);
    static double calcularTotalGastado(const vector<Producto>& listaCompras);
};

#endif
