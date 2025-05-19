//Clase para mantenimiento de clientes
//Programado por Dulce Martìnez 02/05/25

//Actualizaciones y correcciiones
//Programado por Dulce Martìnez 11/05/25

#include "cliente.h"
#include "bitacora.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
#include "usuarios.h"

using namespace std;

extern usuarios usuariosrRegistrado;

void cliente::menu()
{
    int choice;
	char x;

	do
    {
	system("cls");

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\t |   SISTEMA GESTION CLIENTES |"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\t 1. Ingreso Clientes"<<endl;
	cout<<"\t\t\t 2. Despliegue Clientes"<<endl;
	cout<<"\t\t\t 3. Modifica Clientes"<<endl;
	cout<<"\t\t\t 4. Busca Clientes"<<endl;
	cout<<"\t\t\t 5. Borra Clientes"<<endl;
	cout<<"\t\t\t 6. Reportes Clientes" << endl;
	cout<<"\t\t\t 7. Salida"<<endl;

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\tOpcion a escoger:[1/2/3/4/5/6/7]"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
    cout<<"\t\t\tIngresa tu Opcion: ";
    cin>>choice;

    switch(choice)
    {
    case 1:
    	do
    	{
    		insertar();
    		cout<<"\n\t\t\t Agrega otro Clientes(Y,N): ";
    		cin>>x;
		}while(x=='y'||x=='Y');
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
  }while(choice!= 7);
}
void cliente::insertar()
{
	system("cls");
	fstream file;
	char confirmar; //Variable para guardar la respuesta de la confirmacion
	cout<<"\n------------------------------------------------------------------------------------------------------------------------";
	cout<<"\n-------------------------------------------------Agregar detalles Cliente ---------------------------------------------"<<endl;
	cout<<"\t\t\tIngresa Id Cliente         : ";
	cin>>id;
	cout<<"\t\t\tIngresa Nombre Cliente     : ";
	cin>>nombre;
	cout<<"\t\t\tIngresa Telefono Cliente   : ";
	cin>>telefono;
	cout<<"\t\t\tIngresa Nit Cliente   : ";
	cin>>nit;

	cout << "\n\t\t\t¿Deseas guardar los datos? (s/n): ";
    cin >> confirmar;

    if (confirmar == 's' || confirmar == 'S')

	file.open("cliente.txt", ios::app | ios::out);
	file<<left<<setw(15)<< id <<left<<setw(15)<< nombre <<left<<setw(15)<< telefono <<left<< setw(15) << nit <<"\n";
	file.close();

	// Guardar en reportes.txt
	ofstream reporteFile;
    reporteFile.open("reportesClientes.txt", ios::app | ios::out);
    reporteFile << left << setw(15) << id << left << setw(15) << nombre<< left << setw(15) << telefono << left << setw(15) << nit << "\n";
    reporteFile.close();

    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8011", "INS"); //ingreso a las bitácoras
}
void cliente::desplegar()
{
	system("cls");
	fstream file;
	int total=0;
	cout<<"\n-------------------------Tabla de Detalles de Cliente -------------------------"<<endl;
	file.open("cliente.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay informacion...";
		file.close();
	}
	else
	{
		file >> id >> nombre >> telefono >> nit;
		while(!file.eof())
		{
			total++;
			cout<<"\n\n\t\t\t Id Cliente: "<<id<<endl;
			cout<<"\t\t\t Nombre Cliente: "<<nombre<<endl;
            cout<<"\t\t\t Telefono Cliente: "<<telefono<<endl;
            cout<<"\t\t\t Nit Cliente: "<<nit<<endl;

			file >> id >> nombre >> telefono >>nit;
		}
		if(total==0)
		{
			cout<<"\n\t\t\tNo hay informacion...";
		}
		system("pause");
	}
	file.close();
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8011", "MC");//Muestra el cliente de la bitacora
}
void cliente::modificar()
{
	system("cls");
	fstream file,file1;
	string participant_id;
	int found=0;
	cout<<"\n-------------------------Modificacion Detalles Cliente-------------------------"<<endl;
	file.open("cliente.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay informacion..,";
		file.close();
	}
	else
	{
		cout<<"\n Ingrese Id del cliente que quiere modificar: ";
		cin>>participant_id;
		file1.open("temporal.txt",ios::app | ios::out); //Archivo para modificaciones
		file >> id >> nombre >> telefono >> nit;
		while(!file.eof())
		{
			if(participant_id!=id)
			{
			 file1<<left<<setw(15)<< id <<left<<setw(15)<< nombre <<left<<setw(15)<< telefono <<left<<setw(15)<< nit <<"\n";
			}
			else
			{
				cout<<"\t\t\tIngrese Id Cliente: ";
				cin>>id;
				cout<<"\t\t\tIngrese Nombre Cliente: ";
				cin>>nombre;
				cout<<"\t\t\tIngrese Telefono Cliente: ";
				cin>>telefono;
				cout<<"\t\t\tIngrese Nit Cliente: ";
				cin>>nit;
				file1<<left<<setw(15)<< id <<left<<setw(15)<< nombre <<left<<setw(15)<< telefono <<left<<setw(15)<< nit <<"\n";
				found++;
			}
			file >> id >> nombre >> telefono >> nit;

		}
		file1.close();
		file.close();
		remove("cliente.txt");
		rename("temporal.txt","cliente.txt");
        bitacora auditoria;
        auditoria.insertar(usuariosrRegistrado.getNombre(), "8011", "UPD"); //Actualizacion datos cliente
	}
}
void cliente::buscar()
{
	system("cls");
	fstream file;
	int found=0;
	file.open("cliente.txt",ios::in);
	if(!file)
	{
		cout<<"\n-------------------------Datos del Cliente Buscado------------------------"<<endl;
		cout<<"\n\t\t\tNo hay informacion...";
	}
	else
	{
		string participant_id;
		cout<<"\n-------------------------Datos del Cliente Buscado------------------------"<<endl;
		cout<<"\nIngrese Id del cliente que quiere buscar: ";
		cin>>participant_id;
		file >> id >> nombre >> telefono >> nit;
		while(!file.eof())
		{
			if(participant_id==id)
			{
				cout<<"\n\n\t\t\t Id Cliente: "<<id<<endl;
				cout<<"\t\t\t Nombre Cliente: "<<nombre<<endl;
				cout<<"\t\t\t Telefono Cliente: "<<telefono<<endl;
				cout<<"\t\t\t Nit Cliente: "<<nit<<endl;
				found++;
			}
			file >> id >> nombre >> telefono >> nit;
		}
		if(found==0)
		{
			cout<<"\n\t\t\t Persona no encontrada...";
		}
		file.close();
        bitacora auditoria;
        auditoria.insertar(usuariosrRegistrado.getNombre(), "8011", "BC"); //Busqueda cliente en bitacora
	}
}
void cliente::borrar()
{
	system("cls");
	fstream file,file1;
	string participant_id;
	int found=0;
	cout<<"\n-------------------------Detalles CLiente a Borrar-------------------------"<<endl;
	file.open("cliente.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay informacion...";
		file.close();
	}
	else
	{
		cout<<"\n Ingrese el Id del cliente que quiere borrar: ";
		cin>>participant_id;
		file1.open("temporal.txt",ios::app | ios::out);
		file >> id >> nombre >> telefono >> nit;
		while(!file.eof())
		{
			if(participant_id!= id)
			{
				file1<<left<<setw(15)<< id <<left<<setw(15)<< nombre <<left<<setw(15)<< telefono << left<<setw(15)<< nit <<"\n";
			}
			else
			{
				found++;
				cout << "\n\t\t\tBorrado de informacion exitoso";
			}
			file >> id >> nombre >> telefono >> nit;
		}
		if(found==0)
		{
			cout<<"\n\t\t\t Id Persona no encontrado...";
		}
		file1.close();
		file.close();
		remove("cliente.txt");
		rename("temporal.txt","cliente.txt");
        bitacora auditoria;
        auditoria.insertar(usuariosrRegistrado.getNombre(), "8011", "DEL"); //Eliminar cliente de bitacora
	}
}

void cliente::reporte(){
    system("cls");
    fstream file;
    int found = 0;

    cout << "\n----------------------------- Reporte de Clientes -----------------------------\n\n" << endl;
    file.open("cliente.txt", ios::in);

    if (!file) {
        cout << "\n\t\t\tNo hay información...\n";
    }
    else {
        // Encabezado del reporte
        cout << left << setw(15) << "ID" << setw(30) << "Nombre" << setw(15) << "Telefono"
             << setw(15) << "NIT" << endl;
        cout << "-------------------------------------------------------------------------------\n";

        // Leer datos del archivo
        while (file >> id) {
            // Usamos getline para leer nombres con espacios
            file.ignore();  // Ignorar el salto de línea después del ID
            getline(file, nombre);
            file >> telefono >> nit;

            found++;

            // Imprimir los datos del cliente
            cout << left << setw(15) << id << setw(30) << nombre << setw(15)
                 << telefono << setw(15) << nit << endl;
        }

        if (found == 0) {
            cout << "\n\t\t\tNo hay clientes registrados...\n";
        }
    }
    cout << endl;
    file.close();
    system("pause");

    // Guardar todos los clientes en el archivo de reporte
    ofstream reporteFile;
    reporteFile.open("reportesClientes.txt", ios::app);

    // Reabrimos el archivo para escribir todos los clientes
    file.open("cliente.txt", ios::in);
    while (file >> id) {
        file.ignore(); // Ignorar salto de línea después del ID
        getline(file, nombre);
        file >> telefono >> nit;

        // Escribir cada cliente en el reporte
        reporteFile << left << setw(15) << id << setw(30) << nombre
                    << setw(15) << telefono << setw(15) << nit << "\n";
    }
    reporteFile.close();

    // Bitácora
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8011", "RPC"); // Reporte Cliente
}
