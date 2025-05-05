#include <iostream>
#include<fstream>

#include "Opciones.h"
#include "usuarios.h"
#include "bitacora.h"
#include "sistema.h"

using namespace std;
void menuGeneral();

int main()
{
sistema seguridad;//Objeto creado de clase sistema-ANGEL ROQUEL
Opciones opciones;//Objeto creado de clases Opciones-ANGEL ROQUEL
    int opcion;

    do {//Ciclo de sistema de seguridad, registro ingreso de usuarios-ANGEL ROQUEL
        system ("cls");
        cout << "1. Registrar usuario" << endl;
        cout << "2. Ingresar usuario" << endl;
        cout << "3. Mostrar usuarios" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                seguridad.registrarUsuario();
                break;
            case 2:
                seguridad.ingresarUsuario();
                break;
            case 3:
                seguridad.mostrarUsuarios();
                break;
            case 4:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion invalida. Por favor, intente nuevamente." << endl;
        }system("pause");
    } while (opcion != 4);
    return 0;
}
