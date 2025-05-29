#include <iostream>

struct Rectangulo {
    int largo;
    int ancho;

    void inicializar(int l, int a) {
        largo = l;
        ancho = a;
    }

    int calcularArea() {
        return largo * ancho;
    }
};

int main() {
    Rectangulo r1;
    r1.inicializar(7, 4);
    std::cout << "El área del rectángulo es: " << r1.calcularArea() << std::endl;
    return 0;
}