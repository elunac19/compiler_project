#include<iostream>
#include<string>

struct Factura {
    int total;
    std::string producto;

    void setTotal(int t) {
        total = t;
    }

    void setProducto(std::string p) {
        producto = p;
    }

    int getTotal() {
        return total;
    }

    std::string getProducto() {
        return producto;
    }
};

int main() {
    Factura factura1;
    factura1.setTotal(37);
    factura1.setProducto("Libro");

    std::cout << "Producto: " << factura1.getProducto() << "\n";
    std::cout << "Total: " << factura1.getTotal() << "\n";

    return 0;
}