#include<iostream>
#include<string>

class Producto {
private:
    std::string nombre;
    double precio;
public:
    Producto(const std::string& nombre, double precio) : nombre(nombre), precio(precio) {}

    std::string getNombre() const {
        return nombre;
    }

    double getPrecio() const {
        return precio;
    }
};

class OrdenCompra {
private:
    int id;
    Producto* producto;
    int cantidad;
public:
    OrdenCompra(int id, Producto* producto, int cantidad) : id(id), producto(producto), cantidad(cantidad) {}

    double calcularTotal() const {
        return producto->getPrecio() * cantidad;
    }

    void mostrarOrden() const {
        std::cout << "Orden ID: " << id << "\n";
        std::cout << "Producto: " << producto->getNombre() << "\n";
        std::cout << "Cantidad: " << cantidad << "\n";
        std::cout << "Total: " << calcularTotal() << "\n";
    }
};

int main() {
    Producto prod1("Laptop", 1500.00);
    OrdenCompra orden1(23, &prod1, 2);
    orden1.mostrarOrden();
    return 0;
}