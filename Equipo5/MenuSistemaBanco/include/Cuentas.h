//Karla Patricia Ruiz Ordoñez
#ifndef CUENTAS_H // Verifica que este archivo solo se incluya una vez durante la compilación
#define CUENTAS_H

#include <string> // Se incluye la biblioteca estándar de C++ para trabajar con strings

#include "Bitacora.h" // Se incluye la clase Bitacora, que se usará para registrar acciones

class Cuentas { // Declaración de la clase Cuentas
private:
    std::string tipoCuentaSeleccionada;  // Atributo que almacena el tipo de cuenta seleccionada (ej. "Ahorro", "Corriente")

    static Bitacora bitacoraCuentas;  // Objeto estático de tipo Bitacora para registrar las acciones relacionadas a cuentas

public:
    Cuentas();   // Constructor por defecto

    void menuTipoCuenta(const std::string& bancoNombre);  // Método para mostrar el menú de selección de tipo de cuenta

    std::string getTipoCuenta() const; // Método para obtener el tipo de cuenta seleccionada
};

#endif // Fin de la condición de inclusión única
