//Karla Ruiz 9959-24-6859
#ifndef CUENTAS_H // Verifica si CUENTAS_H no ha sido definido.
#define CUENTAS_H // Define CUENTAS_H para evitar inclusiones múltiples.

#include <string> // Incluye la biblioteca para manejar cadenas de texto.
#include "Bitacora.h" // Incluye el encabezado de la clase Bitacora.

using namespace std;
class Cuentas { // Define la clase Cuentas.
private:
    string usuario;//bitacora
    string tipoCuentaSeleccionada; // Almacena el tipo de cuenta seleccionada.


public:
    Cuentas(); // Constructor de la clase Cuentas.
void setUsuario(const string& u);//bitacora
    void menuTipoCuenta(const string& bancoNombre); // Método para mostrar el menú de tipos de cuenta.
    string getTipoCuenta() const; // Método para obtener el tipo de cuenta seleccionada.
};

#endif // Fin de la directiva de inclusión condicional.
