//Jonathan Samuel Gonzalez Ixpata
#ifndef AUDITORIA_H         // Verifica si AUDITORIA_H no ha sido definido
#define AUDITORIA_H         // Define AUDITORIA_H para evitar inclusiones múltiples

#include <string>           // Incluye soporte para cadenas de texto (std::string)
#include <vector>           // Incluye soporte para vectores dinámicos (std::vector)
#include "Bitacora.h"       // Incluye la clase para registrar acciones (bitácora)

using namespace std;        // Evita tener que escribir std:: en cada uso de string o vector

// Estructura para almacenar los datos de un auditor
struct Auditores {
    string nombre;          // Nombre del auditor
    string codigo;          // Código identificador del auditor
};

// Declaración de la clase Auditoria
class Auditoria {
private:
    vector<Auditores> auditores; // Lista de auditores almacenados

public:
    void menuAuditoria();          // Muestra el menú principal de auditoría
    void registrosRealizados();    // Muestra una tabla con registros de auditoría
    void limpiarPantalla();        // Limpia la pantalla según el sistema operativo
    void pausar();                 // Pausa la ejecución hasta que el usuario presione ENTER

    // Funciones para la gestión de auditores
    void submenuAuditor();         // Muestra un submenú con opciones de gestión
    void registrarAuditor();       // Permite registrar un nuevo auditor
    void borrarAuditor();          // Elimina un auditor según su código
    void despliegueAuditores();    // Muestra en pantalla todos los auditores registrados
};

#endif  // Fin del include guard
