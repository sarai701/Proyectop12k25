#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <vector>
#include <string>
#include "bitacora.h"

// Jennifer Alba Dayami Barrios Flores 9959-24-10016
// COORD EQUIPO 3
// MAYO 2025

class Producto {
public:
    std::string codigo;
    std::string nombre;
    double precio;
    int stock;

    // Métodos CRUD
    static void agregar(std::vector<Producto>& lista, const std::string& usuarioActual);
    static void mostrar(const std::vector<Producto>& lista);
    static void modificar(std::vector<Producto>& lista, const std::string& usuarioActual, const std::string& codigo);
    static void eliminar(std::vector<Producto>& lista, const std::string& usuarioActual, const std::string& codigo);

    // Métodos de archivo binario
    static void guardarEnArchivoBin(const std::vector<Producto>& productos);
    static void cargarDesdeArchivoBin(std::vector<Producto>& productos);
    static void guardarEnArchivo(const std::vector<Producto>& lista); // Asegúrate de agregar esta línea
    static void cargarDesdeArchivo(std::vector<Producto>& lista);     // Asegúrate de agregar esta línea

    // Métodos de validación
    static bool esCodigoValido(const std::string& codigo);
    static std::string generarCodigoUnico(const std::vector<Producto>& lista);
    static bool codigoDisponible(const std::vector<Producto>& lista, const std::string& codigo);

    void setStock(int nuevoStock);

    std::string getCodigo() const { return codigo; }
    std::string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }
    int getStock() const { return stock; }
};

#endif // PRODUCTO_H
