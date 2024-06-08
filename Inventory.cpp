
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

class Product {
public:
    std::string id;
    std::string name;
    int quantity;
    double price;

    Product(std::string id, std::string name, int quantity, double price)
        : id(id), name(name), quantity(quantity), price(price) {}

    void display() const {
        std::cout << "ID: " << id << "\nName: " << name
                  << "\nQuantity: " << quantity << "\nPrice: $" << price << std::endl;
    }
};

#endif // PRODUCT_H
```

### Inventory.h
This file defines the `Inventory` class.

```cpp
#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <map>
#include <fstream>
#include <iomanip>
#include "PRODUCT.H"

class Inventory {
private:
    std::map<std::string, Product> products;

public:
    // Add a new product to the inventory
    void addProduct(const Product& product) {
        products[product.id] = product;
    }

    // Update the quantity of an existing product
    void updateQuantity(const std::string& id, int quantity) {
        if (products.find(id) != products.end()) {
            products[id].quantity += quantity;
        } else {
            std::cout << "Product not found." << std::endl;
        }
    }

    // Display details of all products
    void displayAllProducts() const {
        for (const auto& pair : products) {
            pair.second.display();
            std::cout << "-------------------" << std::endl;
        }
    }

    // Generate and save a report of all products
    void generateReport(const std::string& filename) const {
        std::ofstream outFile(filename);

        if (!outFile) {
            std::cerr << "Could not open file for writing!" << std::endl;
            return;
        }

        outFile << std::left << std::setw(10) << "ID"
                << std::setw(20) << "Name"
                << std::setw(10) << "Quantity"
                << std::setw(10) << "Price" << std::endl;

        for (const auto& pair : products) {
            const Product& product = pair.second;
            outFile << std::left << std::setw(10) << product.id
                    << std::setw(20) << product.name
                    << std::setw(10) << product.quantity
                    << std::setw(10) << product.price << std::endl;
        }

        outFile.close();
    }

    // Load products from a file
    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);

        if (!inFile) {
            std::cerr << "Could not open file for reading!" << std::endl;
            return;
        }

        std::string id, name;
        int quantity;
        double price;

        while (inFile >> id >> name >> quantity >> price) {
            Product product(id, name, quantity, price);
            addProduct(product);
        }

        inFile.close();
    }

    // Save products to a file
    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);

        if (!outFile) {
            std::cerr << "Could not open file for writing!" << std::endl;
            return;
        }

        for (const auto& pair : products) {
            const Product& product = pair.second;
            outFile << product.id << " " << product.name << " "
                    << product.quantity << " " << product.price << std::endl;
        }

        outFile.close();
    }
};

#endif // INVENTORY_H



#include <iostream>
#include "INVENTORY.H"

void displayMenu() {
    std::cout << "\nInventory Management System\n";
    std::cout << "1. Add Product\n";
    std::cout << "2. Update Product Quantity\n";
    std::cout << "3. Display All Products\n";
    std::cout << "4. Generate Report\n";
    std::cout << "5. Load from File\n";
    std::cout << "6. Save to File\n";
    std::cout << "7. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    Inventory inventory;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string id, name;
                int quantity;
                double price;

                std::cout << "Enter Product ID: ";
                std::cin >> id;
                std::cout << "Enter Product Name: ";
                std::cin >> name;
                std::cout << "Enter Product Quantity: ";
                std::cin >> quantity;
                std::cout << "Enter Product Price: ";
                std::cin >> price;

                Product product(id, name, quantity, price);
                inventory.addProduct(product);
                break;
            }
            case 2: {
                std::string id;
                int quantity;

                std::cout << "Enter Product ID: ";
                std::cin >> id;
                std::cout << "Enter Quantity to Update: ";
                std::cin >> quantity;

                inventory.updateQuantity(id, quantity);
                break;
            }
            case 3:
                inventory.displayAllProducts();
                break;
            case 4: {
                std::string filename;

                std::cout << "Enter filename to save report: ";
                std::cin >> filename;

                inventory.generateReport(filename);
                break;
            }
            case 5: {
                std::string filename;

                std::cout << "Enter filename to load from: ";
                std::cin >> filename;

                inventory.loadFromFile(filename);
                break;
            }
            case 6: {
                std::string filename;

                std::cout << "Enter filename to save to: ";
                std::cin >> filename;

                inventory.saveToFile(filename);
                break;
            }
            case 7:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice, please try again." << std::endl;
        }
    } while (choice != 7);

    return 0;
}
