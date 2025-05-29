#include<iostream>

struct DispositivoElectronico {
    int id;
    std::string nombre;
    bool estado;

    void Encender() {
        estado = true;
        std::cout << "Dispositivo encendido.\n";
    }

    void Apagar() {
        estado = false;
        std::cout << "Dispositivo apagado.\n";
    }

    void MostrarEstado() {
        if (estado) std::cout << "El dispositivo está encendido.\n";
        else std::cout << "El dispositivo está apagado.\n";
    }
};

struct Smartphone : DispositivoElectronico {
    std::string sistemaOperativo;

    void InstalarApp(std::string nombreApp) {
        std::cout << "Instalando " << nombreApp << " en " << nombre << ".\n";
    }
};

int main() {
    Smartphone dispositivo1;
    dispositivo1.nombre = "iPhone 12";
    dispositivo1.sistemaOperativo = "iOS";
    dispositivo1.Encender();
    dispositivo1.InstalarApp("Whatsapp");
    dispositivo1.MostrarEstado();
    return 0;
}