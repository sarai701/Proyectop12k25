//Karla Patricia Ruiz Ordoñez 9959-24-6859
#include "Cuentas.h" // Incluye el encabezado de la clase Cuentas.
#include <iostream>  // Incluye la biblioteca estándar de entrada/salida.

Bitacora bitacoralogCuentas; // Inicializa una instancia estática de Bitacora.

using namespace std; // Permite usar elementos del espacio de nombres std sin prefijo.
void Cuentas::setUsuario(const string& u) {
    usuario = u;
}
Cuentas::Cuentas() { // Constructor de la clase Cuentas.
    tipoCuentaSeleccionada = "No configurada"; // Inicializa tipoCuentaSeleccionada con un valor por defecto.
}

void Cuentas::menuTipoCuenta(const string& bancoNombre) { // Método para mostrar el menú de tipos de cuenta.
    int opcion; // Variable para almacenar la opción seleccionada por el usuario.
    do {
        cout << "\nUsuario: " << usuario << endl;
        cout << "\n===== TIPO DE CUENTA =====\n"; // Imprime el encabezado del menú.
        cout << "--------------------------------------\n"; // Línea divisoria.
        cout << " Banco:    " << bancoNombre << "\n"; // Muestra el nombre del banco.
        cout << "--------------------------------------\n"; // Línea divisoria.
        cout << "\n1. Cuenta Corriente"; // Opción 1 del menú.
        cout << "\n2. Cuenta de Ahorro"; // Opción 2 del menú.
        cout << "\nSeleccione una opción: "; // Solicita al usuario que seleccione una opción.
        cin >> opcion; // Lee la opción ingresada por el usuario.
        cin.ignore(); // Ignora el carácter de nueva línea dejado en el buffer.

        switch (opcion) { // Estructura de control para manejar la opción seleccionada.
            case 1: // Si la opción es 1.
                tipoCuentaSeleccionada = "Corriente"; // Establece tipoCuentaSeleccionada a "Corriente".
                bitacoralogCuentas.insertar(usuario, 4610, "Cuentas", "Cuenta Corriente"); // Registra la selección en la bitácora.
                return; // Sale del método.
            case 2: // Si la opción es 2.
                tipoCuentaSeleccionada = "Ahorro"; // Establece tipoCuentaSeleccionada a "Ahorro".
                bitacoralogCuentas.insertar(usuario, 4611, "Cuentas", "Cuenta de Ahorro"); // Registra la selección en la bitácora.
                return; // Sale del método.
            default: // Si la opción no es válida.
                cout << "Opción inválida.\n"; // Informa al usuario que la opción es inválida.
                break; // Continúa el ciclo.
        }
    } while (true); // Repite el ciclo hasta que se seleccione una opción válida.
}

string Cuentas::getTipoCuenta() const { // Método para obtener el tipo de cuenta seleccionada.
    return tipoCuentaSeleccionada; // Devuelve el tipo de cuenta seleccionada.
}
