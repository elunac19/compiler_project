#include <iostream>
#include <string>
#include <vector>

class Contacto {
private:
    std::string nombre;
    std::string telefono;

public:
    Contacto(std::string nom, std::string tel) : nombre(nom), telefono(tel) {}

    std::string getNombre() {
        return nombre;
    }

    std::string getTelefono() {
        return telefono;
    }

    void setNombre(std::string nom) {
        nombre = nom;
    }

    void setTelefono(std::string tel) {
        telefono = tel;
    }
};

class Agenda {
private:
    std::vector<Contacto> contactos;

public:
    Agenda() {}

    void agregarContacto(Contacto c) {
        contactos.push_back(c);
    }

    void eliminarContacto(std::string nombre) {
        for (int i = 0; i < contactos.size(); i++) {
            if (contactos[i].getNombre() == nombre) {
                contactos.erase(contactos.begin() + i);
                break;
            }
        }
    }

    void mostrarContactos() {
        for (int i = 0; i < contactos.size(); i++) {
            std::cout << "Nombre: " << contactos[i].getNombre() << ", Telefono: " << contactos[i].getTelefono() << std::endl;
        }
    }
};

int main() {
    Agenda miAgenda;
    Contacto c1("John Doe", "555-5555");
    Contacto c2("Jane Doe", "666-6666");

    miAgenda.agregarContacto(c1);
    miAgenda.agregarContacto(c2);

    miAgenda.mostrarContactos();

    miAgenda.eliminarContacto("John Doe");

    miAgenda.mostrarContactos();

    return 0;
}