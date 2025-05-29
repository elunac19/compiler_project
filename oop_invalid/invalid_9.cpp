#include <iostream>
#include <ctime>

struct RelojDigital {
    int horas;
    int minutos;
    int segundos;
};

void setHora(RelojDigital &rd, int hora) {
    rd.horas = hora;
}

void setMinutos(RelojDigital &rd, int min) {
    rd.minutos = min;
}

void setSegundos(RelojDigital &rd, int seg) {
    rd.segundos = seg;
}

void mostrarHora(RelojDigital &rd) {
    std::cout << rd.horas << ":" << rd.minutos << ":" << rd.segundos << std::endl;
}

int main() {
    RelojDigital rd1;
    setHora(rd1, 10);
    setMinutos(rd1, 20);
    setSegundos(rd1, 30);
    mostrarHora(rd1);
    
    return 0;
}