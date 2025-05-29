#include <iostream>
#include <string>

struct ControlRemoto {
    std::string marca;
    int numeroCanal;
    int volumen;

    void setMarca(std::string m) { marca = m; }
    void setCanal(int c) { numeroCanal = c; }
    void setVolumen(int v) { volumen = v; }

    std::string getMarca() { return marca; }
    int getCanal() { return numeroCanal; }
    int getVolumen() { return volumen; }

    void aumentarVolumen() { if(volumen < 100) volumen++; }
    void disminuirVolumen() { if(volumen > 0) volumen--; }
    void cambiarCanal(int nuevoCanal) { numeroCanal = nuevoCanal; }
};

int main() {
    ControlRemoto miControl;
    
    miControl.setMarca("Sony");
    miControl.setCanal(24);
    miControl.setVolumen(50);
    
    std::cout << "Marca: " << miControl.getMarca() << "\n";
    std::cout << "Canal: " << miControl.getCanal() << "\n";
    std::cout << "Volumen: " << miControl.getVolumen() << "\n";

    miControl.aumentarVolumen();
    miControl.cambiarCanal(30);

    std::cout << "Canal: " << miControl.getCanal() << "\n";
    std::cout << "Volumen: " << miControl.getVolumen() << "\n";

    return 0;
}