#include<iostream>
#include<string>
#include<vector>

struct Product {
    std::string name;
    double price;
};

struct Invoice {
    std::vector<Product> products;

    void addProduct(Product product) {
        products.push_back(product);
    }

    double getTotal() {
        double total = 0;
        for(int i = 0; i < products.size(); i++) {
            total += products[i].price;
        }
        return total;
    }
};

int main() {
    Invoice invoice;

    Product product1;
    product1.name = "Product 1";
    product1.price = 12.99;

    Product product2;
    product2.name = "Product 2";
    product2.price = 15.99;

    invoice.addProduct(product1);
    invoice.addProduct(product2);

    std::cout << "Total: " << invoice.getTotal() << std::endl;

    return 0;
}