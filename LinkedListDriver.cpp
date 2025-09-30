/**
* @file LinkedListDriver.cpp
 * @brief Demonstrates LinkedADTList with std::string and Customer types.
 */
#include <iostream>
#include <fstream>
#include <string>
#include "LinkedADTList.h"
#include "Customer.h"

int main() {
    // ---- Primitive demo: std::string ----
    LinkedADTList<std::string> words;
    words.putItem("apple");
    words.putItem("banana");
    words.putItem("cherry");

    std::cout << "[Linked<string>] len=" << words.getLength() << " : ";
    for (auto it = words.begin(); it != words.end(); ++it) std::cout << *it << " ";
    std::cout << "\n";

    bool found = false;
    words.getItem(std::string("banana"), found);
    std::cout << "[Linked<string>] find 'banana' -> " << (found ? "found" : "not found") << "\n";

    // ---- Customer demo ----
    LinkedADTList<Customer> custs;
    std::ifstream fin("Customers.txt");
    if (fin) {
        Customer c;
        while (fin >> c) custs.putItem(c);
    }

    std::cout << "[Linked<Customer>] loaded=" << custs.getLength() << "\n";
    for (auto it = custs.begin(); it != custs.end(); ++it) {
        std::cout << *it << "\n";
    }
    return 0;
}

