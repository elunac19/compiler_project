#include<iostream>
#include<string>

class Animal {
private:
    std::string nombre;
    std::string sonido;
public:
    Animal(std::string nombre, std::string sonido) {
        this->nombre = nombre;
        this->sonido = sonido;
    }
    std::string getNombre() {
        return nombre;
    }
    std::string getSonido() {
        return sonido;
    }
};

class Zoo {
private:
    Animal* animales[39];
    int numAnimales;
public:
    Zoo() {
        numAnimales = 0;
    }
    void agregarAnimal(Animal* animal) {
        if(numAnimales < 39) {
            animales[numAnimales] = animal;
            numAnimales++;
        } else {
            std::cout << "El zoo está lleno." << std::endl;
        }
    }
    void hacerSonarAnimales() {
        for(int i = 0; i < numAnimales; i++) {
            std::cout << animales[i]->getNombre() << " hace " << animales[i]->getSonido() << "." << std::endl;
        }
    }
};

int main() {
    Zoo zoo;
    zoo.agregarAnimal(new Animal("León", "rugido"));
    zoo.agregarAnimal(new Animal("Perro", "ladrido"));
    zoo.hacerSonarAnimales();
    return 0;
}