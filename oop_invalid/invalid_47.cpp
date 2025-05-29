#include <iostream>
#include <string>

struct DispositivoElectronico {
    std::string nombre;
    int numero;

    void definirNombre(std::string nombre) {
        nombre = nombre;
    }

    std::string obtenerNombre() {
        return nombre;
    }

    void definirNumero(int numero) {
        numero = numero;
    }

    int obtenerNumero() {
        return numero;
    }
};

int main() {
    DispositivoElectronico dispositivo1;
    dispositivo1.definirNombre("TV");
    dispositivo1.definirNumero(47);
    std::cout << "Dispositivo: " << dispositivo1.obtenerNombre() << " Numero: " << dispositivo1.obtenerNumero() << "\n";

    return 0;
}
