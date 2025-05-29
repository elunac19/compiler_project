#include <iostream>
#include <string>
#include <vector>

class Autor {
private:
    std::string nombre;
public:
    Autor(const std::string &nombre) : nombre(nombre) {}

    std::string getNombre() const {
        return nombre;
    }
};

class Libro {
private:
    std::string titulo;
    std::vector<Autor> autores;

public:
    Libro(const std::string &titulo) : titulo(titulo) {}

    void agregarAutor(const Autor &autor) {
        autores.push_back(autor);
    }

    std::string getTitulo() const {
        return titulo;
    }

    void imprimirAutores() const {
        std::cout << "Autores de " << titulo << ":\n";
        for (const auto &autor : autores)
            std::cout << autor.getNombre() << "\n";
    }
};

int main() {
    Autor autor1("Autor 1");
    Autor autor2("Autor 2");

    Libro libro1("Libro 1");
    libro1.agregarAutor(autor1);
    libro1.agregarAutor(autor2);

    std::cout << "Titulo del libro: " << libro1.getTitulo() << "\n";
    libro1.imprimirAutores();

    return 0;
}