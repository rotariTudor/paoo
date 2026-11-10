#include <thermo/naive_thermometer.hpp>
#include <thermo/thermometer.hpp>

#include <iostream>

// Punctele 2 si 3
void incapsulare() {
    std::cout << "\n--- Incapsulare + constructor ---\n";
    Thermometer t("camera", 21.5);
    std::cout << "temperatura: " << t.celsius() << "\n";

    t.setCelsius(25.0);     // valoare valida, se accepta
    std::cout << "dupa setCelsius(25): " << t.celsius() << "\n";

    t.setCelsius(-500.0);   // sub zero absolut, se refuza
    std::cout << "dupa setCelsius(-500): " << t.celsius() << "\n";
}

// Punctul 4: destructor
void destructor() {
    std::cout << "\n--- Destructor ---\n";
    {
        Thermometer t("local", 10.0);
        std::cout << "in bloc\n";
    }   // aici se apeleaza destructorul
    std::cout << "dupa bloc\n";
}

// Punctul 5
void copiereGresita() {
    std::cout << "\n--- Fara copy constructor: shallow copy ---\n";
    NaiveThermometer a(21.5);
    NaiveThermometer b = a;   // se copiaza doar adresa

    std::cout << "adresa a: " << a.address() << "\n";
    std::cout << "adresa b: " << b.address() << "  <- aceeasi\n";

    a.set(99.0);
    std::cout << "b.celsius() = " << b.celsius() << "  <- s-a schimbat si b\n";

    b.abandon();   // doar ca sa nu crape programul (altfel: double delete)
}

void copiereCorecta() {
    std::cout << "\n--- Cu copy constructor: deep copy ---\n";
    Thermometer a("a", 21.5);
    Thermometer b = a;   // se apeleaza copy constructorul nostru

    std::cout << "adresa a: " << a.address() << "\n";
    std::cout << "adresa b: " << b.address() << "  <- diferita\n";

    a.setCelsius(99.0);
    std::cout << "a = " << a.celsius() << ", b = " << b.celsius()
              << "  <- b a ramas neschimbat\n";
}

int main() {
    incapsulare();
    destructor();
    copiereGresita();
    copiereCorecta();
    return 0;
}