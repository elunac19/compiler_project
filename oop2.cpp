#include <iostream>
#include <string>

class Animal {
protected:
    std::string nombre;
public:
    Animal(std::string _nombre) : nombre(_nombre) {}
    virtual void hablar() {
        std::cout << nombre << " hace un sonido genérico." << std::endl;
    }
};

class Perro : public Animal {
public:
    Perro(std::string _nombre) : Animal(_nombre) {}
    void hablar() override {
        std::cout << nombre << " dice: ¡Guau!" << std::endl;
    }
};

class Gato : public Animal {
public:
    Gato(std::string _nombre) : Animal(_nombre) {}
    void hablar() override {
        std::cout << nombre << " dice: ¡Miau!" << std::endl;
    }
};

int main() {
    Animal* a1 = new Perro("Firulais");
    Animal* a2 = new Gato("Michi");

    Perro p("Firulais");
    Gato g("Michi");

    p.hablar();
    g.hablar();

    a1->hablar();
    a2->hablar();

    delete a1;
    delete a2;

    return 0;
}
