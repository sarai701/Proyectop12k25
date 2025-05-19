//Programado por Priscila Sarai Guzmán Calgua 9959-23-450
//Boris de León 9959-24-6203
#ifndef BITACORA_H
#define BITACORA_H

#include <string>

class Bitacora {
public:
    void insertar(const std::string& usuario, int codigo, const std::string& aplicacion, const std::string& accion);
    void mostrar();
    void menuBitacora(); // NUEVO MÉTODO
};

#endif
