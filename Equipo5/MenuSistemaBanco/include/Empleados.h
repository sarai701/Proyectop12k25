<<<<<<< HEAD
<<<<<<< HEAD
=======
// Karla Patricia Ruiz OrdoÃ±ez 9959-24-6859
>>>>>>> 3509a453d075eb4d294700013dae9ae14bc31c71
=======
//Karla Patricia Ruiz Ordoñez 9959-24-6859
>>>>>>> 1ffb03612c47ce1169541ede7ad209ab9ac9dae4
#ifndef EMPLEADOS_H
#define EMPLEADOS_H

#include <vector>
#include <string>
<<<<<<< HEAD
<<<<<<< HEAD
#include "Bitacora.h"

// Clase para representar a un empleado
class Empleado {
public:
    std::string nombre;      // Nombre del empleado
    std::string codigo;      // Código de identificación
    std::string puesto;      // Puesto de trabajo
    std::string telefono;    // Teléfono del empleado
};

// Clase principal para la gestión de empleados
class Empleados {
private:
    std::vector<Empleado> empleados;   // Vector que almacena la lista de empleados

public:
    // Funciones
    void limpiarPantalla();            // Limpia la pantalla según el sistema operativo
    void pausar();                     // Pausa el programa hasta que se presione ENTER
    void cargarEmpleados();            // Carga los empleados desde el archivo
    void guardarEmpleados();           // Guarda todos los empleados en el archivo
    void ordenarEmpleados();           // Ordena a los empleados alfabéticamente por nombre

    // Funciones de menú
    void menuEmpleados();              // Muestra el menú principal de empleados
    void crearEmpleado();              // Agrega un nuevo empleado
    void borrarEmpleado();             // Borra un empleado por nombre y código
    void buscarEmpleado();             // Busca un empleado por nombre y código
    void modificarEmpleado();          // Modifica los datos de un empleado
    void desplegarEmpleados();         // Muestra todos los empleados registrados
=======
#include "Bitacora.h"  //  Se incluye para registrar acciones realizadas

// Clase que representa a un empleado individual
class Empleado {
public:
    std::string nombre;      // Nombre completo del empleado
    std::string codigo;      // CÃ³digo Ãºnico de identificaciÃ³n
    std::string puesto;      // Cargo o puesto dentro de la empresa
    std::string telefono;    // NÃºmero telefÃ³nico de contacto
};

// Clase que gestiona la lista de empleados y sus operaciones
class Empleados {
private:
    std::vector<Empleado> empleados;   // Lista de todos los empleados registrados
    Bitacora bitacoralogEmpleados;     // âœ… BitÃ¡cora para registrar las operaciones realizadas

public:
    // Funciones auxiliares
    void limpiarPantalla();            // Limpia la consola (compatible con Windows y Unix)
    void pausar();                     // Pausa la ejecuciÃ³n hasta que el usuario presione ENTER
    void cargarEmpleados();            // Carga los empleados desde el archivo "empleados.txt"
    void guardarEmpleados();           // Guarda la lista actual de empleados al archivo
    void ordenarEmpleados();           // Ordena a los empleados por nombre de forma ascendente

    // Funciones principales del menÃº
    void menuEmpleados();              // Muestra el menÃº de opciones para gestionar empleados
    void crearEmpleado();              // Permite ingresar un nuevo empleado y registrarlo
    void borrarEmpleado();             // Elimina un empleado con base en su nombre y cÃ³digo
    void buscarEmpleado();             // Busca un empleado especÃ­fico para visualizar su informaciÃ³n
    void modificarEmpleado();          // Edita los datos de un empleado existente
    void desplegarEmpleados();         // Muestra todos los empleados registrados

    //  Cada acciÃ³n importante se registra en la bitÃ¡cora:
    // - crearEmpleado()    â†’ ID: 4001
    // - borrarEmpleado()   â†’ ID: 4002
    // - buscarEmpleado()   â†’ ID: 4003
    // - modificarEmpleado()â†’ ID: 4004
    // - desplegarEmpleados()â†’ ID: 4005
    // Esto permite mantener un historial de auditorÃ­a bÃ¡sico.
>>>>>>> 3509a453d075eb4d294700013dae9ae14bc31c71
=======
#include "BitacoraLog.h" // <-- Asegúrate de que este archivo exista y esté implementado

using namespace std;

// Variable global para registrar las acciones de empleados en la bitácora
extern BitacoraLog bitacoralogEmpleados;

// ==============================
// Estructura de Datos Empleado
// ==============================
struct Empleado {
    string nombre;   // Nombre completo del empleado
    string codigo;   // Código identificador único del empleado
    string puesto;   // Puesto o cargo que ocupa en la empresa
    string telefono; // Número de contacto
};

// ============================
// Clase Empleados
// ============================
class Empleados {
private:
    vector<Empleado> empleados;  // Contenedor de todos los empleados registrados

public:
    // Constructor
    Empleados();

    // Métodos CRUD
    void crearEmpleado(const string& usuario);
    void borrarEmpleado(const string& usuario);
    void buscarEmpleado(const string& usuario);
    void modificarEmpleado(const string& usuario);
    void desplegarEmpleados(const string& usuario);

    // Interfaz de usuario
    void menuEmpleados(const string& usuario);

    // Utilidades
    void limpiarPantalla();
    void pausar();

    // Gestión de archivos
    void cargarEmpleados();
    void guardarEmpleados();
    void ordenarEmpleados();
>>>>>>> 1ffb03612c47ce1169541ede7ad209ab9ac9dae4
};

#endif // EMPLEADOS_H
