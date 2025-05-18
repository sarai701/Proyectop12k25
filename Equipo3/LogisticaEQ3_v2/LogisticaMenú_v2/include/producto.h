#ifndef PRODUCTO_H
#define PRODUCTO_H
#include <vector>
#include <string>
#include "bitacora.h"

// JENNIFER ALBA DAYAMI BARRIOS FLORES 9959-24-10016
// COORD EQUIPO 3
// MAYO 2025

class Producto {
private:
    std::string id;
    std::string codigo;  // Añadido
    std::string nombre;
    std::string descripcion;
    double precio;
    int stock;
    int stockMinimo;

public:
    Producto();

    // Getters
    std::string getId() const;
    std::string getCodigo() const;  // Añadido
    std::string getNombre() const;
    std::string getDescripcion() const;
    double getPrecio() const;
    int getStock() const;
    int getStockMinimo() const;

    // Setters
    void setId(const std::string& id);
    void setCodigo(const std::string& codigo);  // Añadido
    void setNombre(const std::string& nombre);
    void setDescripcion(const std::string& descripcion);
    void setPrecio(double precio);
    void setStock(int stock);
    void setStockMinimo(int stockMinimo);

    // Otros métodos
    static bool codigoDisponible(const std::vector<Producto>& productos, const std::string& codigo);
    void modificar(std::vector<Producto>& productos, const std::string& campo, const std::string& nuevoValor);
    void eliminar(std::vector<Producto>& productos, const std::string& campo, const std::string& valor);
};

#endif // PRODUCTO_H
