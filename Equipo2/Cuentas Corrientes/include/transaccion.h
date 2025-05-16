//Clase transacción - Astrid Ruíz 9959242976
#ifndef TRANSACCION_H
#define TRANSACCION_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class transaccion {
private:
    string idTransaccion; //aquí voy a definir yo el ID
    string tipo; //aquí para definir los datos d las transacciones a realizar
    double monto;
    string fecha;
    string banco;

public:
    transaccion();
    transaccion(string id, string tipo, double monto, string fecha, string banco);

    //Funciones
    static string generarNuevoID(); //para generar el nuevo id
    void registrarTransaccion(string tipoOperacion);
    void mostrarTransaccion() const;
    void guardarEnArchivo() const;
    static void mostrarTodasDesdeArchivo();
    static void editarTransaccion(string id);
    static void eliminarTransaccion(string id);
};

#endif
