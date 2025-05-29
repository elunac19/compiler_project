#include <iostream>

class Sensor {
private:
    double temperatura;
public:
    Sensor(double temp = 36.0) : temperatura(temp) {}

    void setTemperatura(double temp) {
        this->temperatura = temp;
    }

    double getTemperatura() const {
        return this->temperatura;
    }
};

class Dispositivo {
private:
    Sensor sensor;
public:
    Dispositivo(Sensor s) : sensor(s) {}

    void leerSensor() {
        std::cout << "La temperatura del sensor es: " << sensor.getTemperatura() << " grados Celsius" << std::endl;
    }

    void ajustarSensor(double temp) {
        sensor.setTemperatura(temp);
    }
};

int main() {
    Sensor s;
    Dispositivo d(s);
    d.leerSensor();
    d.ajustarSensor(37.0);
    d.leerSensor();
    return 0;
}