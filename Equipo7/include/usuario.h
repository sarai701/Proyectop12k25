#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
public:
    std::string username;
    std::string password;

    Usuario(std::string u, std::string p);
};

#endif // USUARIO_H
