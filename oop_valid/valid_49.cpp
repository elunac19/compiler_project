#include <iostream>
#include <string>

class Device {
private:
    std::string name;
    bool powerStatus;

public:
    // Constructor
    Device(std::string n) : name(n), powerStatus(false) {}

    // Método para encender y apagar el dispositivo
    void togglePower() {
        powerStatus = !powerStatus;
        std::cout << name << " power " << (powerStatus ? "On" : "Off") << std::endl;
    }

    // Método para obtener el estado de energía
    bool getPowerStatus() {
        return powerStatus;
    }

    std::string getName() {
        return name;
    }
};

class RemoteControl {
private:
    Device* device;

public:
    // Constructor
    RemoteControl(Device* d) : device(d) {}

    // Método para encender y apagar un dispositivo
    void togglePower() {
        if (device != nullptr) {
            device->togglePower();
        }
    }

    // Método para comprobar el estado de energía del dispositivo
    void checkPowerStatus() {
        if (device != nullptr) {
            std::cout << device->getName() << " power " << (device->getPowerStatus() ? "On" : "Off") << std::endl;
        }
    }
};


int main() {
    Device tv("TV");
    Device radio("Radio");

    RemoteControl rc(&tv);

    rc.togglePower();
    rc.checkPowerStatus();

    rc = RemoteControl(&radio);

    rc.togglePower();
    rc.checkPowerStatus();

    return 0;
}