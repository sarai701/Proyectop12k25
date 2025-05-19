//Clase para mantenimiento de Proveedores
//Programado por Britany Hernandez 04/05/25

//Actualizacion y correcciones
//Programado por Britany Hernandez 11/05/25
//Modificación para uso de archivos binarios 18/05/25

#include "proveedor.h"
#include "bitacora.h"
#include "usuarios.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<conio.h>
#include<iomanip>

using namespace std;

extern usuarios usuariosrRegistrado; //Objeto usuario declarado en el main

void proveedor::menu()
{
    int choice;
    char x;
    do {
        system("cls");
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\t |   SISTEMA GESTION PROVEEDORES |"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\t 1. Ingreso Proveedores"<<endl;
        cout<<"\t\t\t 2. Despliegue Proveedores"<<endl;
        cout<<"\t\t\t 3. Modifica Proveedores"<<endl;
        cout<<"\t\t\t 4. Busca Proveedores"<<endl;
        cout<<"\t\t\t 5. Borra Proveedores"<<endl;
        cout<<"\t\t\t 6. Reporte Proveedores"<<endl;
        cout<<"\t\t\t 7. Salida"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\tOpcion a escoger:[1/2/3/4/5/6/7]"<<endl;
        cout<<"\t\t\tIngresa tu Opcion: ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            do {
                insertar();
                cout<<"\n\t\t\t Agrega otro Proveedor (Y/N): ";
                cin>>x;
            } while(x=='y'||x=='Y');
            break;
        case 2:
            desplegar();
            break;
        case 3:
            modificar();
            break;
        case 4:
            buscar();
            break;
        case 5:
            borrar();
            break;
        case 6:
            reporte();
            break;
        case 7:
            break;
        default:
		cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
            cin.get();
        }
    } while(choice!= 6);
}

void proveedor::insertar()
{
    system("cls");
    fstream file;
    char guardar; //Variable para guardar la respuesta de la confirmacion

    cout<<"\n-----------------------------------------------------------------------------------";
    cout<<"\n-------------------------------- Agregar Proveedor --------------------------------"<<endl;
    cout << "\t\t\tIngresa ID Proveedor         : ";
    cin >> id;
    cout << "\t\t\tIngresa Nombre Proveedor     : ";
    cin >> nombreProveedor;
    cout << "\t\t\tIngresa Telefono Proveedor   : ";
    cin >> telefono;
    cout << "\t\t\tIngresa Num.Cuenta Proveedor : ";
    cin >> numCuenta;
    cout << "\t\t\tIngresa Banco del Proveedor  : ";
    cin >> banco;

    cout << "\n\t\t\t¿Deseas guardar los datos? (s/n): ";
    cin >> guardar;

    if(guardar=='s' || guardar=='S'){
        // Guardar en archivo binario principal
        file.open("proveedor.bin", ios::binary | ios::app | ios::out);
        file.write((char*)this, sizeof(proveedor));
        file.close();

        // Guardar en reporte (opcional, puede mantenerse como texto)
        ofstream reporteFile;
        reporteFile.open("reportesProveedores.txt", ios::app);
        reporteFile << left << setw(15) << id << left << setw(15) << nombreProveedor
                    << left << setw(15) << telefono << left << setw(15) << numCuenta
                    << left << setw(15) << banco << "\n";
        reporteFile.close();

        bitacora auditoria;
        auditoria.insertar(usuariosrRegistrado.getNombre(), "8030", "INP");

        cout << "\n\t\t\t Proveedor registrado exitosamente!" << endl;
    }
    else {
        cout << "\n\t\t\t Ingreso cancelado..." << endl;
    }
    system("pause");
}

void proveedor::desplegar()
{
    system("cls");
    ifstream file;
    int total=0;
    cout<<"\n------------------------ Lista de Proveedores ------------------------"<<endl;
    file.open("proveedor.bin", ios::binary | ios::in);
    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...\n";
        system("pause");
    }
    else {
        while(file.read((char*)this, sizeof(proveedor))) {
            total++;
            cout<<"\n\t\t\t ID proveedor        : "<<id;
            cout<<"\n\t\t\t Nombre proveedor    : "<<nombreProveedor;
            cout<<"\n\t\t\t Telefono proveedor  : "<<telefono;
            cout<<"\n\t\t\t Banco proveedor     : "<<banco;
            cout<<"\n\t\t\t Num.Cuenta proveedor: "<<numCuenta<<endl;
        }
        if(total==0){
            cout<<"\n\t\t\tNo hay informacion...";
        }
        system("pause");
    }
    file.close();
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8031", "MP");
}


void proveedor::modificar()
{
    system("cls");
    fstream file, tempFile;
    string proveedor_id;
    int found=0;
    cout<<"\n---------------- Modificar Proveedor ----------------"<<endl;
    file.open("proveedor.bin", ios::binary | ios::in);
    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...";
        system("pause");
        file.close();
    }
    else {
        cout<<"\nIngrese ID del proveedor que quiere modificar: ";
        cin>>proveedor_id;
        tempFile.open("temporal.bin", ios::binary | ios::out);

        while(file.read((char*)this, sizeof(proveedor))) {
            if(proveedor_id != id) {
                tempFile.write((char*)this, sizeof(proveedor));
            }
            else {
                cout<<"\t\t\tIngrese Id proveedor        : ";
                cin>>id;
                cout<<"\t\t\tIngrese Nombre proveedor    : ";
                cin>>nombreProveedor;
                cout<<"\t\t\tIngrese Telefono proveedor  : ";
                cin>>telefono;
                cout<<"\t\t\tIngrese Num.Cuenta proveedor: ";
                cin>>numCuenta;
                cout<<"\t\t\tIngrese Banco proveedor     : ";
                cin>>banco;

                tempFile.write((char*)this, sizeof(proveedor));
                found++;
            }
        }

        file.close();
        tempFile.close();
        remove("proveedor.bin");
        rename("temporal.bin", "proveedor.bin");

        if(found==0){
            cout<<"\n\t\t\tProveedor no encontrado...";
        }
        else {
            cout<<"\n\t\t\tProveedor modificado exitosamente!";
        }
        system("pause");
        bitacora auditoria;
        auditoria.insertar(usuariosrRegistrado.getNombre(), "8032", "UPD");
    }
}

void proveedor::buscar()
{
    system("cls");
    ifstream file;
    int found=0;

    cout<<"\n---------------- Buscar Proveedor ----------------"<<endl;
    file.open("proveedor.bin", ios::binary | ios::in);
    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...";
    }
    else {
        string proveedor_id;
        cout<<"\nIngrese ID del proveedor que quiere buscar : ";
        cin>>proveedor_id;

        while(file.read((char*)this, sizeof(proveedor))) {
            if(proveedor_id==id) {
                cout<<"\n\t\t\t ID Proveedor        : "<<id<<endl;
                cout<<"\t\t\t Nombre Proveedor    : "<<nombreProveedor<<endl;
                cout<<"\t\t\t Telefono Proveedor  : "<<telefono<<endl;
                cout<<"\t\t\t Num.Cuenta Proveedor: "<<numCuenta<<endl;
                cout<<"\t\t\t Banco Proveedor     : "<<banco<<endl;
                found++;
                break;
            }
        }

        if(found==0){
            cout<<"\nProveedor no encontrado...\n";
        }
        file.close();
        system("pause");
    }
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8033", "BPR");
}

void proveedor::borrar()
{
    system("cls");
    fstream file, tempFile;
    string proveedor_id;
    int found=0;
    cout<<"\n---------------- Borrar Proveedor ----------------"<<endl;
    file.open("proveedor.bin", ios::binary | ios::in);

    if(!file)
    {
        cout<<"\n\t\t\tNo hay informacion...";
    }
    else
    {
        cout<<"\n Ingrese el Id del Proveedor que quiere borrar: ";
        cin>>proveedor_id;
        tempFile.open("temporal.bin", ios::binary | ios::out);

        while(file.read((char*)this, sizeof(proveedor))) {
            if(proveedor_id != id) {
                tempFile.write((char*)this, sizeof(proveedor));
            }
            else {
                found++;
                cout << "\nProveedor borrado exitosamente\n";
            }
        }

        file.close();
        tempFile.close();
        remove("proveedor.bin");
        rename("temporal.bin","proveedor.bin");

        if(found==0)
        {
            cout<<"\nProveedor no encontrado\n";
        }
        system("pause");
        bitacora auditoria;
        auditoria.insertar(usuariosrRegistrado.getNombre(), "8034", "DPR");
    }
}

void proveedor::reporte(){
    system("cls");
    fstream file;
    int found = 0;

    cout<<"\n----------------------------- Reporte de Proveedores -----------------------------\n\n"<<endl;
    file.open("proveedor.dat", ios::in | ios::binary);

    if (!file) {
        cout << "\n\t\t\tNo hay informacion ...\n";
    }
    else{
        cout << left << setw(15) << "ID" << setw(15) << "Nombre"  << setw(15) << "Telefono"
        << setw(15) << "Num. Cuenta" << setw(15) << "Banco" << endl;

        cout << "------------------------------------------------------------------------------\n";

        file >> id >> nombreProveedor >> telefono >> numCuenta >> banco;
        while (!file.eof()){
            found++;
            cout << left << setw(15) << id << setw(15) << nombreProveedor  << setw(15)
            << telefono << setw(15) << numCuenta << setw(15) << banco << endl;

            file >> id >> nombreProveedor >> telefono >> numCuenta >> banco;
        }

        if(found==0){
            cout<<"\n\t\t\tNo hay proveedores registrados...\n";
        }
    }
    cout << endl;
    file.close();
    system("pause");

    ofstream reporteFile;
        file.open("reportesProveedores.dat", ios::app | ios::out | ios::binary);
        file<<left<<setw(15)<< id <<left<<setw(15)<< nombreProveedor <<left<<setw(15)<<telefono <<left << setw(15)<< numCuenta <<left << setw(15) << banco << "\n";
        file.close();

    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8035", "RPR"); // Reporte Proveedor
}
