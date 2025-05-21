//Boris de León 9959-24-6203
#ifndef BITACORA_H
#define BITACORA_H

#include <string>
using namespace std;
class Bitacora {
public:
    void insertar(const string& usuario, int codigo, const string& aplicacion, const string& accion);
    void mostrar();
    void menuBitacora();
};

#endif
