//Programaddo por Priscila Sarai Guzmán Calgua 9959-23-450
#ifndef NOMINAS_H
#define NOMINAS_H

#include <string>
#include <vector>

struct Empleados {
    std::string nombre;
    std::string telefono;
    std::string codigo;
    std::string direccion;
    float salario;
};

class Nominas {
private:
    std::vector<Empleados> empleados; // Lista en memoria de empleados
    void cargarEmpleados();           // Carga desde empleados.txt
    void guardarEmpleados();          // Guarda toda la lista en empleados.txt
    void ordenarEmpleados();          // Ordena alfabéticamente por nombre

public:
    void menuNominas();       // Muestra el menú principal
    void crearEmpleado();     // Agrega un nuevo empleado
    void borrarEmpleado();    // Borra un empleado por nombre y código
    void buscarEmpleado();    // Busca un empleado por nombre y código
    void modificarEmpleado(); // Modifica un empleado existente
    void desplegarEmpleados();// Muestra todos los empleados

    void limpiarPantalla();   // Limpia la consola
    void pausar();            // Pausa hasta que se presione ENTER
};

#endif


