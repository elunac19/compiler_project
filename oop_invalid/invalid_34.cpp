#include <iostream>
#include <string>

struct Reloj {
    int horas;
    int minutos;
    int segundos;

    void establecerHora(int h) {
        horas = h;
    }
    void establecerMinutos(int m) {
        minutos = m;
    }
    void establecerSegundos(int s) {
        segundos = s;
    }
    int obtenerHora() {
        return horas;
    }
    int obtenerMinutos() {
        return minutos;
    }
    int obtenerSegundos() {
        return segundos;
    }
    void mostrarTiempo(){
        std::cout<<horas<<":"<<minutos<<":"<<segundos<<std::endl;
    }
};

int main() {
    Reloj reloj1;
    reloj1.establecerHora(10);
    reloj1.establecerMinutos(34);
    reloj1.establecerSegundos(55);
    reloj1.mostrarTiempo();
    return 0;
}