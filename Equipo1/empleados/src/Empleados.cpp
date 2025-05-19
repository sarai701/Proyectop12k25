#include "Empleados.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
Empleados::Empleados()
{
}
void Empleados::menu()
{
    int eleccion =0;
    char x;
    do
    {
    system("cls");
    cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\t |   Registro de empleados  |"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\t 1. Ingreso de Empleados"<<endl;
	cout<<"\t\t\t 2. Despliegue de Empleados"<<endl;
	cout<<"\t\t\t 3. Modificar Empleados"<<endl;
	cout<<"\t\t\t 4. Borrar Empleados"<<endl;
    cout<<"\t\t\t 5. salida"<<endl;

	cout<<"Presione el numero para el caso \n";
	cin>>eleccion;
        switch(eleccion)
        {
        case 1:
            cout<<"Opcion escogida... \n";
            registro();
            cout<<"Hay mas empleados por anadir? Y/N \n";
            cin>>x;
            while (x=='y'||x=='Y')
            {
                registro();
            }
        break;
        case 2:
            cout<<"Opcion escogida...\n";
            lista();
        break;
        case 3:
            cout<<"Opcion escogida \n";
            cambio();
            break;
        case 4:
            cout<<"Opcion escogida \n";
            borrar();
            break;
        case 5:
            exit(0);
            break;
        default:
            cout<<"Opcion no valida"<<endl;
            break;

        }
        getch();
    }
    while(eleccion !=5);
}
void Empleados::registro()
{
    //Llamada de fstream
    system("cls");
	fstream file;
	cout<<"\n-------------------------------------------------Agregar detalles Persona ---------------------------------------------"<<endl;
	//Ingreso de datos
	cout<<"\t\t\tIngresa el tipo de empleado (contrato o sueldo)    : ";
	cin>>tipoEmpleado;
	cout<<"\t\t\tIngresa Nombre: ";
	getline(cin, Nombre);
	cout<<"\t\t\tIngresa Sueldo de empleado : Q";
	cin>>sueldo;
	//Crear un archivo y añadir la informacion
	file.open("Usuarios.txt", ios::app | ios::out);
	//Insertado de datos
	file<<std::left<<std::setw(15)<< tipoEmpleado <<std::left<<std::setw(15)<< Nombre <<std::left<<std::setw(15)<< sueldo << "\n";
	file.close();
}
void Empleados::lista()
{
  system("cls");
  //Llamada de fstream
	fstream file;
	//Variable para revisar linea por linea
	int total=0;
	cout<<"\Empleados"<<endl;
	//Se llama el mismo txt
	file.open("Usuarios.txt",ios::in);
	//Si no existe el txt, retorna debido a que no hay informacion
	if(!file)
	{
		cout<<"\n\t\t\tNo hay información...";
		file.close();
	}
	else
	{
	    //Se revisa linea por linea
		file >> tipoEmpleado >> Nombre >> sueldo;
		//hasta el fin del archivo
		while(!file.eof())
		{
		    //se incrementa el total cuando hay lineas que tengan contenido
			total++;
			//se imprimen los datos del empleado
			cout<<"\n\n\t\t\t Tipo de empleado: "<<tipoEmpleado<<endl;
			cout<<"\t\t\t Nombre del empleado: "<<Nombre<<endl;
			cout<<"\t\t\t Paga del empleado: "<<sueldo<<endl;
			file >> tipoEmpleado >> Nombre >> sueldo;
		}
		if(total==0)
		{
			cout<<"\n\t\t\tNo hay informacion...";
		}
	}
	file.close();
}
void Empleados::cambio()
{
    //Clean de la consola
	system("cls");
	//Llamada de fstream a dos archivos
	fstream file,file1;
	//Busqueda
	string tipoEmpleadoCambio,NombreCambio;
	double sueldoCambio;
	int found=0;
	cout<<"\n-------------------------Cambios laborales (no despidos)-------------------------"<<endl;
	//Abrir el primer archivo
	file.open("Usuarios.txt",ios::in);
	//Validacion del archivo
	if(!file)
	{
		cout<<"\n\t\t\tNo hay informacion..,";
		file.close();
	}
	//Ingreso del cambio
	else
	{
	    //Validaciones del cambio
		cout<<"\n Ingrese El tipo de empleado que quiere modificar: ";
		cin>>tipoEmpleadoCambio;
		cout<<"\n Ingrese el nombre de la persona a modificar: ";
		cin>>NombreCambio;
		cout<<"\n Ingrese el sueldo de la persona a modificar";
		cin>>sueldoCambio;
		//Cambio del registro en otro archivo txt nuevo
		file1.open("Record.txt",ios::app | ios::out);
		file >> tipoEmpleado >> Nombre >> sueldo;
		//revision hasta el fin del archivo
		while(!file.eof())
		{
		    //si no hay cambios entonces se deja asi
			if(tipoEmpleadoCambio!=tipoEmpleado && NombreCambio!=Nombre && sueldoCambio!=sueldo)
			{
			 file1<<std::left<<std::setw(15)<< tipoEmpleado <<std::left<<std::setw(15)<< Nombre <<std::left<<std::setw(15)<< sueldo << "\n";
			}
			else
			{
				cout<<"\t\t\tIngrese tipo de empleado: ";
				cin>>tipoEmpleado;
				cout<<"\t\t\tIngrese Nombre Persona: ";
				cin>>Nombre;
				cout<<"\t\t\tIngrese Sueldo: ";
				cin>>sueldo;
				file1<<std::left<<std::setw(15)<< tipoEmpleado <<std::left<<std::setw(15)<< Nombre <<std::left<<std::setw(15)<< sueldo << "\n";
				found++;
			}
			file >> tipoEmpleado >> Nombre >> sueldo;

		}
		file1.close();
		file.close();
		remove("Usuarios.txt");
		rename("Record.txt","Usuarios.txt");
	}
}
void Empleados::borrar()
{
	system("cls");
	//Llamada a fstream de 2 archivos
	fstream file,file1;
	string CambioNombreBorrar = "";
	//variable de busqueda
	int found=0;
	cout<<"\n-------------------------Detalles Persona a Borrar-------------------------"<<endl;
	//Abrir archivo  y verificar su existencia
	file.open("Usuarios.txt",ios::in);
	if(!file)
	{
		cout<<"\n\t\t\tNo hay informacion...";
		file.close();
	}
	//Si existe el archivo entonces se modifica en base al nombre
	else
	{
		cout<<"\n Ingrese el nombre de la Persona que quiere borrar: ";
		cin>>CambioNombreBorrar;
		//Llamada a una bitacora
		file1.open("Record.txt",ios::app | ios::out);
		file >> tipoEmpleado >> Nombre >> sueldo;
		//Revisar hasta el fin del archivo
		while(!file.eof())
		{
		    //Si el nombre es diferente entonces se ignora y se copia
			if(CambioNombreBorrar!= Nombre)
			{
				file1<<std::left<<std::setw(15)<< tipoEmpleado <<std::left<<std::setw(15)<< Nombre <<std::left<<std::setw(15)<< sueldo << "\n";
			}
			//Si el nombre es igual entonces se borra
			else
			{
				found++;
				cout << "\n\t\t\tBorrado de informacion exitoso";
			}
			file >> tipoEmpleado >> Nombre >> sueldo;
		}
		//Validacion acerca de no encontrar a la persona estipulada
		if(found==0)
		{
			cout<<"\n\t\t\t Id Persona no encontrado...";
		}
		//Cerrar los archivos
		file1.close();
		file.close();
		//Borra usuarios y manda todo a Record y otro Usuarios
		remove("Usuarios.txt");
		rename("Record.txt","Usuarios.txt");
	}
}
