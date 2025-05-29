#include<iostream>
#include<string>

class Estado{
    private:
        std::string estado;
    public:
        Estado(std::string estado) : estado(estado){}
        std::string getEstado() { return this->estado; }
        void setEstado(std::string estado) { this->estado = estado; }   
};

class Pedido{
    private:
        int numero;
        std::string descripcion;
        Estado* estadoPedido;

    public:
        Pedido(int numero, std::string descripcion, Estado* estadoPedido) : numero(numero), descripcion(descripcion), estadoPedido(estadoPedido) {}
        void mostrarPedido() {
            std::cout<<"Pedido Numero: "<<this->numero<<std::endl;
            std::cout<<"Descripcion: "<<this->descripcion<<std::endl;
            std::cout<<"Estado: "<<this->estadoPedido->getEstado()<<std::endl;
        }
        void setEstado(Estado* nuevoEstado) { this->estadoPedido = nuevoEstado; }
};

int main(){
    Estado* nuevo = new Estado("Nuevo");
    Estado* procesando = new Estado("Procesando");
    Estado* enviado = new Estado("Enviado");

    Pedido* pedido1 = new Pedido(1, "Zapatos", nuevo);
    Pedido* pedido2 = new Pedido(2, "Camiseta", procesando);

    pedido1->mostrarPedido();
    pedido2->mostrarPedido();

    pedido1->setEstado(enviado);
    pedido1->mostrarPedido();

    delete nuevo;
    delete procesando;
    delete enviado;

    delete pedido1;
    delete pedido2;

    return 0;
}