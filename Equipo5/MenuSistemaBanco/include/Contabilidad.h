//Jonathan Samuel GOnzalez Ixpata
#ifndef CONTABILIDAD_H
#define CONTABILIDAD_H

#include <iostream>
#include <fstream>
#include <string>
#include "Bitacora.h"

class Contabilidad {
public:
    void menuContabilidad();               // Menú principal
    void registroNomina();                 // Opción 1: Registrar pago
    void desplegarRegistroSalarios();      // Opción 2: Generar salarios.txt
    void limpiarPantalla();                // Limpiar pantalla
    void pausar();                         // Pausar ejecución
};

#endif
