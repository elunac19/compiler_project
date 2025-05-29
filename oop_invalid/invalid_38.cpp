#include <iostream>

struct Jugador {
    int puntos;

    void asignarPuntos(int p) {
        puntos = p;
    }

    int obtenerPuntos() {
        return puntos;
    }
};

struct Juego {
    Jugador jugador1;
    Jugador jugador2;

    void iniciarJuego(int p1, int p2) {
        jugador1.asignarPuntos(p1);
        jugador2.asignarPuntos(p2);
    }

    void mostrarPuntos() {
        std::cout << "Jugador 1: " << jugador1.obtenerPuntos() << "\n";
        std::cout << "Jugador 2: " << jugador2.obtenerPuntos() << "\n";
    }
};

int main() {
    Juego juego;
    juego.iniciarJuego(38, 38);
    juego.mostrarPuntos();
    return 0;
}