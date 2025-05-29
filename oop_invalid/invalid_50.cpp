#include <iostream>
#include <string>
using namespace std;

struct Pantalla {
    int ancho, alto;
    string tipo;

    void setAncho(int a){
        ancho=a;
    }
    void setAlto(int a){
        alto=a;
    }
    void setTipo(string t){
        tipo=t;
    }

    int getAncho(){
        return ancho;
    }
    int getAlto(){
        return alto;
    }
    string getTipo(){
        return tipo;
    }

    int calculaResolucion(){
        return ancho*alto;
    }
};

struct Television: Pantalla {
    string nombre;
    void setNombre(string n){
        nombre=n;
    }
    string getNombre(){
        return nombre;
    }

    void imprimirDetalles(){
        cout << "Nombre: " << getNombre() << endl;
        cout << "Tipo: " << getTipo() << endl;
        cout << "Resolución: " << calculaResolucion() << endl;
    }
};

int main() {
    Television tv;
    tv.setNombre("Samsung");
    tv.setAncho(1920);
    tv.setAlto(1080);
    tv.setTipo("LED");
    tv.imprimirDetalles();
    return 0;
}
