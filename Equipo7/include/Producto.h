// STEVEN ANDRE VASQUEZ CHAVEZ 9959 24 11528

#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
#include <vector>
using namespace std;

struct ProductoInfo {
    string nombre;
    int cantidad;
    float precio;
    int codigo;
};

class Producto {
public:
    Producto();
    void MenuProducto();
    void NuevoProducto();
    void MostrarProductos();
    void EliminarProducto();
    void AumentarExistencias();
    static std::vector<ProductoInfo>& obtenerProductos();

private:
    static std::vector<ProductoInfo> productos;
    static int ultimoCodigo;
    int generarCodigo();
    void GuardarEnBinario();
    void CargarDesdeBinario();
};

#endif // PRODUCTO_H



