#ifndef THERMO_THERMOMETER_HPP
#define THERMO_THERMOMETER_HPP

#include <string>

class Thermometer {
public:
    Thermometer(const std::string& label, double celsius);
    ~Thermometer();
    Thermometer(const Thermometer& other); 


    Thermometer& operator=(const Thermometer&) = delete;

    int id() const { return id_; }
    const std::string& label() const { return label_; }
    double celsius() const { return *temperature_; }
    bool setCelsius(double celsius);
    const void* address() const { return temperature_; }

private:
    std::string label_;
    double* temperature_;
    const int id_;
};

#endif