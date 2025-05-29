#include <iostream>
#include <string>

class Producto {
private:
    std::string nombre;
    double precio;
public:
    Producto(const std::string& nombre, double precio) : nombre(nombre), precio(precio) {}
    std::string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }
};

class Factura {
private:
    Producto* productos[37];
    int totalProductos;
public:
    Factura() : totalProductos(0) {}
    void agregarProducto(const Producto& producto){
        if(totalProductos < 37){
            productos[totalProductos++] = new Producto(producto);
        }
    }
    double calcularTotal() const {
        double total = 0;
        for(int i = 0; i < totalProductos; ++i){
            total += productos[i]->getPrecio();
        }
        return total;
    }
    ~Factura(){
        for(int i = 0; i < totalProductos; ++i){
            delete productos[i];
        }
    }
};

int main() {
    Factura factura;
    factura.agregarProducto(Producto("Producto1", 10.0));
    factura.agregarProducto(Producto("Producto2", 20.0));
    factura.agregarProducto(Producto("Producto3", 30.0));

    std::cout << "Total de la factura: " << factura.calcularTotal() << std::endl;

    return 0;
}