#include <iostream>
#include <string>
#include <vector>

struct Producto {
    std::string nombre;
    int cantidad;
    double precio;
};

struct Inventario {
    std::vector<Producto> productos;

    void agregarProducto(std::string nombre, int cantidad, double precio){
        Producto prod;
        prod.nombre = nombre;
        prod.cantidad = cantidad;
        prod.precio = precio;
        productos.push_back(prod);
    }

    void mostrarInventario(){
        for(int i = 0; i < productos.size(); i++){
            std::cout << "Nombre: " << productos[i].nombre << ", Cantidad: " << productos[i].cantidad << ", Precio: $" << productos[i].precio << "\n";
        }
    }
};

int main(){
    Inventario inv;
    inv.agregarProducto("Manzana", 10, 0.99);
    inv.agregarProducto("Naranja", 15, 0.75);
    inv.agregarProducto("Uvas", 8, 1.50);
    inv.mostrarInventario();
    
    return 0;
}