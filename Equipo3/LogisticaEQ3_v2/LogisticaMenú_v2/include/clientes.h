#ifndef CLIENTES_H
#define CLIENTES_H

#include <vector>
#include <string>

class Clientes {
public:
    std::string id;
    std::string nombre;
    std::string direccion;
    std::string telefono;
    std::string nit;


    // Métodos CRUD
    static void agregar(std::vector<Clientes>& lista, const std::string& usuarioActual);
    static void mostrar(const std::vector<Clientes>& lista);
    static void modificar(std::vector<Clientes>& lista, const std::string& usuarioActual, const std::string& id);
    static void eliminar(std::vector<Clientes>& lista, const std::string& usuarioActual, const std::string& id);

    // Métodos de archivo
    static void guardarEnArchivo(const std::vector<Clientes>& lista);
    static void cargarDesdeArchivo(std::vector<Clientes>& lista);

    // Métodos para gestión de IDs
    static std::string generarIdUnico(const std::vector<Clientes>& lista);
    static bool idDisponible(const std::vector<Clientes>& lista, const std::string& id);
    static bool esIdValido(const std::string& id);
};

#endif // CLIENTES_H
