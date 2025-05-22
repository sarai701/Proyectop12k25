//Boris de León 9959-24-6203
//Priscila Guzmán 9959-23-450
#ifndef BITACORA_H
#define BITACORA_H

#include <string>
using namespace std;
class Bitacora {
public:
    void insertar(const string& usuario, int codigo, const string& aplicacion, const string& accion);
    void mostrar();
    void menuBitacora();

private:
    // Estructura para almacenar un registro de bitácora en formato binario
struct RegistroBitacora {
    char usuario[30];
    int codigo;
    char aplicacion[30];
    char accion[50];
    char fechaHora[30];
};
};

#endif
