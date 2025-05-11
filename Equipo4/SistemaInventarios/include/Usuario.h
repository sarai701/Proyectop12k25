#ifndef USUARIOS_H
#define USUARIOS_H
#include<iostream>

using std::string;

class usuarios
{
    public:
        usuarios();
        virtual ~usuarios();//DESTRUYE LA INFORMACION DEL OBJETO EN MEMORIA
        bool loginUsuarios();
        void menuUsuarios();
        bool buscar(string user, string passw);
        string getNombre();
        void setNombre(string nombre);//parametro por valor(IMPORTANTE)

    protected:

    private:
		string id;
		string name;
		string pass;

};

#endif // USUARIOS_H
