#include "Bitacora.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
#include<algorithm>
#include<ctime>

using namespace std;

void bitacora::menu()
{
    int choice;
    do {
        system("cls");

        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\t |   SISTEMA GESTION BITACORA  |"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\t 1. Despliegue Bitacora"<<endl;
        cout<<"\t\t\t 2. Exit"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\tOpcion a escoger:[1/2]"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\tIngresa tu Opcion: ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            desplegar();
            break;
        case 2:
            break;
        default:
            cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
            cin.get();
        }
    } while(choice != 2);
}

void bitacora::insertar(string nombre, int codigo, string aplicacion, string accion)
{
    fstream file;
    fstream readFile;

    int ultimoCodigo = 1999;
    string line;

    readFile.open("bitacora.txt", ios::in);
    if (readFile)
    {
        while (getline(readFile, line))
        {
            if (line.length() >= 4) {
                string codStr = line.substr(0, 4);
                bool esNumero = all_of(codStr.begin(), codStr.end(), ::isdigit);
                if (esNumero) {
                    int cod = stoi(codStr);
                    if (cod > ultimoCodigo)
                        ultimoCodigo = cod;
                }
            }
        }
    }
    readFile.close();

    int nuevoCodigo = ultimoCodigo + 1;
    if (nuevoCodigo > 2999)
    {
        cout << "❌ Límite de bitácoras alcanzado (2999)" << endl;
        return;
    }

    file.open("bitacora.txt", ios::app | ios::out);

    time_t now = time(0);
    struct tm * timeinfo = localtime(&now);

    char dateBuffer[25];
    char timeBuffer[10];

    strftime(dateBuffer, sizeof(dateBuffer), "%b %d %Y %H:%M:%S", timeinfo);
    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", timeinfo);

    // Escribimos los campos con formato fijo
    file << std::setw(4) << std::setfill('0') << nuevoCodigo << " "
         << std::left << std::setw(20) << nombre
         << std::left << std::setw(20) << aplicacion
         << std::left << std::setw(30) << accion
         << std::left << std::setw(30) << dateBuffer
         << std::left << std::setw(10) << timeBuffer << "\n";


    file.close();
}

void bitacora::desplegar() {
    system("cls");
    fstream file;
    string linea;
    int total = 0;

    cout << "\n-------------------------Tabla de Detalles de Bitacora -------------------------" << endl;
    file.open("bitacora.txt", ios::in);
    if (!file) {
        cout << "\n\t\t\tNo hay información...";
    } else {
        while (getline(file, linea)) {
            if (linea.length() >= 103) { // Validación de longitud
                string codigo = linea.substr(0, 4);
                string nombre = linea.substr(5, 20);
                string aplicacion = linea.substr(26, 20);
                string accion = linea.substr(47, 30);
                string fecha = linea.substr(75, 19);  // Sep 25 2023 14:30:00
                string hora = linea.substr(95, 8);     // 14:30:00

                cout << "\n\t\t\t Codigo Bitacora: " << codigo << endl;
                cout << "\t\t\t Nombre Usuario:  " << nombre << endl;
                cout << "\t\t\t Aplicacion:      " << aplicacion << endl;
                cout << "\t\t\t Accion:          " << accion << endl;
                cout << "\t\t\t Fecha y Hora:    " << fecha << " " << hora << endl;
                cout << "-------------------------------------------------------------------------------\n";
                total++;
            } else {
                cout << "Error en formato de línea: " << linea << endl;
            }
        }
        if (total == 0) {
            cout << "\n\t\t\tNo hay información...";
        }
    }
    file.close();
    system("pause");
}
