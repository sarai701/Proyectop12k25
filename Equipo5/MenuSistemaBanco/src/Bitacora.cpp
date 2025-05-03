#include "bitacora.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>

using namespace std;

void bitacora::menu()
{
    int choice;
	char x;
	do
    {
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
    }while(choice!= 2);
}
void bitacora::insertar(string nombre, string aplicacion, string accion)
{
	system("cls");
	fstream file;
	file.open("bitacora.txt", ios::app | ios::out);
	file<<std::left<<std::setw(15)<< nombre <<std::left<<std::setw(15)<< aplicacion <<std::left<<std::setw(15)<< accion << "\n";
	file.close();
}
void bitacora::desplegar()
{
	system("cls");
	fstream file;
	int total=0;
	cout<<"\n-------------------------Tabla de Detalles de Bitacora -------------------------"<<endl;
	file.open("bitacora.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay información...";
		file.close();
	}
	else
	{
		file >> nombre >> aplicacion >> accion;
		while(!file.eof())
		{
			total++;
			cout<<"\n\n\t\t\t Nombre Usuario: "<<nombre<<endl;
			cout<<"\t\t\t No. Aplicacion: "<<aplicacion<<endl;
            cout<<"\t\t\t Accion realizada: "<<accion<<endl;

			file >> nombre >> aplicacion >> accion;
		}
		if(total==0)
		{
			cout<<"\n\t\t\tNo hay informacion...";
		}
		system("pause");
	}
	file.close();
}
