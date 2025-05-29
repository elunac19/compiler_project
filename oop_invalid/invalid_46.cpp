#include <iostream>

struct Parlante {
    int volumen;
    void setVolumen(int val) {
        volumen = val;
    }

    int getVolumen() {
        return volumen;
    }
};

int main() {
    Parlante parlante;
    parlante.setVolumen(46);
    std::cout << "El volumen del parlante es: " << parlante.getVolumen() << std::endl;
    return 0;
}