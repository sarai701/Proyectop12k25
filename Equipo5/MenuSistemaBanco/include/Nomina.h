#ifndef NOMINAS_H
#define NOMINAS_H

#include <iostream>
#include <vector>
#include <string>

struct DatosEmpleado {
    std::string nombre;
    std::string telefono;
    std::string codigo;
    std::string direccion;
    double salario;
};

class Nominas {
private:
    std::vector<DatosEmpleado> empleados;

public:
    void menuNominas();
    void crearEmpleado();
    void borrarEmpleado();
    void buscarEmpleado();
    void modificarEmpleado();
};

#endif

