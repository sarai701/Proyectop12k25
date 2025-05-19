//Clase para mantenimiento de Proveedores
//Programado por Britany Hernandez 04/05/25

//Actualizacion y correcciones
//Programado por Britany Hernandez 11/05/25

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
        file.open("proveedor.txt", ios::app | ios::out);
        file<<left<<setw(15)<< id <<left<<setw(15)<< nombreProveedor <<left<<setw(15)<<telefono <<left << setw(15)<< numCuenta <<left << setw(15) << banco << "\n";
        file.close();

        ofstream reporteFile;
        file.open("reportesProveedores.txt", ios::app | ios::out);
        file<<left<<setw(15)<< id <<left<<setw(15)<< nombreProveedor <<left<<setw(15)<<telefono <<left << setw(15)<< numCuenta <<left << setw(15) << banco << "\n";
        file.close();

        bitacora auditoria;
        auditoria.insertar(usuariosrRegistrado.getNombre(), "8030", "INP"); //Ingreso a la bitacoras

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
    fstream file;
    int total=0;
    cout<<"\n------------------------ Lista de Proveedores ------------------------"<<endl;
    file.open("proveedor.txt", ios::in);
    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...\n";
        system("pause");
    }
    else {
        file >> id >> nombreProveedor >> telefono >> numCuenta>> banco ;
        while(!file.eof()) {
            total++;
            cout<<"\n\t\t\t ID proveedor        : "<<id;
            cout<<"\n\t\t\t Nombre proveedor    : "<<nombreProveedor;
            cout<<"\n\t\t\t Telefono proveedor  : "<<telefono;
            cout<<"\n\t\t\t Banco proveedor     : "<<banco;
            cout<<"\n\t\t\t Num.Cuenta proveedor: "<<numCuenta<<endl;

            file >> id >> nombreProveedor >> telefono >> numCuenta >> banco ;
        }
        if(total==0){
            cout<<"\n\t\t\tNo hay informacion...";
            system("pause");
        }
		system("pause");
		}
    file.close();
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8031", "MP"); //Mostrar Proveedor
}

void proveedor::modificar()
{
    system("cls");
    fstream file, file1;
    string proveedor_id;
    int found=0;
    cout<<"\n---------------- Modificar Proveedor ----------------"<<endl;
    file.open("proveedor.txt", ios::in);
    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...";
        system("pause");
        file.close();
    }
    else {
        cout<<"\nIngrese ID del proveedor que quiere modificar: ";
        cin>>proveedor_id;
        file1.open("temporal.txt", ios::app | ios::out);
        file >> id >> nombreProveedor >> telefono >> numCuenta>> banco ;

        while(!file.eof())
        {
            if(proveedor_id != id) {
                file1<<left<<setw(15)<< id <<left<<setw(15)<< nombreProveedor <<left<<setw(15)<< telefono <<
                left << setw(15)<< numCuenta <<left << setw(15) << banco << "\n";
            }
        else {
                cout<<"\t\t\tIngrese Id proveedor        : ";
				cin>>id;
				cout<<"\t\t\tIngrese Nombre proveedor    : ";
				cin>>nombreProveedor;
				cout<<"\t\t\tIngrese Telefono proveedor  : ";
				cin>>telefono;
				cout<<"\t\t\tIngrese Num.Cuenta proveedor: ";
				cin >>numCuenta;
				cout<<"\t\t\tIngrese Banco proveedor     : ";
				cin>>banco;


                file1<<left<<setw(15)<< id <<left<<setw(15)<< nombreProveedor <<left<<setw(15)<< telefono <<
                left << setw(15)<< numCuenta  <<left << setw(15) << banco << "\n";
                found++;
            }
            file >> id >> nombreProveedor >> telefono >> numCuenta >> banco;
        }
        if(found==0){
            cout<<"\n\t\t\tProveedor no encontrado...";
            system("pause");
        }

        file1.close();
        file.close();
        remove("proveedor.txt");
        rename("temporal.txt","proveedor.txt");
        bitacora auditoria;
        auditoria.insertar(usuariosrRegistrado.getNombre(), "8032", "UPD");
    }
}

void proveedor::buscar()
{
    system("cls");
    fstream file;
    int found=0;


    file.open("proveedor.txt", ios::in);
    cout<<"\n---------------- Buscar Proveedor ----------------"<<endl;
    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...";
        file.close();

    } else {
        string proveedor_id;
        cout<<"\nIngrese ID del proveedor que quiere buscar : ";
        cin>>proveedor_id;
        file >> id >> nombreProveedor >> telefono >> numCuenta >> banco;

        while(!file.eof()) {
            if(proveedor_id==id) {
                cout<<"\n\t\t\t ID Proveedor        : "<<id<<endl;
                cout<<"\t\t\t Nombre Proveedor    : "<<nombreProveedor<<endl;
                cout<<"\t\t\t Telefono Proveedor  : "<<telefono<<endl;
                cout<<"\t\t\t Num.Cuenta Proveedor: "<<numCuenta<<endl;
                cout<<"\t\t\t Banco Proveedor     : "<<banco<<endl;
                found++;
                system("pause");
            }
            file >> id >> nombreProveedor >> telefono >> numCuenta >> banco ;

        }

        if(found==0){
            cout<<"\nProveedor no encontrado...\n";
            system("pause");
        }
        file.close();
    }
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8033", "BPR");
}

void proveedor::borrar()
{
    system("cls");
    fstream file, file1;
    string proveedor_id;
    int found=0;
    cout<<"\n---------------- Borrar Proveedor ----------------"<<endl;
    file.open("proveedor.txt", ios::in);

	if(!file)
	{
		cout<<"\n\t\t\tNo hay informacion...";
		system("pause");
		file.close();
	}
	else
	{
		cout<<"\n Ingrese el Id del Proveedor que quiere borrar: ";
		cin>>proveedor_id;
		file1.open("temporal.txt",ios::app | ios::out);
		file >> id >> nombreProveedor >> telefono >> numCuenta >> banco;
		while(!file.eof())
		{
			if(proveedor_id!= id)
			{
				file1<<left<<setw(15)<< id <<left<<setw(15)<< nombreProveedor <<left<<setw(15)<< telefono <<
                left << setw(15)<< numCuenta <<left << setw(15) << banco << "\n";
			}
			else
			{
				found++;
				cout << "\nProveedor borrado exitosamente\n";
				system("pause");
			}
			file >> id >> nombreProveedor >> telefono >> numCuenta >> banco;
		}
		if(found==0)
		{
			cout<<"\nProveedor no encontrado\n";
			system("pause");
		}
		file1.close();
		file.close();
		remove("proveedor.txt");
		rename("temporal.txt","proveedor.txt");
        bitacora auditoria;
        auditoria.insertar(usuariosrRegistrado.getNombre(), "8034", "DPR"); //Eliminar preedor de bitacora
	}
}

void proveedor::reporte(){
    system("cls");
    fstream file;
    int found = 0;

    cout<<"\n----------------------------- Reporte de Proveedores -----------------------------\n\n"<<endl;
    file.open("proveedor.txt", ios::in);

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
        file.open("reportesProveedores.txt", ios::app | ios::out);
        file<<left<<setw(15)<< id <<left<<setw(15)<< nombreProveedor <<left<<setw(15)<<telefono <<left << setw(15)<< numCuenta <<left << setw(15) << banco << "\n";
        file.close();

    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8035", "RPR"); // Reporte Proveedor
}
