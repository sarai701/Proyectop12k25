#include "Empleados.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
//Creado y documentado Por Isaias Cedillo (9959-24-1672) "IsaC8-bit"
Empleados::Empleados()
{
}
void Empleados::menuEmpleados()
{
    int eleccion = 0;
    char x;
    do
    {
        //Menu
        system("cls");
        cout << "\t\t\t-------------------------------" << endl;
        cout << "\t\t\t |   Registro de empleados  |" << endl;
        cout << "\t\t\t-------------------------------" << endl;
        cout << "\t\t\t 1. Ingreso de Empleados" << endl;
        cout << "\t\t\t 2. Despliegue de Empleados" << endl;
        cout << "\t\t\t 3. Modificar Empleados" << endl;
        cout << "\t\t\t 4. Borrar Empleados" << endl;
        cout << "\t\t\t 5. Salida" << endl;

        cout << "Presione el numero para el caso \n";
        cin >> eleccion;
         //Switch de eleccion
        switch(eleccion)
        {
            case 1:
                cout << "Opcion escogida... \n";
                registroEmpleados();
                cout << "Hay mas empleados por anadir? Y/N \n";
                cin >> x;
                while (x == 'y' || x == 'Y')
                {
                    registroEmpleados();
                }
                break;
            case 2:
                cout << "Opcion escogida...\n";
                listaEmpleados();
                break;
            case 3:
                cout << "Opcion escogida \n";
                cambioEmpleados();
                break;
            case 4:
                cout << "Opcion escogida \n";
                borrarEmpleados();
                break;
            case 5:
                cout <<"Regresando...."<<endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
        system("pause");
    } while(eleccion != 5);
}

void Empleados::registroEmpleados()
{
    //Llamada de biblioteca
    system("cls");
    fstream file;
    cout << "\n--------------------- Agregar Empleado ---------------------" << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
    //Getlines para obtener palabras con espacios
    cout << "Tipo de empleado (contrato/sueldo): ";
    getline(cin, tipoEmpleado);

    cout << "Nombre completo: ";
    getline(cin, Nombre);

    cout << "Sueldo: Q";
    cin >> sueldo;
    //Creacion de archivo
    file.open("Empleados.txt", ios::app | ios::out);
    //Limitador nuevo y eficiente (Gracias a DeepSeek, Revisa que el archivo exista o este abierto
    if (!file.is_open())
    {
        cout << "Error al abrir el archivo!" << endl;
        return;
    }

    // Guardar con un delimitador claro (|)
    file << tipoEmpleado << "|" << Nombre << "|" << sueldo << "\n";
    //Registro completado
    file.close();
    cout << "\nEmpleado registrado exitosamente!\n";
}

void Empleados::listaEmpleados()
{
    //Llamada a libreria
    system("cls");
    fstream file;
    int total = 0;

    cout << "\n==================== LISTA DE EMPLEADOS ====================" << endl;
    //Abre el archivo previamente creado y revisa su existencia
    file.open("Empleados.txt", ios::in);
    if (!file.is_open())
    {
        cout << "\nNo hay empleados registrados o el archivo no existe.\n";
        return;
    }
    // busca lineas con delimitador y un while
    string linea;
    while (getline(file, linea)) // Leer línea por línea
    {
        //Busca los registros con un delimitador con el metodo size_t
        size_t pos1 = linea.find("|");
        size_t pos2 = linea.find("|", pos1 + 1);
        //Si no hay nada antes del | (npos) el cual verifica que sea todo
        if (pos1 != string::npos && pos2 != string::npos)
        {   //Revista todo hasta el primer |
            tipoEmpleado = linea.substr(0, pos1);
            //Revisa el segundo | tomando en cuenta la distancia como los vectores
            Nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            //convierte a string el float
            sueldo = stof(linea.substr(pos2 + 1));
            //Impresion y validacion
            cout << "\nTipo: " << tipoEmpleado << endl;
            cout << "Nombre: " << Nombre << endl;
            cout << "Sueldo: Q" << fixed << setprecision(2) << sueldo << endl;
            total++;
        }
    }
   //Revision de empleados
    if (total == 0)
    {
    cout << "\nNo hay empleados registrados.\n";
    }
    else
    cout << "\nTotal de empleados: " << total << endl;

    file.close();
}
void Empleados::cambioEmpleados() {
    // Limpiar pantalla
    system("cls");
    fstream file;
    string tipoEmpleadoCambio, NombreCambio;
    float sueldoCambio;
    int found = 0;

    cout << "\n-------------------------Cambios laborales (no despidos)-------------------------" << endl;

    // Solicitar nombre del empleado a modificar
    cout << "\n Ingrese el nombre de la persona a modificar: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
    getline(cin, NombreCambio);

    // Abrir archivo original para lectura
    file.open("Empleados.txt", ios::in);
    if (!file.is_open()) {
        cout << "\n\t\t\tNo hay información o no se pudo abrir el archivo..." << endl;
        return;
    }

    string linea;
    while (getline(file, linea)) {
        size_t pos1 = linea.find("|");
        size_t pos2 = linea.find("|", pos1 + 1);
        if (pos1 != string::npos && pos2 != string::npos) {
            string nombreTemp = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            if (nombreTemp == NombreCambio) {
                found++;
                break;
            }
        }
    }
    file.close();

    if (found == 0) {
        cout << "\n\t\t\tUsuario no encontrado..." << endl;
        return;
    }

    // Solicitar los nuevos datos
    cout << "\n Ingrese el nuevo tipo de empleado (contrato/sueldo): ";
    getline(cin, tipoEmpleadoCambio);
    cout << "\n Ingrese el nuevo sueldo: ";
    cin >> sueldoCambio;

    // Crear archivo temporal para escribir los datos actualizados
    fstream file1;
    file.open("Empleados.txt", ios::in);
    file1.open("Record.txt", ios::out);
    if (!file1.is_open()) {
        cout << "\n\t\t\tError al crear archivo temporal." << endl;
        file.close();
        return;
    }

    while (getline(file, linea)) {
        size_t pos1 = linea.find("|");
        size_t pos2 = linea.find("|", pos1 + 1);
        if (pos1 != string::npos && pos2 != string::npos) {
            string tipoTemp = linea.substr(0, pos1);
            string nombreTemp = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            float sueldoTemp = stof(linea.substr(pos2 + 1));
            if (nombreTemp == NombreCambio) {
                file1 << tipoEmpleadoCambio << "|" << NombreCambio << "|" << sueldoCambio << "\n";
                cout << "\n\t\t\tEmpleado actualizado con exito." << endl;
            } else {
                file1 << tipoTemp << "|" << nombreTemp << "|" << sueldoTemp << "\n";
            }
        }
    }
    file.close();
    file1.close();

    remove("Empleados.txt");
    rename("Record.txt", "Empleados.txt");
}



void Empleados::borrarEmpleados()
{
    // Limpiar la pantalla
    system("cls");
    fstream file, file1;
    string CambioNombreBorrar;
    int found = 0;

    cout << "\n-------------------------Detalles Persona a Borrar-------------------------" << endl;

    // Abrir el archivo de empleados para lectura
    file.open("Empleados.txt", ios::in);
    if (!file.is_open())
    {
        cout << "\n\t\t\tNo hay información o no se pudo abrir el archivo..." << endl;
        return;
    }

    // Solicitar el nombre del empleado a borrar
    cout << "\n Ingrese el nombre de la Persona que quiere borrar: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
    getline(cin, CambioNombreBorrar); // Leer nombre completo con espacios

    // Abrir archivo temporal donde se guardarán los empleados no eliminados
    file1.open("Record.txt", ios::out);
    if (!file1.is_open())
    {
        cout << "\n\t\t\tError al crear archivo temporal." << endl;
        file.close();
        return;
    }

    string linea;
    // Leer el archivo original línea por línea
    while (getline(file, linea))
    {
        // Buscar posiciones del delimitador |
        size_t pos1 = linea.find("|");
        size_t pos2 = linea.find("|", pos1 + 1);

        // Verificar que los delimitadores existan
        if (pos1 != string::npos && pos2 != string::npos)
        {
            // Extraer campos de la línea
            tipoEmpleado = linea.substr(0, pos1);
            Nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            sueldo = stof(linea.substr(pos2 + 1));

            // Si el nombre no coincide con el que se quiere borrar, se escribe en el archivo temporal
            if (CambioNombreBorrar != Nombre)
            {
                file1 << tipoEmpleado << "|" << Nombre << "|" << sueldo << "\n";
            }
            else
            {
                found++; // Se encontró el empleado a borrar
                cout << "\n\t\t\tBorrado de información exitoso" << endl;
            }
        }
    }

    file.close();
    file1.close();

    // Revisión final: si se encontró y eliminó al empleado, se reemplaza el archivo original
    if (found == 0)
    {
        cout << "\n\t\t\tEmpleado no encontrado..." << endl;
        remove("Record.txt"); // Eliminar archivo temporal si no hubo coincidencias
    }
    else
    {
        remove("Empleados.txt");              // Borrar archivo original
        rename("Record.txt", "Empleados.txt"); // Renombrar archivo temporal como definitivo
    }
}
