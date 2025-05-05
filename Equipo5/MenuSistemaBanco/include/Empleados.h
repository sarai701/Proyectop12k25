// Karla Patricia Ruiz Ordoñez 9959-24-6859
#ifndef EMPLEADOS_H
#define EMPLEADOS_H

#include <vector>
#include <string>
#include "Bitacora.h"  //  Se incluye para registrar acciones realizadas

// Clase que representa a un empleado individual
class Empleado {
public:
    std::string nombre;      // Nombre completo del empleado
    std::string codigo;      // Código único de identificación
    std::string puesto;      // Cargo o puesto dentro de la empresa
    std::string telefono;    // Número telefónico de contacto
};

// Clase que gestiona la lista de empleados y sus operaciones
class Empleados {
private:
    std::vector<Empleado> empleados;   // Lista de todos los empleados registrados
    Bitacora bitacoralogEmpleados;     // ✅ Bitácora para registrar las operaciones realizadas

public:
    // Funciones auxiliares
    void limpiarPantalla();            // Limpia la consola (compatible con Windows y Unix)
    void pausar();                     // Pausa la ejecución hasta que el usuario presione ENTER
    void cargarEmpleados();            // Carga los empleados desde el archivo "empleados.txt"
    void guardarEmpleados();           // Guarda la lista actual de empleados al archivo
    void ordenarEmpleados();           // Ordena a los empleados por nombre de forma ascendente

    // Funciones principales del menú
    void menuEmpleados();              // Muestra el menú de opciones para gestionar empleados
    void crearEmpleado();              // Permite ingresar un nuevo empleado y registrarlo
    void borrarEmpleado();             // Elimina un empleado con base en su nombre y código
    void buscarEmpleado();             // Busca un empleado específico para visualizar su información
    void modificarEmpleado();          // Edita los datos de un empleado existente
    void desplegarEmpleados();         // Muestra todos los empleados registrados

    //  Cada acción importante se registra en la bitácora:
    // - crearEmpleado()    → ID: 4001
    // - borrarEmpleado()   → ID: 4002
    // - buscarEmpleado()   → ID: 4003
    // - modificarEmpleado()→ ID: 4004
    // - desplegarEmpleados()→ ID: 4005
    // Esto permite mantener un historial de auditoría básico.
};

#endif // EMPLEADOS_H
