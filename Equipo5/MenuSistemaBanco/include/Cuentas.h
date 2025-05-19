//Karla Patricia Ruiz Ordo�ez
#ifndef CUENTAS_H // Verifica que este archivo solo se incluya una vez durante la compilaci�n
#define CUENTAS_H

#include <string> // Se incluye la biblioteca est�ndar de C++ para trabajar con strings

#include "Bitacora.h" // Se incluye la clase Bitacora, que se usar� para registrar acciones

class Cuentas { // Declaraci�n de la clase Cuentas
private:
    std::string tipoCuentaSeleccionada;  // Atributo que almacena el tipo de cuenta seleccionada (ej. "Ahorro", "Corriente")

    static Bitacora bitacoraCuentas;  // Objeto est�tico de tipo Bitacora para registrar las acciones relacionadas a cuentas

public:
    Cuentas();   // Constructor por defecto

    void menuTipoCuenta(const std::string& bancoNombre);  // M�todo para mostrar el men� de selecci�n de tipo de cuenta

    std::string getTipoCuenta() const; // M�todo para obtener el tipo de cuenta seleccionada
};

#endif // Fin de la condici�n de inclusi�n �nica
