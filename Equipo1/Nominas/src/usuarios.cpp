#include "usuarios.h"
#include<fstream>
#include<cstdlib>
#include<conio.h>
#include<bitacora.h>
#include<iostream>

using namespace std;


usuarios::usuarios(string nombre, string contrasenia)
{
    this->nombre = nombre;
    this->contrasenia = contrasenia;
}

usuarios::~usuarios()
{
    //dtor
}
string usuarios::getNombre() //Metodo para obtener nombre-ANGEL ROQUEL
{
    return nombre;
}

string usuarios::getContrasenia() //Metodo para obtener contrasenia-ANGEL ROQUEL
{
    return contrasenia;
}

bool usuarios::verificarContrasenia(string contrasenia)//Metodo para verificar si contraseña es verdadera o falsa-ANGEL ROQUEL
 {
    return this->contrasenia == contrasenia;
}
