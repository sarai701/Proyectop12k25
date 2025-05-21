// Jonathan Samuel Gonzalez Ixpata 9959-23-3184

#ifndef AUDITORIA_H
#define AUDITORIA_H

#include <string>
#include <vector>
#include "Bitacora.h"

using namespace std;

// Estructura que almacena información básica de los auditores
struct Auditores {
    char nombre[50];     // Nombre completo del auditor (50 caracteres)
    char codigo[20];     // Identificador único del auditor (20 caracteres)
};

// Clase principal para gestión del módulo de auditoría
class Auditoria {
private:
    string usuario;              // Usuario actual del sistema
    vector<Auditores> auditores; // Almacenamiento temporal de auditores

public:
    // Establece el usuario activo para registro en bitácora
    void setUsuario(const string& u);

    // Gestión principal del módulo
    void menuAuditoria();       // Menú principal de auditoría

    // Utilidades de sistema
    void limpiarPantalla();     // Limpia consola según SO
    void pausar();              // Pausa ejecución hasta entrada

    // Funcionalidades de gestión de auditores
    void submenuAuditor();      // Submenú de operaciones
    void registrarAuditor();    // Registra nuevos auditores
    void borrarAuditor();       // Elimina auditores por código
    void despliegueAuditores(); // Muestra lista completa de auditores
};

#endif

