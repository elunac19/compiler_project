#include<iostream>
#include<string>

struct Pedido{
    int id;
    std::string producto;
    int cantidad;
    std::string estado;
};

struct Estado{
    std::string nombre;
    std::string descripcion;
};

void setId(Pedido *p, int id){
    p->id = id;
}

void setProducto(Pedido *p, std::string producto){
    p->producto = producto;
}

void setCantidad(Pedido *p, int cantidad){
    p -> cantidad = cantidad;
}

void setEstado(Pedido *p, std::string estado){
    p->estado = estado;
}

void setNombre(Estado *e, std::string nombre){
    e->nombre = nombre;
}

void setDescripcion(Estado *e, std::string descripcion){
    e->descripcion = descripcion;
}

int getId(Pedido *p){
    return p->id;
}

std::string getProducto(Pedido *p){
    return p->producto;
}

int getCantidad(Pedido *p){
    return p->cantidad;
}

std::string getEstado(Pedido *p){
    return p->estado;
}

std::string getNombre(Estado *e){
    return e->nombre;
}

std::string getDescripcion(Estado *e){
    return e->descripcion;
}

int main(){
    Pedido p;
    Estado e;

    setId(&p, 1);
    setProducto(&p, "Pizza");
    setCantidad(&p, 2);
    setEstado(&p, "En camino");
    setNombre(&e, "En camino");
    setDescripcion(&e, "El pedido se encuentra en camino a la dirección indicada.");

    std::cout << "Pedido ID: " << getId(&p) << "\n";
    std::cout << "Producto: " << getProducto(&p) << "\n";
    std::cout << "Cantidad: " << getCantidad(&p) << "\n";
    std::cout << "Estado: " << getEstado(&p) << "\n";
    std::cout << "Estado detalle: " << getNombre(&e) << " - " << getDescripcion(&e) << "\n";

    return 0;
}