#include <iostream>
#include <iomanip>

class Time {
private:
    int hours;
    int minutes;
    int seconds;
public:
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}
    
    void setHours(int h) {
        hours = h;
    }

    void setMinutes(int m) {
        minutes = m;
    }

    void setSeconds(int s) {
        seconds = s;
    }

    int getHours() const {
        return hours;
    }

    int getMinutes() const {
        return minutes;
    }

    int getSeconds() const {
        return seconds;
    }
};

class DigitalClock {
private:
    Time time;
public:
    DigitalClock(int h, int m, int s) : time(h, m, s) {}

    void setTime(int h, int m, int s) {
        time.setHours(h);
        time.setMinutes(m);
        time.setSeconds(s);
    }

    void displayTime() const {
        std::cout << std::setw(2) << std::setfill('0') << time.getHours() << ":"
                  << std::setw(2) << std::setfill('0') << time.getMinutes() << ":"
                  << std::setw(2) << std::setfill('0') << time.getSeconds() << std::endl;
    }
};

int main() {
    DigitalClock clock(12, 30, 45);
    clock.displayTime();

    clock.setTime(23, 59, 59);
    clock.displayTime();

    return 0;
}