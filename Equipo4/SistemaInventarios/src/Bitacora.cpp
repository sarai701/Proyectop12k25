#include "Bitacora.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>

#include <ctime>
//bitacaora es un histórico
//Ferdynand Monroy 9959-24-14049 Mayo 2025

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
            if (line.length() >= 4)
            {
                int cod = stoi(line.substr(0, 4));
                if (cod > ultimoCodigo)
                    ultimoCodigo = cod;
            }
        }
    }
    readFile.close();

    int nuevoCodigo = ultimoCodigo + 1;
    if (nuevoCodigo > 2999) //aqui se encuentra el tope asignado en clase para nuestro programa
    {
        cout << "❌ Límite de bitácoras alcanzado (2999)" << endl;
        return;
    }

    file.open("bitacora.txt", ios::app | ios::out);

    time_t now = time(0);
    char* dt = ctime(&now);
    dt[strcspn(dt, "\n")] = 0;

    struct tm * timeinfo;
    timeinfo = localtime(&now);
    char timeBuffer[9];
    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", timeinfo);

    file << std::setw(4) << std::setfill('0') << nuevoCodigo << " "
         << std::left << std::setw(15) << nombre
         << std::left << std::setw(15) << aplicacion
         << std::left << std::setw(15) << accion
         << std::left << std::setw(25) << dt
         << std::left << std::setw(10) << timeBuffer << "\n";

    file.close();
}


void bitacora::desplegar()
{
	system("cls");
	fstream file;
	string linea;
	int total = 0;

	cout<<"\n-------------------------Tabla de Detalles de Bitacora -------------------------"<<endl;
	file.open("bitacora.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay información...";
	}
	else
	{
		while (getline(file, linea))
		{
			if (linea.length() > 0)
			{
				string codigo = linea.substr(0, 4);
				string nombre = linea.substr(5, 15);
				string aplicacion = linea.substr(21, 15);
				string accion = linea.substr(37, 15);
				string fecha = linea.substr(53);

				cout<<"\n\t\t\t Codigo Bitacora: " << codigo << endl;
				cout<<"\t\t\t Nombre Usuario:  " << nombre << endl;
				cout<<"\t\t\t Aplicacion:      " << aplicacion << endl;
				cout<<"\t\t\t Accion:          " << accion << endl;
				cout<<"\t\t\t Fecha y Hora:    " << fecha << endl;
				cout<<"-------------------------------------------------------------------------------\n";

				total++;
			}
		}
		if(total == 0)
		{
			cout<<"\n\t\t\tNo hay informacion...";
		}
	}
	file.close();
	system("pause");
}



