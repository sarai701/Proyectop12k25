//9959 24 11603 GE
#ifndef ALMACEN_H
#define ALMACEN_H

#include <vector>
#include <string>
#include "bitacora.h"

// Clase que representa un Almacén dentro del sistema
class Almacen {
public:
    std::string id;             // ID único autogenerado en el rango 3260-3310
    std::string direccion;      // Dirección del almacén
    int capacidad;              // Capacidad del almacén en metros cuadrados
    std::string responsable;    // Nombre del responsable del almacén
    std::string contacto;       // Información de contacto del responsable
    std::string estado;         // Estado del almacén: "operativo" o "en mantenimiento"

    // Métodos para operaciones CRUD sobre almacenes

    // Agrega un nuevo almacén a la lista y lo registra en la bitácora
    static void agregar(std::vector<Almacen>& lista, const std::string& usuario);

    // Muestra todos los almacenes registrados
    static void mostrar(const std::vector<Almacen>& lista);

    // Modifica los datos de un almacén existente según su ID
    static void modificar(std::vector<Almacen>& lista, const std::string& usuario, const std::string& id);

    // Elimina un almacén de la lista según su ID
    static void eliminar(std::vector<Almacen>& lista, const std::string& usuario, const std::string& id);

    // Métodos para persistencia de datos

    // Guarda la lista completa de almacenes en un archivo de texto
    static void guardarEnArchivo(const std::vector<Almacen>& lista);

    // Carga los datos de almacenes desde un archivo de texto a la lista
    static void cargarDesdeArchivo(std::vector<Almacen>& lista);

private:
    // Métodos auxiliares internos

    // Genera un ID único en el rango permitido que no esté en uso
    static std::string generarID(const std::vector<Almacen>& lista);

    // Valida si el estado ingresado es válido ("operativo" o "en mantenimiento")
    static bool validarEstado(const std::string& estado);
};

#endif
