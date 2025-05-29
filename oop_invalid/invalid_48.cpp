#include <iostream>
#include <vector>
#include <string>

struct Proveedor {
  std::string nombre;
  std::string direccion;
};

struct Producto {
  std::string nombre;
  int cantidad;
  double precio;
};

struct OrdenCompra {
  Proveedor proveedor;
  std::vector<Producto> productos;

  void agregarProducto(Producto producto){
    productos.push_back(producto);
  }

  double calcularTotal(){
    double total = 0;
    for(auto producto : productos){
      total += producto.cantidad * producto.precio;
    }
    return total;
  }

  void imprimirOrden(){
    std::cout << "Proveedor: " << proveedor.nombre << "\n";
    std::cout << "Direccion: " << proveedor.direccion << "\n";
    for(auto producto : productos){
      std::cout << "Producto: " << producto.nombre << ", "
                << "Cantidad: " << producto.cantidad << ", "
                << "Precio: " << producto.precio << "\n";
    }
    std::cout << "Total: " << calcularTotal() << "\n";
  }
};

int main() {
  Proveedor proveedor = {"Proveedor Uno", "Direccion Uno"};
  Producto producto1 = {"Producto Uno", 5, 10.0};
  Producto producto2 = {"Producto Dos", 3, 15.0};

  OrdenCompra ordenCompra = {proveedor};
  ordenCompra.agregarProducto(producto1);
  ordenCompra.agregarProducto(producto2);
  ordenCompra.imprimirOrden();
  return 0;
}