#include <thermo/thermometer.hpp>

#include <iostream>

namespace {
const double kAbsoluteZero = -273.15;
int nextId = 1;
}

Thermometer::Thermometer(const std::string& label, double celsius)
    : label_(label), temperature_(new double(celsius)), id_(nextId++) {
    std::cout << "  [ctor]      #" << id_ << " " << label_
              << ", valoare " << celsius << ", adresa " << address() << "\n";
}

//destructorul elibereaza ce a alocat constructorul.
Thermometer::~Thermometer() {
    std::cout << "  [dtor]      #" << id_ << " " << label_
              << ", delete " << address() << "\n";
    delete temperature_;
}

//deep copy, nu copiem adresa ci un obiect nou
Thermometer::Thermometer(const Thermometer& other)
    : label_(other.label_ + "_copy"),
      temperature_(new double(*other.temperature_)),
      id_(nextId++) {
    std::cout << "  [copy ctor] #" << id_ << " " << label_ << " din #"
              << other.id_ << ", adresa noua " << address() << "\n";
}

bool Thermometer::setCelsius(double celsius) {
    if (celsius < kAbsoluteZero) {
        return false;
    }
    *temperature_ = celsius;
    return true;
}