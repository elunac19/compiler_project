#include <iostream>
#include <string>

class Autor {
private:
    std::string nombre;
    std::string apellido;
public:
    Autor(std::string nombre, std::string apellido) {
        this->nombre = nombre;
        this->apellido = apellido;
    }

    std::string getNombre() {
        return this->nombre;
    }

    std::string getApellido() {
        return this->apellido;
    }

    std::string getNombreCompleto() {
        return this->nombre + " " + this->apellido;
    }
};

class Libro {
private:
    std::string titulo;
    Autor autor;
public:
    Libro(std::string titulo, Autor autor) : autor(autor) {
        this->titulo = titulo;
    }

    std::string getTitulo() {
        return this->titulo;
    }

    Autor getAutor() {
        return this->autor;
    }

    void imprimirInformacion() {
        std::cout << "Titulo: " << this->titulo << "\n";
        std::cout << "Autor: " << this->autor.getNombreCompleto() << "\n";
    }
};

int main() {
    Autor autor("J.K.", "Rowling");
    Libro libro("Harry Potter", autor);

    libro.imprimirInformacion();

    return 0;
}