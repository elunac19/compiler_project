#include <iostream>
using namespace std;

struct Jugador {
    int puntos;

    void asignarPuntos(int n) {
        puntos = n;
    }

    int obtenerPuntos() {
        return puntos;
    }
};

struct Juego {
    Jugador jugador1;
    Jugador jugador2;

    void iniciarJuego() {
        jugador1.asignarPuntos(0);
        jugador2.asignarPuntos(0);
    }

    void agregarPuntosJugador1(int n) {
        jugador1.puntos += n;
    }

    void agregarPuntosJugador2(int n) {
        jugador2.puntos += n;
    }

    int obtenerPuntosJugador1() {
        return jugador1.obtenerPuntos();
    }

    int obtenerPuntosJugador2() {
        return jugador2.obtenerPuntos();
    }

    void mostrarPuntos() {
        cout << "Jugador 1: " << obtenerPuntosJugador1() << endl;
        cout << "Jugador 2: " << obtenerPuntosJugador2() << endl;
    }
};

int main() {
    Juego juego;

    juego.iniciarJuego();
    juego.agregarPuntosJugador1(5);
    juego.agregarPuntosJugador2(7);
    juego.mostrarPuntos();

    return 0;
}