//LUIS ANGEL MENDEZ FUENTES 9959-24-6845
// MAYO 2025
#ifndef BITACORA_H
#define BITACORA_H

// Inclusión de bibliotecas necesarias
#include <string>
#include <fstream> // Para manejo de archivos

using namespace std;

// Clase bitacora: permite registrar y visualizar acciones realizadas por usuarios
class bitacora {
private:
    // Atributos que pueden utilizarse para representar una entrada de bitácora
    string nombreUsuario;   // Nombre del usuario que realizó la acción
    string codigoAccion;    // Código asociado a la acción realizada
    string descripcion;     // Descripción textual de la acción

public:
    // Inserta un nuevo registro en el archivo de bitácora
    void insertar(string usuario, string codigo, string accion);

    // Muestra en pantalla los registros actuales de la bitácora
    void desplegar();

    // Muestra el menú interactivo para gestionar la bitácora
    void menuBitacora();
};

#endif // BITACORA_H
