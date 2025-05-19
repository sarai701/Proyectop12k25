#include <iostream>
#include "usuario.h"
#include "compras.h"
#include <vector>
#include <iomanip>
#include <limits>
#include <windows.h> //Libreria para mostrar tildes

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    vector<Producto> listaCompras;
    int opcion;
    string nombreUsuario, contrasena;

    // Menú de registro e inicio de sesión
    int opcionLogin;
    do {
        cout << "\n=== SISTEMA DE REGISTRO E INICIO DE SESION ===" << endl;
        cout << "1. Registrar nuevo usuario" << endl;
        cout << "2. Iniciar sesión" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcionLogin;

        // Si elige registrar
        if (opcionLogin == 1) {
            cout << "Ingrese nombre de usuario: ";
            cin >> nombreUsuario;
            cout << "Ingrese contraseña: ";
            cin >> contrasena;
            Usuario::registrarUsuario(nombreUsuario, contrasena);
        }
        // Si elige iniciar sesión
        else if (opcionLogin == 2) {
            bool sesionExitosa = false;
            while (!sesionExitosa) {
                cout << "Ingrese nombre de usuario: ";
                cin >> nombreUsuario;
                cout << "Ingrese contraseña: ";
                cin >> contrasena;

                // Verifica si el inicio de sesión es exitoso
                if (Usuario::iniciarSesion(nombreUsuario, contrasena)) {
                    sesionExitosa = true;
                    cout << "\n¡Bienvenido " << nombreUsuario << "!" << endl;

                    // Menú de compras después de inicio de sesión
                    do {
                        Compras::mostrarMenu(); // Mostrar el menú de compras
                        cin >> opcion;

                        // Dependiendo de la opción, ejecuta las funciones correspondientes
                        switch (opcion) {
                            case 1:
                                Compras::registrarCompra(listaCompras);
                                break;
                            case 2:
                                Compras::mostrarHistorial(listaCompras);
                                break;
                            case 3:
                                Compras::buscarPorProveedor(listaCompras);
                                break;
                            case 4:
                                cout << "\n💰 Total gastado: Q" << fixed << setprecision(2)
                                     << Compras::calcularTotalGastado(listaCompras) << endl;
                                break;
                            case 5:
                                cout << "\n👋 Saliendo del sistema...\n";
                                break;
                            default:
                                cout << "\n❌ Opción inválida. Intente nuevamente." << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    } while (opcion != 5); // Salir cuando opción 5 es seleccionada
                } else {
                    cout << "❌ Usuario o contraseña incorrectos. Intenta nuevamente." << endl;
                }
            }
        }
        // Si elige salir
        else if (opcionLogin == 3) {
            cout << "👋 Saliendo del sistema..." << endl;
        }
        // Si elige una opción no válida
        else {
            cout << "❌ Opción no válida. El programa se cerrará." << endl;
        }
    } while (opcionLogin != 3); // Si elige salir, termina el programa

    return 0;
}
