#include<iostream>
#include<string>

class Resolution {
private:
    int width;
    int height;
public:
    Resolution(int w, int h) : width(w), height(h) {}

    int getWidth() {
        return this->width;
    }

    int getHeight() {
        return this->height;
    }
};

class Screen {
private:
    std::string brand;
    Resolution res;
public:
    Screen(std::string b, Resolution r) : brand(b), res(r) {}

    void displayDetails() {
        std::cout << "Brand: " << this->brand << std::endl;
        std::cout << "Resolution: " << this->res.getWidth() << "x" << this->res.getHeight() << std::endl;
    }
};

int main() {
    Resolution res(1920, 1080);
    Screen screen("Samsung", res);
    screen.displayDetails();

    return 0;
}