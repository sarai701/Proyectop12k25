#include "ui.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <conio.h> // Para _getch() en Windows
#include <windows.h> // Para Sleep()
#include <cstdlib> // Para exit()

UserInterface::UserInterface(AuthSystem& a, CompraManager& c) : auth(a), compras(c) {}

std::string UserInterface::getHiddenInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    char ch;

    while ((ch = _getch()) != '\r') { // Hasta presionar Enter
        if (ch == '\b') { // Manejar backspace
            if (!input.empty()) {
                std::cout << "\b \b";
                input.pop_back();
            }
        } else {
            std::cout << '*';
            input.push_back(ch);
        }
    }
    std::cout << std::endl;
    return input;
}

void UserInterface::run() {
    compras.cargarDatos(); // Carga datos de compras al inicio

    while (true) {
        if (auth.isLoggedIn()) {
            showPurchaseMenu();
        } else {
            showAuthMenu();
        }
    }
}

void UserInterface::showAuthMenu() {
    int opcion = 0;
    while (true) {
        std::cout << "\n=== SISTEMA DE COMPRAS ===\n";
        std::cout << "1. Iniciar sesión\n";
        std::cout << "2. Registrarse\n";
        std::cout << "3. Salir\n";
        std::cout << "Opción: ";

        if (std::cin >> opcion && opcion >= 1 && opcion <= 3) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer
            break;
        } else {
            std::cout << "Entrada inválida. Intente de nuevo.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Sleep(1000);
            system("cls"); // Limpia pantalla en Windows
        }
    }

    switch (opcion) {
        case 1: handleLogin(); break;
        case 2: handleRegister(); break;
        case 3: exit(0);
    }
}

void UserInterface::handleLogin() {
    std::string user, pass;
    std::cout << "Usuario: ";
    std::getline(std::cin, user);

    pass = getHiddenInput("Contraseña: ");

    if (auth.login(user, pass)) {
        std::cout << "Bienvenido, " << user << "!\n";
        Sleep(1000); // Pausa pequeña para mejor UX
    } else {
        std::cout << "Usuario o contraseña incorrectos.\n";
        Sleep(1500);
    }
}

void UserInterface::handleRegister() {
    std::string user, pass;
    std::cout << "Nuevo usuario: ";
    std::getline(std::cin, user);
    pass = getHiddenInput("Contraseña: ");

    if (auth.registerUser(user, pass)) {
        std::cout << "Usuario registrado exitosamente.\n";
    } else {
        std::cout << "El nombre de usuario ya existe.\n";
    }
    Sleep(1500);
}

void UserInterface::showPurchaseMenu() {
    int opcion = 0;
    while (true) {
        std::cout << "\n=== MENÚ DE COMPRAS ===\n";
        std::cout << "1. Listar compras\n";
        std::cout << "2. Agregar nueva compra\n";
        std::cout << "3. Cerrar sesión\n";
        std::cout << "Opción: ";

        if (std::cin >> opcion && opcion >= 1 && opcion <= 3) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer
            break;
        } else {
            std::cout << "Entrada inválida. Intente de nuevo.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Sleep(1000);
            system("cls"); // Limpia pantalla
        }
    }

    switch (opcion) {
        case 1: compras.listarCompras(); break;
        case 2: agregarCompra(); break;
        case 3: auth.logout(); break;
    }
}

void UserInterface::agregarCompra() {
    std::string descripcion;
    double monto = 0.0;

    std::cout << "Descripción de la compra: ";
    std::getline(std::cin, descripcion);

    std::cout << "Monto: ";
    while (!(std::cin >> monto) || monto <= 0) {
        std::cout << "Monto inválido. Ingrese un número positivo: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    compras.agregarCompra(descripcion, monto);
    std::cout << "Compra agregada exitosamente.\n";
    Sleep(1000);
}
