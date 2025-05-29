#include <iostream>
#include <iomanip>

class Hora {
private:
    int horas;
    int minutos;
    int segundos;

public:
    Hora(int h=0, int m=0, int s=0) : horas(h), minutos(m), segundos(s) {}

    void setHora(int h, int m, int s) {
        horas = h;
        minutos = m;
        segundos = s;
    }

    void imprimir() const {
        std::cout << std::setw(2) << std::setfill('0') << horas << ":"
                  << std::setw(2) << std::setfill('0') << minutos << ":"
                  << std::setw(2) << std::setfill('0') << segundos << std::endl;
    }
};

class RelojDigital {
private:
    Hora horaActual;

public:
    RelojDigital(int h=0, int m=0, int s=0) : horaActual(h, m, s) {}

    void setHora(int h, int m, int s) {
        horaActual.setHora(h, m, s);
    }

    void mostrarHora() const {
        horaActual.imprimir();
    }
};

int main() {
    RelojDigital reloj(10, 30, 45);
    reloj.mostrarHora();
    reloj.setHora(15, 45, 30);
    reloj.mostrarHora();
    return 0;
}