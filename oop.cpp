#include <iostream>
using namespace std;

class Animal {
protected:
    string nombre;
public:
    Animal(string _nombre) : nombre(_nombre) {}
    virtual void hablar() {
        cout << nombre << " hace un sonido genérico." << endl;
    }
};

class Perro : public Animal {
public:
    Perro(string _nombre) : Animal(_nombre) {}
    void hablar() override {
        cout << nombre << " dice: ¡Guau!" << endl;
    }
};

class Gato : public Animal {
public:
    Gato(string _nombre) : Animal(_nombre) {}
    void hablar() override {
        cout << nombre << " dice: ¡Miau!" << endl;
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
