#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <vector>
#include <string>
#include "bitacora.h"

// JENNIFER ALBA DAYAMI BARRIOS FLORES 9959-24-10016
// COORD EQUIPO 3
// MAYO 2025

class Producto {
public:
    std::string id;           // Cambiado de codigo a id
    std::string nombre;
    std::string descripcion;  // Nuevo campo
    double precio;
    int stock;
    int stockMinimo;          // Nuevo campo

    // Métodos CRUD
    static void agregar(std::vector<Producto>& lista, const std::string& usuarioActual);
    static void mostrar(const std::vector<Producto>& lista);
    static void modificar(std::vector<Producto>& lista, const std::string& usuarioActual, const std::string& id);
    static void eliminar(std::vector<Producto>& lista, const std::string& usuarioActual, const std::string& id);

    // Métodos de archivo binario
    static void guardarEnArchivoBin(const std::vector<Producto>& productos);
    static void cargarDesdeArchivoBin(std::vector<Producto>& productos);
    static void guardarEnArchivo(const std::vector<Producto>& lista);
    static void cargarDesdeArchivo(std::vector<Producto>& lista);

    // Métodos de validación
    static bool esCodigoValido(const std::string& id);
    static std::string generarCodigoUnico(const std::vector<Producto>& lista);
    static bool codigoDisponible(const std::vector<Producto>& lista, const std::string& id);

    // Setters
    void setId(const std::string& id) { this->id = id; }
    void setNombre(const std::string& nombre) { this->nombre = nombre; }
    void setDescripcion(const std::string& descripcion) { this->descripcion = descripcion; }
    void setPrecio(double precio) { this->precio = precio; }
    void setStock(int stock) { this->stock = stock; }
    void setStockMinimo(int stockMinimo) { this->stockMinimo = stockMinimo; }

    // Getters
    std::string getId() const { return id; }
    std::string getNombre() const { return nombre; }
    std::string getDescripcion() const { return descripcion; }
    double getPrecio() const { return precio; }
    int getStock() const { return stock; }
    int getStockMinimo() const { return stockMinimo; }
};

#endif // PRODUCTO_H
