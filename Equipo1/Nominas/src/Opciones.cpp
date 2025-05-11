#include "Opciones.h"
#include "bitacora.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
#include "usuarios.h"

using namespace std;
bitacora Bitacora;

void Opciones::menu()//Metodo de despliegue del menu-ANGEL ROQUEL
{
    int opciones;
    bool repetir = true;
    do
    {
        system("cls");
        cout<<"\n\n\t\tNominas"<<endl;
        cout<<"\t --------------------"<<endl;
        cout<<"\t 1. Calcular devengos: "<<endl;
        cout<<"\t 2. Calcular deducciones: "<<endl;
        cout<<"\t 3. Calcular impuesto ISR (Impuesto sobre la renta): "<<endl;
        cout<<"\t 4. Calcular cuotas patronales: "<<endl;
        cout<<"\t 5. Calcular nomina: "<<endl;
        cout<<"\t 6. Periodo de liquidacion: "<<endl;
        cout<<"\t 7. Percepciones: "<<endl;
        cout<<"\t 8. Bases de liquidacion: "<<endl;
        cout<<"\t 9. Bitacoras "<<endl<<endl;
        cout<<"\t 10. Salir del menu: "<<endl<<endl;
        cin>>opciones;
        switch (opciones)
        {
        case 1:
            {

            }
            break;
        case 2:
            {

            }
            break;
        case 3:
            {

            }
            break;
        case 4:
            {

            }
            break;
        case 5:
            {

            }
            break;
        case 6:
            {

            }
            break;
        case 7:
            {

            }
            break;
        case 8:
            {

            }
            break;
        case 9:
            {
             Bitacora.menu();//Se llama al metodo del objeto bitacora para abrir el menu de la bitacora
            }
            break;
        case 10:
            {
            repetir=false;
            }
            break;
	default:
		cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
	}
    }while(repetir);
}
void Opciones::insertar()
{
	system("cls");
	fstream file;
	cout<<"\n------------------------------------------------------------------------------------------------------------------------";
	cout<<"\n-------------------------------------------------Agregar detalles Aplicacion ---------------------------------------------"<<endl;
	cout<<"\t\t\tIngresa Id Aplicacion         : ";
	cin>>id;
	cout<<"\t\t\tIngresa Nombre Aplicacion     : ";
	cin>>nombre;
	cout<<"\t\t\tIngresa estatus Aplicacion   : ";
	cin>>estatus;

	file.open("aplicaciones.txt", ios::app | ios::out);
	file<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< nombre <<std::left<<std::setw(15)<< estatus << "\n";
	file.close();
	bitacora auditoria;
	auditoria.insertar("usuario registrado", "801", "INS");
}
void Opciones::desplegar()
{
	system("cls");
	fstream file;
	int total=0;
	cout<<"\n-------------------------Tabla de Detalles de aplicaciones -------------------------"<<endl;
	file.open("aplicaciones.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay información...";
		file.close();
	}
	else
	{
		file >> id >> nombre >> estatus;
		while(!file.eof())
		{
			total++;
			cout<<"\n\n\t\t\t Id Aplicacion: "<<id<<endl;
			cout<<"\t\t\t Nombre Aplicacion: "<<nombre<<endl;
            cout<<"\t\t\t estatus Aplicacion: "<<estatus<<endl;

			file >> id >> nombre >> estatus;
		}
		if(total==0)
		{
			cout<<"\n\t\t\tNo hay informacion...";
		}
		system("pause");
	}
	file.close();
    bitacora auditoria;
    auditoria.insertar("usuario registrado", "801", "SEL");
}
void Opciones::modificar()
{
	system("cls");
	fstream file,file1;
	string participant_id;
	int found=0;
	cout<<"\n-------------------------Modificacion Detalles Aplicacion-------------------------"<<endl;
	file.open("aplicaciones.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay informacion..,";
		file.close();
	}
	else
	{
		cout<<"\n Ingrese Id del Aplicacion que quiere modificar: ";
		cin>>participant_id;
		file1.open("temporal.txt",ios::app | ios::out);
		file >> id >> nombre >> estatus;
		while(!file.eof())
		{
			if(participant_id!=id)
			{
			 file1<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< nombre <<std::left<<std::setw(15)<< estatus << "\n";
			}
			else
			{
				cout<<"\t\t\tIngrese Id Aplicacion: ";
				cin>>id;
				cout<<"\t\t\tIngrese Nombre Aplicacion: ";
				cin>>nombre;
				cout<<"\t\t\tIngrese estatus Aplicacion: ";
				cin>>estatus;
				file1<<std::left<<std::setw(15)<< id <<std::left<<std::setw(15)<< nombre <<std::left<<std::setw(15)<< estatus << "\n";
				found++;
			}
			file >> id >> nombre >> estatus;

		}
		file1.close();
		file.close();
		remove("aplicaciones.txt");
		rename("temporal.txt","aplicaciones.txt");
        bitacora auditoria;
        auditoria.insertar("usuario registrado", "801", "UPD");
	}
}
