#include <iostream>
#include<fstream>
#include <limits>
#include "Opciones.h"
#include "usuarios.h"
#include "bitacora.h"
#include "sistema.h"
//Realizado por ANGEL ROQUEL
using namespace std;
void menuGeneral();
int contrasenia = 147;
int ingreso;
int main()
{
sistema seguridad;//Objeto creado de clase sistema
Opciones opciones;//Objeto creado de clases Opciones
    int opcion;

    do {
    // Limpiar la pantalla
    system("cls");

    // Mostrar el menú
    cout << "=======================" << endl;
    cout << "1. Registrar usuario ||" << endl;
    cout << "2. Ingresar          ||" << endl;
    cout << "3. Mostrar usuarios  ||" << endl;
    cout << "4. Salir             ||" << endl;
    cout << "=======================" << endl << endl;

    // Solicitar la opción al usuario
    cout << "Ingrese opcion: ";

    try {
        // Verificar si la entrada es un entero válido
        if (!(cin >> opcion)) {
            // Lanzar una excepción si la entrada no es válida
            throw runtime_error("Error de entrada");
        }

        // Verificar si la opción está dentro del rango válido
        if (opcion < 1 || opcion > 4) {
            // Lanzar una excepción si la opción no es válida
            throw runtime_error("Opción invalida");
        }
    } catch (const exception& e) {
        // Manejar la excepción y mostrar un mensaje de error
        cerr << "Ingrese datos validos.." << endl;

        // Limpiar el flag de error y ignorar la entrada inválida
        cin.clear();
        cin.ignore(10000, '\n');

        // Pausar el sistema y continuar con el siguiente ciclo
        system("pause");
        continue;
    }

    // Procesar la opción seleccionada
    switch (opcion) {
        case 1:
            // Registrar un nuevo usuario
            system("cls");
            cout << "Ingrese contrasenia maestra.." << endl;
            cin >> ingreso;
            if (ingreso == contrasenia) {
                seguridad.registrarUsuario();
            } else {
                cout << "Contrasenia incorrecta..." << endl;
                cout << "Regresando......." << endl;
            }
            break;
        case 2:
            // Ingresar al sistema
            seguridad.ingresarUsuario();
            break;
        case 3:
            // Mostrar los usuarios registrados
            seguridad.mostrarUsuarios();
            break;
        case 4:
            // Salir del sistema
            cout << "Saliendo del sistema..." << endl;
            break;
    }

    // Pausar el sistema antes de mostrar el menú nuevamente
    system("pause");
} while (opcion != 4); // Continuar hasta que se seleccione la opción de salir
    return 0;
}
