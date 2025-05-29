#include<iostream>
#include<string>

class Product {
private:
    std::string name;
    double price;
public:
    Product(std::string name, double price) : name(name), price(price) {}
    std::string getName() { return this->name; }
    double getPrice() { return this->price; }
};

class Order {
private:
    Product product;
    int quantity;
public:
    Order(Product product, int quantity) : product(product), quantity(quantity) {}
    double getTotalPrice() { return this->product.getPrice() * this->quantity; }
    void printOrder() {
        std::cout << "Product: " << this->product.getName() << "\n";
        std::cout << "Quantity: " << this->quantity << "\n";
        std::cout << "Total Price: " << this->getTotalPrice() << "\n";
    }
};

int main() {
    Product p1("Apple", 0.5);
    Order o1(p1, 10);
    o1.printOrder();
    return 0;
}