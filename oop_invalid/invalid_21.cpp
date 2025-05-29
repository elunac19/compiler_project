#include<iostream>

struct Parlante {
    int volumen;
    
    void setVolumen(int v) {
        volumen = v;
    }
    
    int getVolumen() {
        return volumen;
    }
};

int main() {
    Parlante p;
    p.setVolumen(21);
    std::cout << "El volumen del parlante es: " << p.getVolumen() << std::endl;
    return 0;
}