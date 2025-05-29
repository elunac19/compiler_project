#include<iostream>
#include<string>
#include<vector>

struct Persona {
    std::string nombre;
    std::string telefono;
};

struct Agenda {
    std::vector<Persona> contactos;

    void agregarContacto(Persona persona) {
        contactos.push_back(persona);
    }

    void mostrarContactos() {
        for(auto contacto : contactos) {
            std::cout << "Nombre: " << contacto.nombre << ", Teléfono: " << contacto.telefono << std::endl;
        }
    }
};

int main() {
    Persona contacto1 = { "Juan", "1234567890" };
    Persona contacto2 = { "Ana", "0987654321" };
    Persona contacto3 = { "Pedro", "1122334455" };

    Agenda miAgenda;
    miAgenda.agregarContacto(contacto1);
    miAgenda.agregarContacto(contacto2);
    miAgenda.agregarContacto(contacto3);

    miAgenda.mostrarContactos();

    return 0;
}