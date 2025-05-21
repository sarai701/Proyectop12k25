// steven vasquez
// marlon de leon

#include "Vendedores.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "encabezado.h"

using namespace std;

vector<Vendedores> Vendedores::vendedores;
int Vendedores::contadorVendedores = 100; // Código inicial

Vendedores::Vendedores() {}

Vendedores::Vendedores(string n, string t, string cod)
    : nombre(n), telefono(t), codigo(cod) {}

std::vector<Vendedores>& Vendedores::obtenerVendedores() {
    return vendedores;
}

void Vendedores::MenuVendedores() {
    int opcion;
    do {
        system("cls");
        cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
        cout << "\n\t\t\t---------------------------\n";
        cout << "\t\t\t |   SISTEMA DE VENDEDORES  |\n";
        cout << "\t\t\t---------------------------\n";
        cout << "\t\t\t 1. NUEVO VENDEDOR\n";
        cout << "\t\t\t 2. MODIFICAR VENDEDOR\n";
        cout << "\t\t\t 3. ELIMINAR VENDEDOR\n";
        cout << "\t\t\t 4. SALIR\n";
        cout << "\t\t\t-------------------------------\n";
        cout << "\t\t\tIngresa tu opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                AgregarVendedor();
                break;
            case 2:
                ModificarVendedor();
                break;
            case 3:
                EliminarVendedor();
                break;
            case 4:
                return;
            default:
                cout << "\n\t\t\t Opción inválida...Intente otra vez...\n";
                cin.ignore();
                cin.get();
        }
    } while (opcion != 4);
}

void Vendedores::AgregarVendedor() {
    system("cls");
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t---------------------\n";
    cout << "\t\t\t |   NUEVO VENDEDOR   |\n";
    cout << "\t\t\t----------------------\n";

    string nombre, telefono;
    string codigo = to_string(contadorVendedores++);

    cout << "\t\t\tIngrese el nombre del vendedor: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "\t\t\tIngrese el número telefónico del vendedor: ";
    cin >> telefono;

    vendedores.push_back(Vendedores(nombre, telefono, codigo));
    GuardarEnBinario();
    cout << "\t\t\tVendedor agregado exitosamente.\n";

    cout << "\nPresione ENTER para regresar al menú...";
    cin.ignore();
    cin.get();
}

void Vendedores::ModificarVendedor() {
    system("cls");
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t--------------------------\n";
    cout << "\t\t\t |   MODIFICAR VENDEDOR   |\n";
    cout << "\t\t\t--------------------------\n";

    string codigoBuscado;
    cout << "\t\t\tIngrese el código del vendedor a modificar: ";
    cin >> codigoBuscado;

    for (auto& vendedor : vendedores) {
        if (vendedor.codigo == codigoBuscado) {
            cout << "\t\t\tVendedor encontrado:\n";
            cout << "\t\t\tNombre: " << vendedor.nombre << "\n";
            cout << "\t\t\tTelefono: " << vendedor.telefono << "\n";

            cout << "\t\t\t¿Que desea modificar?\n";
            cout << "\t\t\t1. Nombre\n";
            cout << "\t\t\t2. Telefono\n";
            int opcion;
            cin >> opcion;

            if (opcion == 1) {
                cout << "\t\t\tIngrese nuevo nombre: ";
                cin.ignore();
                getline(cin, vendedor.nombre);
            } else if (opcion == 2) {
                cout << "\t\t\tIngrese nuevo número telefónico: ";
                cin >> vendedor.telefono;
            } else {
                cout << "\t\t\tOpción inválida.\n";
            }

            GuardarEnBinario();
            cout << "\t\t\tVendedor modificado exitosamente.\n";
            break;
        }
    }

    cout << "\t\t\tPresione ENTER para regresar al menú...";
    cin.ignore();
    cin.get();
}

void Vendedores::EliminarVendedor() {
    system("cls");
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t-------------------------\n";
    cout << "\t\t\t |   ELIMINAR VENDEDOR   |\n";
    cout << "\t\t\t-------------------------\n";

    string codigoBuscado;
    cout << "\t\t\tIngrese el código del vendedor a eliminar: ";
    cin >> codigoBuscado;

    for (auto it = vendedores.begin(); it != vendedores.end(); ++it) {
        if (it->codigo == codigoBuscado) {
            vendedores.erase(it);
            GuardarEnBinario();
            cout << "\t\t\tVendedor eliminado exitosamente.\n";
            break;
        }
    }

    cout << "\t\t\tPresione ENTER para regresar al menú...";
    cin.ignore();
    cin.get();
}

void Vendedores::MostrarVendedores() {
    system("cls");
    cout << "\n\t\t\t USUARIO ACTUAL: " << usuarioActual; //Marlon De Leon 5001
    cout << "\n\t\t\t----------------------------\n";
    cout << "\t\t\t |   LISTADO DE VENDEDORES   |\n";
    cout << "\t\t\t----------------------------\n";

    if (vendedores.empty()) {
        cout << "\t\t\tNo hay vendedores registrados.\n";
    } else {
        cout << left << setw(10) << "Codigo" << setw(20) << "Nombre"
             << setw(15) << "Telefono" << "\n";
        cout << "-------------------------------------------\n";

        for (const auto& vendedor : vendedores) {
            cout << left << setw(10) << vendedor.codigo
                 << setw(20) << vendedor.nombre
                 << setw(15) << vendedor.telefono << "\n";
        }
    }

    cout << "\t\t\tPresione ENTER para regresar al menú...";
    cin.ignore();
    cin.get();
}

void Vendedores::GuardarEnBinario() {
    ofstream archivo("vendedores.dat", ios::binary);
    if (!archivo) {
        cout << "Error al abrir el archivo.\n";
        return;
    }
    for (const auto& vendedor : vendedores) {
        archivo.write(reinterpret_cast<const char*>(&vendedor), sizeof(Vendedores));
    }
    archivo.close();
}

void Vendedores::CargarDesdeBinario() {
    ifstream archivo("vendedores.dat", ios::binary);
    if (!archivo) return;

    Vendedores vendedor;
    while (archivo.read(reinterpret_cast<char*>(&vendedor), sizeof(Vendedores))) {
        vendedores.push_back(vendedor);
    }
    archivo.close();
}
