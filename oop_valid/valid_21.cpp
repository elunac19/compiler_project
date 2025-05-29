#include<iostream>
using namespace std;

class Volumen {
private:
    int nivel;

public:
    Volumen(int nivel_inicial=0) : nivel(nivel_inicial) {}

    int obtenerNivel() {
        return nivel;
    }

    void aumentar() {
        if(nivel < 100)
            nivel++;
    }

    void disminuir() {
        if(nivel > 0)
            nivel--;
    }
};

class Parlante {
private:
    Volumen volumen;

public:
    Parlante(int nivel_inicial=0) : volumen(nivel_inicial) {}

    void aumentarVolumen() {
        volumen.aumentar();
        cout << "Volumen aumentado a: " << volumen.obtenerNivel() << endl;
    }

    void disminuirVolumen() {
        volumen.disminuir();
        cout << "Volumen disminuido a: " << volumen.obtenerNivel() << endl;
    }
};

int main() {
    Parlante miParlante(50);
    miParlante.aumentarVolumen();
    miParlante.disminuirVolumen();
    return 0;
}