#include <iostream>
#include <string>

struct Pedido {
    int id;
    std::string producto;
    int cantidad;
    std::string estado;
};

struct Estado {
    std::string estado;

    void cambiarEstado(Pedido* pedido, std::string nuevoEstado) {
        pedido->estado = nuevoEstado;
    }
};

int main() {
    Pedido pedido1;
    pedido1.id = 1;
    pedido1.producto = "Computadora";
    pedido1.cantidad = 3;
    pedido1.estado = "En proceso";

    Estado herramientaEstado;
    herramientaEstado.cambiarEstado(&pedido1, "Enviado");

    std::cout << "Pedido ID: " << pedido1.id << std::endl;
    std::cout << "Producto: " << pedido1.producto << std::endl;
    std::cout << "Cantidad: " << pedido1.cantidad << std::endl;
    std::cout << "Estado: " << pedido1.estado << std::endl;

    return 0;
}