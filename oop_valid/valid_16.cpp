#include <iostream>
#include <string>

class Estado {
private:
    std::string estado;

public:
    Estado(std::string estado) : estado(estado) {}

    std::string getEstado() {
        return this->estado;
    }
};

class Pedido {
private:
    int id;
    std::string descripcion;
    Estado* estado;

public:
    Pedido(int id, std::string descripcion, Estado* estado) : id(id), descripcion(descripcion), estado(estado) {}

    void cambiarEstado(Estado* nuevoEstado) {
        this->estado = nuevoEstado;
    }

    void imprimirPedido() {
        std::cout << "Pedido ID: " << this->id << "\n";
        std::cout << "Descripcion: " << this->descripcion << "\n";
        std::cout << "Estado: " << this->estado->getEstado() << "\n";
    }
};

int main() {
    Estado* preparacion = new Estado("En preparacion");
    Estado* enviado = new Estado("Enviado");

    Pedido* pedido = new Pedido(1, "Pedido de libros", preparacion);
    pedido->imprimirPedido();

    pedido->cambiarEstado(enviado);
    pedido->imprimirPedido();

    delete preparacion;
    delete enviado;
    delete pedido;

    return 0;
}