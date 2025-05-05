#include "Usuario.h"
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <sstream> // Agregado para procesar cada línea
#include "Bitacora.h"

using namespace std;

usuarios::usuarios()
{
    // ctor
}

usuarios::~usuarios()
{
    // dtor
}

bool usuarios::loginUsuarios()
{
    string usuario, contra;
    int contador = 0;
    bool ingresa = false;

    do
    {
        system("cls");
        cout << "---------------------------" << endl;
        cout << " AUTENTICACION DE USUARIOS " << endl;
        cout << "---------------------------" << endl;

        cout << "\nNombre Usuario: ";
        getline(cin, usuario);

        cout << "\nContrasena: ";
        char caracter;
        contra = "";
        caracter = getch();
        while (caracter != 13) // ENTER
        {
            if (caracter != 8) // RETROCESO
            {
                contra.push_back(caracter);
                cout << "*";
            }
            else
            {
                if (contra.length() > 0)
                {
                    cout << "\b \b";
                    contra = contra.substr(0, contra.length() - 1);
                }
            }
            caracter = getch();
        }

        if (buscar(usuario, contra))
        {
            ingresa = true;
            cout << "\n=== Bienvenido al Sistema ===" << endl;
            bitacora auditoria;
            auditoria.insertar(name, 100, "LOGS", "Inicio exitoso");
            cin.get();
        }
        else
        {
            cout << "\nEl usuario y/o contrasena son incorrectos" << endl;
            bitacora auditoria;
            auditoria.insertar(usuario, 100, "LOGF", "Intento fallido");
            cin.get();
            contador++;
        }

    } while (!ingresa && contador < 3);

    if (!ingresa)
    {
        cout << "\nLo siento, no puede ingresar al sistema..." << endl;
        cin.get();
    }

    return ingresa;
}

void usuarios::menuUsuarios()
{
    int choice;
    do
    {
        system("cls");
        cout << "\t\t\t-------------------------------------------------------" << endl;
        cout << "\t\t\t |   SISTEMA GESTION DE SEGURIDAD - Catalogos Usuarios |" << endl;
        cout << "\t\t\t-------------------------------------------------------" << endl;
        cout << "\t\t\t 1. Ingreso Usuarios" << endl;
        cout << "\t\t\t 2. Consulta Usuarios" << endl;
        cout << "\t\t\t 3. Modificacion Usuarios" << endl;
        cout << "\t\t\t 4. Eliminacion Usuarios" << endl;
        cout << "\t\t\t 5. Retornar menu anterior" << endl;
        cout << "\t\t\t-------------------------------------------------------" << endl;
        cout << "\t\t\tOpcion a escoger:[1/2/3/4/5]" << endl;
        cout << "\t\t\t-------------------------------------------------------" << endl;
        cout << "\t\t\tIngresa tu Opcion: ";
        cin >> choice;
        cin.ignore(); // <- muy importante: limpiar buffer

        switch (choice)
        {
        case 1:
            // Aquí iría código para agregar usuarios
            break;
        case 2:
            // Consultar usuarios
            break;
        case 3:
            // Modificar usuarios
            break;
        case 4:
            // Eliminar usuarios
            break;
        case 5:
            break;
        default:
            cout << "\n\t\t\t Opcion invalida...Por favor prueba otra vez.." << endl;
        }
        cin.get();
    } while (choice != 5);
}

bool usuarios::buscar(string user, string passw)
{
    fstream file;
    file.open("Usuarios.txt", ios::in);

    if (!file)
    {
        cout << "\nNo hay informacion de usuarios..." << endl;
        return false;
    }

    string linea;
    while (getline(file, linea))
    {
        istringstream iss(linea);
        int tempId;
        string tempName, tempPass;

        iss >> tempId >> tempName >> tempPass;

        if (user == tempName && passw == tempPass)
        {
            id = tempId;
            name = tempName;
            pass = tempPass;
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

string usuarios::getNombre()
{
    return name;
}

void usuarios::setNombre(string nombre)
{
    name = nombre;
}
