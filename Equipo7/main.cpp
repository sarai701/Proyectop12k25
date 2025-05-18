#include <iostream>
#include "SistemaVentas.h"
#include "Login.h"
#include "bitacora.h"
#include <fstream>
#include <string>


using namespace std;


string usuarioActual; // Para guardar el nombre del usuario bitacora

void mostrarMenuPrincipal();
void mostrarArchivo();  // Función para mostrar el archivo bitacora.txt
int main() {
    int opcion;
    bool accesoPermitido = false;


    do {

        system ("cls");
        cout << "\n--- Bienvenido al Sistema ---\n";
        cout << "1. Iniciar Sesion\n";
        cout << "2. Registrarse\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Para evitar errores con getline

        switch (opcion) {
            case 1:
                accesoPermitido = iniciarSesion(usuarioActual);
                break;
            case 2:
                registrarUsuario();
                break;
            case 3:
                cout << "\n\nSaliendo del sistema...\n";
                return 0;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (!accesoPermitido);

    mostrarMenuPrincipal();
     registrarEvento(usuarioActual, "Cerro sesion desde menu principal");
    return 0;
}




void mostrarMenuPrincipal() {
    SistemaVentas sistema;
    int opcion;
    do {
        system ("cls");
        cout << "\n--- Menu General ---\n";
        cout << "1. Archivo\n";
        cout << "2. Catalogos\n";
        cout << "3. Procesos\n";
        cout << "4. Informes\n";
        cout << "5. Salir del sistema\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarEvento(usuarioActual, "Entro a la opción Archivo");
                cout<< "sin funcion\n";
                system("pause");
                break;
            case 2:
                registrarEvento(usuarioActual, "Entro a la opción Catálogos");
                sistema.mostrarMenu();
                break;
            case 3:
                registrarEvento(usuarioActual, "Entro a la opción Procesos");
                sistema.realizarVenta();
                break;
            case 4:
                registrarEvento(usuarioActual, "Entro a la opción Informes");
                mostrarArchivo(); // Mostrar contenido de bitacora.txt
                system ("pause");
                break;
            case 5:
                registrarEvento(usuarioActual, "Salio del menú general");
                cout << "Cerrando sesion...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);
}



void mostrarArchivo() {
    system("cls");
    std::ifstream archivo("bitacora.bin", std::ios::binary);
    if (!archivo) {
        std::cout << "No se pudo abrir bitacora.bin" << std::endl;
        return;
    }

    std::cout << "=== Contenido de bitacora.bin ===" << std::endl;
    size_t longitud;
    std::string mensaje;

    while (archivo.read(reinterpret_cast<char*>(&longitud), sizeof(longitud))) {
        mensaje.resize(longitud);
        archivo.read(&mensaje[0], longitud);
        std::cout << mensaje << std::endl;
    }

    archivo.close();
}
