// Modificaci�n por Ferdynand Monroy abril 2025
// Modificado para guardado de productos por Anthony Suc, 2 de mayo 2025
//Modificacion by Marco H. 18/05/25
#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <vector>
#include <string>
#include "Producto.h"

class Inventario {
private:
    std::vector<Producto> productos;
    std::string nombreArchivo = "inventario.txt";

public:
    Inventario();

    void agregarProducto(int codigo, std::string nombre,
    float precio, int stock, std::string tipo);
    void mostrarInventarioGeneral();
    void mostrarInventarioPorTipo(std::string tipo);
    Producto* buscarProducto(int codigo);
    void ventas(int codigo, int stock);
    void guardarEnArchivo() const;
    void cargarDesdeArchivo();
    bool eliminarProducto(int codigo);
    void movimientoBodega(int codigo, int cantidad, bool esEntrada);
    void mostrarMovimientosBodega();
    void mostrarKardexBodega();


    ~Inventario();
};

#endif // INVENTARIO_H
