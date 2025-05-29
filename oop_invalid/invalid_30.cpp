#include<iostream>
#include<string>

struct Libro {
    std::string titulo;
    std::string autor;

    void setTitulo(std::string t) {
        titulo = t;
    }

    void setAutor(std::string a) {
        autor = a;
    }
    
    std::string getTitulo() {
        return titulo;
    }
    
    std::string getAutor() {
        return autor;
    }
};

int main() {
    Libro libro;
    libro.setTitulo("1984");
    libro.setAutor("George Orwell");

    std::cout << "Titulo: " << libro.getTitulo() << "\n";
    std::cout << "Autor: " << libro.getAutor() << "\n";
    return 0;
}