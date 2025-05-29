#include <iostream>
#include <string>

class DispositivoElectronico {
private:
    std::string marca;
    std::string modelo;

public:
    DispositivoElectronico(std::string marca, std::string modelo) {
        this->marca = marca;
        this->modelo = modelo;
    }

    std::string obtenerMarca(){
        return this->marca;
    }

    std::string obtenerModelo() {
        return this->modelo;
    }
};

class TelefonoMovil : public DispositivoElectronico {
private:
    int memoria;
    bool es5G;

public:
    TelefonoMovil(std::string marca, std::string modelo, int memoria, bool es5G) : DispositivoElectronico(marca, modelo) {
        this->memoria = memoria;
        this->es5G = es5G;
    }

    int obtenerMemoria() {
        return this->memoria;
    }

    bool soporta5G() {
        return this->es5G;
    }
};

int main() {
    TelefonoMovil movil("Samsung", "Galaxy S21", 128, true);

    std::cout << "Marca: " << movil.obtenerMarca() << std::endl;
    std::cout << "Modelo: " << movil.obtenerModelo() << std::endl;
    std::cout << "Memoria: " << movil.obtenerMemoria() << "GB" << std::endl;
    std::cout << "Soporta 5G: " << (movil.soporta5G() ? "Si" : "No") << std::endl;

    return 0;
}