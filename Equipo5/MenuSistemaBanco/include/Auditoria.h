//Jonathan Samuel Gonzalez Ixpata
#ifndef AUDITORIA_H
#define AUDITORIA_H

#include <string>
#include <vector>

struct Auditores {
    std::string nombre;
    std::string codigo;
};

class Auditoria {
private:
    std::vector<Auditores> auditores;

public:
    void menuAuditoria();          // Menú principal
    void registrosRealizados();    // Tabla de movimientos
    void limpiarPantalla();        // Limpiar pantalla
    void pausar();                 // Pausar ejecución

    // Funciones para gestionar auditores
    void submenuAuditor();         // Submenú de opciones
    void registrarAuditor();       // Registrar nuevo auditor
    void borrarAuditor();          // Borrar por código
    void despliegueAuditores();    // Mostrar todos los auditores
};

#endif
