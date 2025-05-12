//Angoly Araujo Mayo 2025 9959-24-17623
#ifndef PROVEEDOR_H
#define PROVEEDOR_H

#include <vector>
#include <string>

// Clase que representa a un proveedor del sistema
class Proveedor {
public:
    // Agrega un nuevo proveedor a la lista
    static void agregar(std::vector<Proveedor>& lista, const std::string& usuarioActual);

    // Modifica un proveedor existente según su ID
    static void modificar(std::vector<Proveedor>& lista, const std::string& usuarioActual, const std::string& id);

    // Elimina un proveedor de la lista por ID
    static void eliminar(std::vector<Proveedor>& lista, const std::string& usuarioActual, const std::string& id);

    // Muestra todos los proveedores registrados
    static void mostrar(const std::vector<Proveedor>& lista);

    // Guarda todos los proveedores en archivo
    static void guardarEnArchivo(const std::vector<Proveedor>& lista);

    // Carga los proveedores desde el archivo a la lista
    static void cargarDesdeArchivo(std::vector<Proveedor>& lista);

    // Genera un ID único dentro del rango permitido
    static std::string generarIdUnico(const std::vector<Proveedor>& lista);

    // Verifica si un ID ya existe en la lista
    static bool idDisponible(const std::vector<Proveedor>& lista, const std::string& id);

    // Valida que un ID esté en el rango permitido
    static bool esIdValido(const std::string& id);

private:
    std::string id;        // ID del proveedor (auto-generado)
    std::string nombre;    // Nombre completo del proveedor
    std::string telefono;  // Número de teléfono del proveedor
};

#endif // PROVEEDOR_H

