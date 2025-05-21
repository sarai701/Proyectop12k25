//Clase para mantenimiento de Acreedores
//Programado por Britany Hernandez  04/05/25

#include "acreedor.h"
#include "bitacora.h"
#include "usuarios.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<conio.h>
#include<iomanip>
using namespace std;

extern usuarios usuariosrRegistrado;

void acreedor::menu()
{
    int choice;
    char x;
    do {
        system("cls");
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\t|  SISTEMA GESTION ACREEDORES |"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\t 1. Ingreso Acreedores"<<endl;
        cout<<"\t\t\t 2. Despliegue Acreedores"<<endl;
        cout<<"\t\t\t 3. Modifica Acreedores"<<endl;
        cout<<"\t\t\t 4. Busca Acreedores"<<endl;
        cout<<"\t\t\t 5. Borra Acreedores"<<endl;
        cout<<"\t\t\t 6. Reportes Acreedores"<<endl;
        cout<<"\t\t\t 7. Salida"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\tOpcion a escoger:[1/2/3/4/5/6]"<<endl;
        cout<<"\t\t\tIngresa tu Opcion: ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            do {
                insertar(); // Agregar nuevo acreedor
                cout<<"\n\t\t\t Agrega otro Acreedor (Y/N): ";
                cin>>x;
            } while(x=='y'||x=='Y');
            break;
        case 2:
            desplegar(); // Mostrar todos los acreedores
            break;
        case 3:
            modificar(); // Editar información de un acreedor
            break;
        case 4:
            buscar(); // Buscar acreedor por ID
            break;
        case 5:
            borrar(); // Eliminar acreedor por ID
            break;
        case 6:
            reporte(); // Mostrar reporte tabular de acreedores
            break;
        case 7:
            break;
        default:
            cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
            cin.get();
        }
    } while(choice!= 7);
}

// Inserta un nuevo acreedor con validación y confirmación de datos
void acreedor::insertar()
{
    system("cls");
    fstream file;
    char confirmar;

    do {
        cout << "\n----------------------------------------------------------------------------------";
        cout << "\n-------------------------------- Agregar Acreedor --------------------------------\n";

        cout << "\t\t\tIngresa ID Acreedor         : ";
        cin >> id;
        cout << "\t\t\tIngresa Nombre Acreedor     : ";
        cin >> nombreAcreedor;
        cout << "\t\t\tIngresa Telefono Acreedor   : ";
        cin >> telefono;
        cout << "\t\t\tIngresa Num.Cuenta Acreedor : ";
        cin >> numCuenta;
        cout << "\t\t\tIngresa Banco del Acreedor  : ";
        cin >> banco;

        cout << "\nResumen de la información ingresada:\n";
        cout << "\t\t\tID Acreedor        : " << id << endl;
        cout << "\t\t\tNombre Acreedor    : " << nombreAcreedor << endl;
        cout << "\t\t\tTelefono Acreedor  : " << telefono << endl;
        cout << "\t\t\tNumero de Cuenta   : " << numCuenta << endl;
        cout << "\t\t\tBanco              : " << banco << endl;

        cout << "\n Esta seguro de guardar esta informacion? (S/N): ";
        cin >> confirmar;

        if (confirmar == 's' || confirmar == 'S') {
            file.open("acreedor.txt", ios::app | ios::out);
            file << left << setw(15) << id
                 << left << setw(15) << nombreAcreedor
                 << left << setw(15) << telefono
                 << left << setw(15) << numCuenta
                 << left << setw(15) << banco << "\n";
            file.close();

            bitacora auditoria;
            auditoria.insertar(usuariosrRegistrado.getNombre(), "8040", "INA"); // Insertar nuevo acreedor
            cout << "\nAcreedor guardado correctamente.\n";
        } else {
            cout << "\nVolvamos a ingresar los datos...\n";
        }

    } while (confirmar != 's' && confirmar != 'S');
}

// Muestra todos los acreedores registrados
void acreedor::desplegar()
{
    system("cls");
    fstream file;
    int total=0;
    cout<<"\n------------------------ Lista de Acreedores ------------------------"<<endl;
    file.open("acreedor.txt", ios::in);
    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...\n";
        system("pause");
    }
    else {
        file >> id >> nombreAcreedor >> telefono >> numCuenta >> banco;
        while(!file.eof()) {
            total++;
            cout<<"\n\t\t\t ID Acreedor        : "<<id<<endl;
            cout<<"\t\t\t Nombre Acreedor    : "<<nombreAcreedor<<endl;
            cout<<"\t\t\t Telefono Acreedor  : "<<telefono <<endl ;
            cout<<"\t\t\t Num.Cuenta Acreedor: "<<numCuenta<<endl;
            cout<<"\t\t\t Banco Acreedor     : "<<banco<<endl;

            file >> id >> nombreAcreedor >> telefono >> numCuenta >> banco;
        }
        if(total==0){
            cout<<"\n\t\t\tNo hay informacion...";
        }
        system("pause");
    }
    file.close();
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8041", "MA"); // Mostrar Acreedor
}

// Permite modificar la información de un acreedor ya existente
void acreedor::modificar()
{
    system("cls");
    fstream file, file1;
    string acreedor_id;
    int found=0;
    cout<<"\n---------------- Modificar Acreedor ----------------"<<endl;
    file.open("acreedor.txt", ios::in);
    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...";
        system("pause");
        file.close();
    }
    else {
        cout<<"\nIngrese ID del Acreedor que quiere modificar: ";
        cin>>acreedor_id;
        file1.open("temporal.txt", ios::app | ios::out);

        file >> id >> nombreAcreedor >> telefono >> numCuenta >> banco;

        while(!file.eof())
        {
            if(acreedor_id != id) {
                file1<<left<<setw(15)<< id << left<<setw(15)<< nombreAcreedor <<left<<setw(15)<< telefono <<left << setw(15)
                << numCuenta << left << setw(15)<< banco << "\n";
            }
            else {
                cout<<"\t\t\tIngrese Id Acreedor        : ";
                cin>>id;
                cout<<"\t\t\tIngrese Nombre Acreedor    : ";
                cin>>nombreAcreedor;
                cout<<"\t\t\tIngrese Telefono Acreedor  : ";
                cin>>telefono;
                cout<<"\t\t\tIngrese Num.Cuenta Acreedor: ";
                cin >>numCuenta;
                cout<<"\t\t\tIngrese Banco Acreedor     : ";
                cin>>banco;

                file1<<left<<setw(15)<< id << left<<setw(15)<< nombreAcreedor <<left<<setw(15)<< telefono <<left << setw(15)
                << numCuenta << left << setw(15)<< banco << "\n";
                found++;
            }
            file >> id >> nombreAcreedor >> telefono >> numCuenta >> banco;
        }
        if(found==0){
            cout<<"\n\t\t\tAcreedor no encontrado...";
            system("pause");
        }

        file1.close();
        file.close();
        remove("acreedor.txt");
        rename("temporal.txt","acreedor.txt");
        bitacora auditoria;
        auditoria.insertar(usuariosrRegistrado.getNombre(), "8042", "UAD"); // Actualizar Acreedor
    }
}

// Permite buscar un acreedor por ID y mostrar su información
void acreedor::buscar()
{
    system("cls");
    fstream file;
    int found=0;

    file.open("acreedor.txt", ios::in);
    cout<<"\n---------------- Buscar Acreedor ----------------"<<endl;
    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...";
        file.close();
    } else {
        string acreedor_id;
        cout<<"\nIngrese ID del Acreedor que quiere buscar : ";
        cin>>acreedor_id;
        file>> id >> nombreAcreedor >> telefono >> numCuenta >> banco;

        while(!file.eof()) {
            if(acreedor_id==id) {
                cout<<"\n\t\t\t ID Acreedor        : "<<id<<endl;
                cout<<"\t\t\t Nombre Acreedor    : "<<nombreAcreedor<<endl;
                cout<<"\t\t\t Telefono Acreedor  : "<<telefono<<endl;
                cout<<"\t\t\t Num.Cuenta Acreedor: "<<numCuenta<<endl;
                cout<<"\t\t\t Banco Acreedor     : "<<banco<<endl;
                found++;
            }
            file >> id >> nombreAcreedor >> telefono >> numCuenta >> banco;
        }
        if(found==0) cout<<"\n\t\t\tAcreedor no encontrado...\n";
        system("pause");
        file.close();
    }
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8043", "BAR"); // Buscar Acreedor
}

// Elimina un acreedor según su ID
void acreedor::borrar()
{
    system("cls");
    fstream file, file1;
    string acreedor_id;
    int found=0;
    cout<<"\n---------------- Borrar Acreedor ----------------"<<endl;
    file.open("acreedor.txt", ios::in);

    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...";
        system("pause");
        file.close();
    }
    else {
        cout<<"\n Ingrese el Id del Acreedor que quiere borrar: ";
        cin>>acreedor_id;
        file1.open("temporal.txt",ios::app | ios::out);
        file >> id >> nombreAcreedor >> telefono >> numCuenta >> banco;
        while(!file.eof()) {
            if(acreedor_id!= id) {
                file1<<left<<setw(15)<< id << left<<setw(15)<< nombreAcreedor <<left<<setw(15)<< telefono <<left << setw(15)
                << numCuenta << left << setw(15)<< banco << "\n";
            } else {
                found++;
                cout << "\nAcreedor borrado exitosamente\n";
                system("pause");
            }
            file >> id >> nombreAcreedor >> telefono >> numCuenta >> banco;
        }
        if(found==0) {
            cout<<"\nAcreedor no encontrado\n";
            system("pause");
        }
        file1.close();
        file.close();
        remove("acreedor.txt");
        rename("temporal.txt","acreedor.txt");
        bitacora auditoria;
        auditoria.insertar(usuariosrRegistrado.getNombre(), "8044", "DAR"); // Eliminar Acreedor de bitácora
    }
}

// Genera un reporte tabular con todos los acreedores y guarda una copia en reportes.txt
void acreedor::reporte(){
    system("cls");
    fstream file, reporteFile;
    int found = 0;

    cout<<"\n----------------------------- Reporte de Acreedores -----------------------------\n"<<endl;
    file.open("acreedor.txt", ios::in);
    reporteFile.open("reportes.txt", ios::app | ios::out); // nuevo archivo

    if (!file) {
        cout << "\n\t\t\tNo hay informacion ...\n";
        reporteFile << "No hay informacion en acreedor.txt\n\n";
    }
    else {
        cout << left << setw(15) << "ID" << setw(15) << "Nombre"  << setw(15) << "Telefono"
             << setw(15) << "Num. Cuenta" << setw(15) << "Banco" << endl;
        cout << "----------------------------------------------------------------------------------\n";

        reporteFile << "----------------------------- REPORTE DE ACREEDORES -----------------------------\n";
        reporteFile << left << setw(15) << "ID" << setw(15) << "Nombre"  << setw(15) << "Telefono"
                    << setw(15) << "Num. Cuenta" << setw(15) << "Banco" << "\n";
        reporteFile << "----------------------------------------------------------------------------------\n";

        file >> id >> nombreAcreedor >> telefono >> numCuenta >> banco;
        while (!file.eof()) {
            found++;
            cout << left << setw(15) << id << setw(15) << nombreAcreedor << setw(15)
                 << telefono << setw(15) << numCuenta << setw(15) << banco << endl;

            reporteFile << left << setw(15) << id << setw(15) << nombreAcreedor << setw(15)
                        << telefono << setw(15) << numCuenta << setw(15) << banco << "\n";

            file >> id >> nombreAcreedor >> telefono >> numCuenta >> banco;
        }

        reporteFile << "----------------------------------------------------------------------------------\n\n";

        if(found==0){
            cout<<"\n\t\t\tNo hay Acreedores registrados...\n";
            reporteFile << "No hay Acreedores registrados...\n\n";
        }
    }

    cout << endl;
    file.close();
    reporteFile.close();
    system("pause");
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8035", "RAR"); // Reporte Acreedor
}
