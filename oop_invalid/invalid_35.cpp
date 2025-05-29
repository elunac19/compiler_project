#include <iostream>
#include <string>
#include <vector>

struct Producto {
    std::string nombre;
    int cantidad;
    float precio;
};

struct Inventario {
    std::vector<Producto> productos;

    void agregarProducto(std::string nom, int cant, float prec) {
        Producto p = {nom, cant, prec};
        productos.push_back(p);
    }

    void mostrarInventario() {
        for (int i = 0; i < productos.size(); i++) {
            std::cout << "Nombre: " << productos[i].nombre << ", Cantidad: " << productos[i].cantidad << ", Precio: " << productos[i].precio << std::endl;
        }
    }
};

int main() {
    Inventario inv;

    inv.agregarProducto("Producto 1", 10, 15.5);
    inv.agregarProducto("Producto 2", 20, 30.5);
    inv.agregarProducto("Producto 3", 30, 45.5);

    inv.mostrarInventario();

    return 0;
}