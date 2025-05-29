struct Producto {
    int id;
    std::string nombre;
    double precio;
};

struct OrdenDeCompra {
    Producto producto;
    int cantidad;

    double calcularTotal() {
        double total = producto.precio * cantidad;
        return total;
    }
};

int main() {
    Producto product;
    product.id = 23;
    product.nombre = "Libro";
    product.precio = 150.5;

    OrdenDeCompra orden;
    orden.producto = product;
    orden.cantidad = 2;

    std::cout << "El total de la orden de compra es: " << orden.calcularTotal() << std::endl;

    return 0;
}