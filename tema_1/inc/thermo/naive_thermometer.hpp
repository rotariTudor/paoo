#ifndef THERMO_NAIVE_THERMOMETER_HPP
#define THERMO_NAIVE_THERMOMETER_HPP

class NaiveThermometer {
public:
    explicit NaiveThermometer(double celsius);
    ~NaiveThermometer();

    double celsius() const { return *temperature_; }
    void set(double celsius) { *temperature_ = celsius; }
    const void* address() const { return temperature_; }

    //doar pentru demo: renunta la pointer fara sa-l stearga, ca sa putem
    // arata problema fara ca programul sa se opreasca.
    void abandon() { temperature_ = nullptr; }

private:
    double* temperature_;
};

#endif