#include <iostream>

struct SensorDeTemperatura {
    int temperatura;

    void setTemperatura(int t) {
        temperatura = t;
    }

    int getTemperatura() {
        return temperatura;
    }
};

struct MonitorDeTemperatura {
    SensorDeTemperatura sensor;

    void setSensorT(SensorDeTemperatura s) {
        sensor = s;
    }

    void imprimirTemperatura() {
        std::cout << "La temperatura actual es: " << sensor.getTemperatura() << std::endl;
    }
};

int main() {
    SensorDeTemperatura s;
    s.setTemperatura(36);

    MonitorDeTemperatura m;
    m.setSensorT(s);
    m.imprimirTemperatura();

    return 0;
}