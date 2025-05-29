#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Contacto {
private:
    string nombre;
    string telefono;
    string email;

public:
    Contacto(string nombre, string telefono, string email) {
        this->nombre = nombre;
        this->telefono = telefono;
        this->email = email;
    }

    string getNombre() {
        return this->nombre;
    }

    string getTelefono() {
        return this->telefono;
    }

    string getEmail() {
        return this->email;
    }
};

class Agenda {
private:
    vector<Contacto> contactos;

public:
    void agregarContacto(Contacto nuevoContacto) {
        contactos.push_back(nuevoContacto);
    }

    void mostrarContactos() {
        for (int i = 0; i < contactos.size(); i++) {
            cout << "Nombre: " << contactos[i].getNombre() << "\n";
            cout << "Telefono: " << contactos[i].getTelefono() << "\n";
            cout << "Email: " << contactos[i].getEmail() << "\n";
            cout << "--------------------------\n";
        }
    }
};

int main() {
    Agenda miAgenda;
    miAgenda.agregarContacto(Contacto("Juan", "111-222-333", "juan@example.com"));
    miAgenda.agregarContacto(Contacto("Ana", "222-333-444", "ana@example.com"));
    miAgenda.agregarContacto(Contacto("Carlos", "333-444-555", "carlos@example.com"));

    miAgenda.mostrarContactos();

    return 0;
}