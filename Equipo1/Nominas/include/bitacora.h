#ifndef BITACORA_H
#define BITACORA_H

#include <string>

// Clase que maneja el sistema de bitácora
class bitacora // Registro de bitacora - Xander Reyes
{
private:
    // Variables para almacenar información de cada registro
    std::string nombre, aplicacion, accion;

public:
    // Muestra el menú principal al usuario
    void menu();

    // Inserta un nuevo registro en la bitácora
    void insertar(std::string nombre, std::string aplicacion, std::string accion);

    // Muestra todos los registros almacenados
    void desplegar();
};

#endif
