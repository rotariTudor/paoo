#include <thermo/naive_thermometer.hpp>

#include <iostream>

NaiveThermometer::NaiveThermometer(double celsius)
    : temperature_(new double(celsius)) {
    std::cout << "  [ctor]      NaiveThermometer " << celsius
              << ", adresa " << address() << "\n";
}

NaiveThermometer::~NaiveThermometer() {
    std::cout << "  [dtor]      NaiveThermometer, delete " << address() << "\n";
    delete temperature_;
}