#include <iostream>
#include <string>

class DispositivoElectronico {
private:
    std::string nombre;
    bool encendido;

public:
    DispositivoElectronico(std::string nom) : nombre(nom), encendido(false) {}

    void encender() {
        encendido = true;
        std::cout << nombre << " encendido." << std::endl;
    }

    void apagar() {
        encendido = false;
        std::cout << nombre << " apagado." << std::endl;
    }

    bool estaEncendido() const {
        return encendido;
    }
};

class TelefonoMovil : public DispositivoElectronico {
private:
    std::string numero;

public:
    TelefonoMovil(std::string nom, std::string num) : DispositivoElectronico(nom), numero(num) {}

    void llamar(std::string numDestino) {
        if(estaEncendido()) {
            std::cout << "Llamando a " << numDestino << " desde " << numero << std::endl;
        }
        else {
            std::cout << "El teléfono está apagado. No se puede realizar la llamada." << std::endl;
        }
    }
};

int main() {
    TelefonoMovil miTelefono("Samsung Galaxy", "1234567890");
    miTelefono.encender();
    miTelefono.llamar("0987654321");
    miTelefono.apagar();
    miTelefono.llamar("0987654321");

    return 0;
}