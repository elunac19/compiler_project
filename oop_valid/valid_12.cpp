#include<iostream>
#include<string>

class Producto {
    private:
        std::string nombre;
        double precio;

    public:
        Producto(std::string nombre, double precio) {
            this->nombre = nombre;
            this->precio = precio;
        }

        double getPrecio() {
            return this->precio;
        }

        std::string getNombre() {
            return this->nombre;
        }
};

class Factura {
    private:
        Producto *productos[12];
        int totalProductos;

    public:
        Factura() {
            totalProductos = 0;
        }

        void agregarProducto(Producto *producto) {
            if (totalProductos < 12) {
                productos[totalProductos] = producto;
                totalProductos++;
            } else {
                std::cout << "Factura llena, no se puede agregar más productos.\n";
            }
        }

        double calcularTotal() {
            double total = 0;
            for (int i = 0; i < totalProductos; i++) {
                total += productos[i]->getPrecio();
            }
            return total;
        }
};

int main() {
    Factura factura;
    Producto prod1("Producto 1", 10.0);
    Producto prod2("Producto 2", 20.0);

    factura.agregarProducto(&prod1);
    factura.agregarProducto(&prod2);

    std::cout << "El total de la factura es: " << factura.calcularTotal() << "\n";

    return 0;
}