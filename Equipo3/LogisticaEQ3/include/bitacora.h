// LUIS ANGEL MENDEZ FUENTES 9959-24-6845
#ifndef BITACORA_H
#define BITACORA_H

#include <string>
#include <fstream>
using namespace std;

// Clase 'bitacora': Maneja el registro de acciones realizadas en el sistema.
class bitacora {
private:
    string nombreUsuario;   // Nombre del usuario que realiza la acción
    string codigoAccion;    // Código que identifica la acción
    string descripcion;     // Descripción de la acción realizada
public:
    // Inserta una nueva entrada en la bitácora con los datos proporcionados
    void insertar(string usuario, string codigo, string accion);

    // Muestra las entradas registradas en la bitácora
    void desplegar();

    // Muestra un menú para acceder a la bitácora (solo desde administración)
    void menuBitacora();
};

#endif // BITACORA_H
