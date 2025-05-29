#include <iostream>
#include <string>

struct Remote {
    std::string brand;
    int model;
    bool power;
    
    void powerOn() {
        power = true;
        std::cout << "Remote is ON\n";
    }
    
    void powerOff() {
        power = false;
        std::cout << "Remote is OFF\n";
    }

    void setBrand(std::string b) {
        brand = b;
    }

    void setModel(int m) {
        model = m;
    }
};

struct TV {
    Remote r;

    void setRemote(Remote rem) {
        r = rem;
    }

    void turnOn() {
        r.powerOn();
    }

    void turnOff() {
        r.powerOff();
    }
};

int main() {
    TV myTV;

    Remote myRemote;
    myRemote.setBrand("Samsung");
    myRemote.setModel(2020);

    myTV.setRemote(myRemote);

    myTV.turnOn();
    myTV.turnOff();

    return 0;
}