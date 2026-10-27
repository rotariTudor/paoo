#include <thermo/naive_thermometer.hpp>
#include <thermo/thermometer.hpp>

#include <cstring>
#include <iostream>

static void title(const char* text) {
    std::cout << "\n=== " << text << " ===\n";
}

// p2 p3
static void demoEncapsulation() {
    title("Incapsulare + initializare in constructor");
    Thermometer t1("camera", 21.5);
    Thermometer t2("balcon", 8.0);
    std::cout << "  " << t1.label() << " (id " << t1.id() << "): " << t1.celsius() << "\n";
    std::cout << "  " << t2.label() << " (id " << t2.id() << "): " << t2.celsius() << "\n";
    std::cout << "  setCelsius(25.0)   -> " << t1.setCelsius(25.0)
              << ", acum " << t1.celsius() << "\n";
    std::cout << "  setCelsius(-500.0) -> " << t1.setCelsius(-500.0)
              << ", ramane " << t1.celsius() << "\n";
}

//p4
static void demoDestructor() {
    title("Destructor: eliberarea heap-ului");
    {
        std::cout << " bloc cu obiect local:\n";
        Thermometer local("local", 10.0);
    }   // destructorul ruleaza la acolada de inchidere
    std::cout << " dupa bloc\n";

    std::cout << " obiect creat cu new:\n";
    Thermometer* p = new Thermometer("dinamic", 30.0);
    delete p;   // destructorul ruleaza la delete
    p = nullptr;
}

//ce se intampla FARA copy constructor propriu
static void demoShallowCopy(bool crash) {
    title("Fara copy constructor propriu: shallow copy");
    if (crash) {
        std::cout << " Double delete REAL, programul se va opri:\n";
        NaiveThermometer a(21.5);
        NaiveThermometer b = a;   // copy ctor generat de compilator
        std::cout << "  a: " << a.address() << ", b: " << b.address() << std::endl;
        return;   // ~b si ~a sterg aceeasi adresa
    }
    NaiveThermometer a(21.5);
    NaiveThermometer b = a;   // copy ctor generat de compilator (shallow)
    std::cout << "  adresa a: " << a.address() << "\n"
              << "  adresa b: " << b.address() << "  <- ACEEASI adresa\n";
    a.set(99.0);
    std::cout << "  dupa a.set(99.0): b.celsius() = " << b.celsius()
              << "  <- b s-a schimbat fara sa-l atingem\n";
    std::cout << "  La final ambele destructoare ar sterge aceeasi adresa\n"
                 "  (double delete). Ca demo-ul sa mearga mai departe,\n"
                 "  b renunta manual la pointer. Crash real: ./thermo --crash\n";
    b.abandon();
}

//copy constructor propriu
static void demoDeepCopy() {
    title("Cu copy constructor propriu: deep copy");
    Thermometer a("a", 21.5);
    Thermometer b = a;
    std::cout << "  adresa a: " << a.address() << "\n"
              << "  adresa b: " << b.address() << "  <- adrese diferite\n";
    a.setCelsius(99.0);
    std::cout << "  dupa a.setCelsius(99.0): a = " << a.celsius()
              << ", b = " << b.celsius() << "  <- b neschimbat\n";
    std::cout << "  La final fiecare obiect sterge propriul double.\n";
}

int main(int argc, char* argv[]) {
    bool crash = argc > 1 && std::strcmp(argv[1], "--crash") == 0;
    if (crash) {
        demoShallowCopy(true);
        return 0;
    }
    demoEncapsulation();
    demoDestructor();
    demoShallowCopy(false);
    demoDeepCopy();
    std::cout << "\n--------------------.\n";
    return 0;
}