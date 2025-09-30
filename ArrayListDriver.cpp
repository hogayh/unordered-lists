/**
* @file ArrayListDriver.cpp
 * @brief Demonstrates ArrayADTList with int and Customer types.
 */
#include <iostream>
#include <fstream>
#include "ArrayADTList.h"
#include "Customer.h"

int main() {
    // ---- Primitive demo: int -----
    ArrayADTList<int> ints(16);
    ints.putItem(10);
    ints.putItem(20);
    ints.putItem(30);

    std::cout << "[Array<int>] len=" << ints.getLength() << " : ";
    for (auto it = ints.begin(); it != ints.end(); ++it) std::cout << *it << " ";
    std::cout << "\n";

    bool found = false;
    ints.getItem(20, found);
    std::cout << "find 20 -> " << (found ? "found" : "not found") << "\n";

    // ---- Customer demo ----
    ArrayADTList<Customer> customers(1024);
    std::ifstream fin("Customers.txt");
    if (fin) {
        Customer c;
        while (fin >> c) customers.putItem(c);
    }

    std::cout << "[Array<Customer>] loaded=" << customers.getLength() << "\n";
    for (auto it = customers.begin(); it != customers.end(); ++it) {
        std::cout << *it << "\n";
    }
    return 0;
}
