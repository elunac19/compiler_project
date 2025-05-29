#include <iostream>
#include <string>
#include <vector>

class Producto {
private:
    std::string nombre;
    int cantidad;
    double precio;
public:
    Producto(std::string nom, int cant, double pre) : nombre(nom), cantidad(cant), precio(pre)
    {}

    std::string getNombre() {
        return nombre;
    }

    int getCantidad() {
        return cantidad;
    }

    double getPrecio() {
        return precio;
    }

    void setCantidad(int cant) {
        this->cantidad = cant;
    }
};

class Inventario {
private:
    std::vector<Producto> productos;
public:
    void agregarProducto(Producto p) {
        productos.push_back(p);
    }

    void mostrarInventario() {
        for(Producto p : productos) {
            std::cout << "Nombre: " << p.getNombre() << std::endl;
            std::cout << "Cantidad: " << p.getCantidad() << std::endl;
            std::cout << "Precio: " << p.getPrecio() << std::endl;
            std::cout << "------------------" << std::endl;
        }
    }
};

int main() {
    Inventario inv;
    inv.agregarProducto(Producto("Manzana", 10, 1.99));
    inv.agregarProducto(Producto("Banana", 20, 0.99));
    inv.agregarProducto(Producto("Naranja", 30, 1.49));

    inv.mostrarInventario();
    
    return 0;
}