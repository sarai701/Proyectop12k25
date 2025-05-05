#ifndef BITACORA_H
#define BITACORA_H

#include <string>

class Bitacora {
public:
    static void registrarEvento(const std::string& usuario, const std::string& accion);
};

#endif // BITACORA_H
