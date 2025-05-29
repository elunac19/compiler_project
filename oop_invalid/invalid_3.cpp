#include <iostream>

struct Rectangulo {
    int largo;
    int ancho;

    void setLargo(int l) {
        largo = l;
    }

    void setAncho(int a) {
        ancho = a;
    }

    int getLargo() {
        return largo;
    }

    int getAncho() {
        return ancho;
    }

    int calcularArea() {
        return largo * ancho;
    }
};

int main() {
    Rectangulo r;
    r.setLargo(5);
    r.setAncho(4);
    int area = r.calcularArea();

    std::cout << "Area del rectangulo: " << area << std::endl;

    return 0;
}