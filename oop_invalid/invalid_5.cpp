#include <iostream>
#include <string>

struct Libro {
    std::string titulo;
    std::string autor;
    void setTitulo(std::string t) { titulo = t; }
    void setAutor(std::string a) { autor = a; }
};

int main() {
    Libro libros[5];

    for(int i=0; i<5; i++){
        libros[i].setTitulo("Titulo " + std::to_string(i+1));
        libros[i].setAutor("Autor " + std::to_string(i+1));
    }

    for(int i=0; i<5; i++){
        std::cout << "Libro " << i+1 << ": " << libros[i].titulo << " por " << libros[i].autor << std::endl;
    }

    return 0;
}