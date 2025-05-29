#include <iostream>
#include <string>

class Producto {
private:
    std::string nombre;
    double precio;
    int cantidad;

public:
    Producto(std::string nombre, double precio, int cantidad) {
        this->nombre = nombre;
        this->precio = precio;
        this->cantidad = cantidad;
    }

    std::string getNombre() {
        return this->nombre;
    }

    double getPrecio() {
        return this->precio;
    }

    int getCantidad() {
        return this->cantidad;
    }

    void setCantidad(int cantidad) {
        this->cantidad = cantidad;
    }
};

class Inventario {
private:
    Producto* productos[35];
    int contador;

public:
    Inventario() {
        this->contador = 0;
    }

    void agregarProducto(Producto* producto) {
        if (contador < 35) {
            this->productos[contador] = producto;
            contador++;
        } else {
            std::cout << "Inventario lleno." << std::endl;
        }
    }

    void mostrarInventario() {
        for (int i = 0; i < contador; i++) {
            std::cout << "Producto: " << productos[i]->getNombre() << ", Precio: " << productos[i]->getPrecio() << ", Cantidad: " << productos[i]->getCantidad() << std::endl;
        }
    } 
};

int main() {
    Inventario inventario;
    Producto producto1("Laptop", 1200.50, 10);
    Producto producto2("Mouse", 25.99, 50);
    inventario.agregarProducto(&producto1);
    inventario.agregarProducto(&producto2);
    inventario.mostrarInventario();
    return 0;
}