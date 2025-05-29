#include<iostream>
#include<string>

class Duracion {
    private:
        int minutos;
        int segundos;
    
    public:
        Duracion(int m, int s) : minutos(m), segundos(s) {}
        int getMinutos() { return this->minutos; }
        int getSegundos() { return this->segundos; }
};

class Cancion {
    private:
        std::string titulo;
        Duracion duracion;
    
    public:
        Cancion(std::string t, Duracion d) : titulo(t), duracion(d) {}
        void mostrarCancion() {
            std::cout << "Titulo: " << this->titulo << std::endl;
            std::cout << "Duracion: " << this->duracion.getMinutos() << ":" << this->duracion.getSegundos() << std::endl;
        }
};

int main() {
    Duracion duracion1(3, 44);
    Cancion cancion1("Mi cancion favorita", duracion1);
    cancion1.mostrarCancion();
    return 0;
}