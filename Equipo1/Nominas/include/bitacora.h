#ifndef BITACORA_H
#define BITACORA_H

#include <string>
using namespace std;

// Clase que maneja el sistema de bitácora
class bitacora {// Registro de bitacora - Isaias Cedillo (9959-24-1672) "IsaC8-bit"
private:
    // Variables para almacenar información de cada registro
    string nombre, aplicacion, accion;

public:
    // Muestra el menú principal al usuario
    void menu();

    // Inserta un nuevo registro en la bitácora
    void insertar(string nombre, std::string aplicacion, string accion);

    // Muestra todos los registros almacenados
    void desplegar();
    // Aplicacion para registros
     string generarCodigoAplicacion();
};

#endif
