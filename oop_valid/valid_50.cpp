#include <iostream>
#include <string>

class Resolucion {
private:
    int ancho;
    int alto;
public:
    Resolucion(int ancho, int alto) : ancho(ancho), alto(alto) {}
    int getAncho() const { return ancho; }
    int getAlto() const { return alto; }
};

class Pantalla {
private:
    std::string marca;
    std::string modelo;
    Resolucion resolucion;
public:
    Pantalla(std::string marca, std::string modelo, Resolucion resolucion) 
        : marca(marca), modelo(modelo), resolucion(resolucion) {}
    void mostrarDetalles() {
        std::cout << "Marca: " << marca << ", Modelo: " << modelo << ", Resolucion: " << resolucion.getAncho() << "x" << resolucion.getAlto() << std::endl;
    }
};

int main() {
    Resolucion res(1920, 1080);
    Pantalla pantalla("Samsung", "S24F350", res);
    pantalla.mostrarDetalles();
    return 0;
}