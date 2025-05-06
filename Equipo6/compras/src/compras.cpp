#include "compras.h"
#include <iomanip>
#include <limits>

void Compras::mostrarMenu() {
    cout << "\n=== SISTEMA DE COMPRAS A PROVEEDORES ===" << endl;
    cout << "1. Registrar nueva compra" << endl;
    cout << "2. Mostrar historial de compras" << endl;
    cout << "3. Buscar compras por proveedor" << endl;
    cout << "4. Calcular total gastado" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

void Compras::registrarCompra(vector<Producto>& listaCompras) {
    Producto nuevaCompra;

    cout << "\n--- REGISTRAR NUEVA COMPRA ---" << endl;

    cout << "Nombre del producto: ";
    cin.ignore();  // Limpia el buffer
    getline(cin, nuevaCompra.nombre);

    cout << "Proveedor: ";
    getline(cin, nuevaCompra.proveedor);

    cout << "Precio de compra por unidad (Q): ";
    while (!(cin >> nuevaCompra.precioCompra) || nuevaCompra.precioCompra <= 0) {
        cout << "Valor inválido. Ingrese el precio en quetzales (Q): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Cantidad comprada: ";
    while (!(cin >> nuevaCompra.cantidad) || nuevaCompra.cantidad <= 0) {
        cout << "Cantidad inválida. Ingrese un número positivo: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Fecha de compra (DD/MM/AAAA): ";
    cin.ignore();
    getline(cin, nuevaCompra.fechaCompra);

    listaCompras.push_back(nuevaCompra);
    cout << "\n✅ Compra registrada exitosamente" << endl;
}

void Compras::mostrarHistorial(const vector<Producto>& listaCompras) {
    if (listaCompras.empty()) {
        cout << "\n⚠️ No hay compras registradas." << endl;
        return;
    }

    cout << "\n--- HISTORIAL DE COMPRAS ---" << endl;
    cout << left << setw(25) << "PRODUCTO" << setw(20) << "PROVEEDOR"
         << setw(15) << "PRECIO (Q)" << setw(10) << "CANTIDAD"
         << setw(15) << "TOTAL (Q)" << setw(12) << "FECHA" << endl;
    cout << string(97, '-') << endl;

    for (const auto& compra : listaCompras) {
        double total = compra.precioCompra * compra.cantidad;
        cout << left << setw(25) << compra.nombre
             << setw(20) << compra.proveedor
             << "Q" << setw(14) << fixed << setprecision(2) << compra.precioCompra
             << setw(10) << compra.cantidad
             << "Q" << setw(14) << total
             << setw(12) << compra.fechaCompra << endl;
    }
}

void Compras::buscarPorProveedor(const vector<Producto>& listaCompras) {
    string proveedorBuscado;
    cout << "\n🔍 Ingrese el nombre del proveedor: ";
    cin.ignore();
    getline(cin, proveedorBuscado);

    bool encontrado = false;
    for (const auto& compra : listaCompras) {
        if (compra.proveedor == proveedorBuscado) {
            encontrado = true;
            cout << "📦 Producto: " << compra.nombre
                 << " | Cantidad: " << compra.cantidad
                 << " | Total: Q" << fixed << setprecision(2) << (compra.precioCompra * compra.cantidad)
                 << " | Fecha: " << compra.fechaCompra << endl;
        }
    }

    if (!encontrado) {
        cout << "❌ No se encontraron compras a este proveedor." << endl;
    }
}

double Compras::calcularTotalGastado(const vector<Producto>& listaCompras) {
    double total = 0;
    for (const auto& compra : listaCompras) {
        total += compra.precioCompra * compra.cantidad;
    }
    return total;
}
