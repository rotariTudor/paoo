#pragma once
// Item 4: Make sure that objects are initialized before they're used.
#include <string>
#include "common.hpp"

namespace item04 {

// 1. Tipurile built-in NU sunt initializate automat.
struct RawPoint  { int x; int y; };           // valori nedefinite daca nu initializezi
struct SafePoint { int x{0}; int y{0}; };     // default member initializers (C++11)

// 2. Atribuire in corpul constructorului vs. lista de initializare.
//    Atribuirea = membrii sunt mai intai default-construiti, apoi atribuiti (munca dubla).
class BadEntry {
public:
    BadEntry(const std::string& name, const Noisy& address) {
        theName_ = name;               // default ctor + assignment
        theAddress_ = address;         // default ctor + COPY assignment
        numTimesConsulted_ = 0;
    }
private:
    std::string theName_;
    Noisy       theAddress_;
    int         numTimesConsulted_;
};

class GoodEntry {
public:
    GoodEntry(const std::string& name, const Noisy& address)
        : theName_(name),              // o singura operatie: copy construct
          theAddress_(address),
          numTimesConsulted_(0) {}
    // Constructorul implicit: initializam explicit, chiar si "din nimic".
    GoodEntry() : theName_(), theAddress_(), numTimesConsulted_(0) {}
private:
    std::string theName_;
    Noisy       theAddress_;
    int         numTimesConsulted_;
};

// 3. Membrii const si referintele TREBUIE initializati in lista de initializare.
class Config {
public:
    Config(const std::string& name, int& counter)
        : name_(name), counter_(counter) {}
    // Config(...) { name_ = name; }  // EROARE de compilare: const/ref nu se pot atribui
    void bump() { ++counter_; }
    const std::string& name() const { return name_; }
private:
    const std::string name_;
    int&              counter_;
};

// 4. Constructori care delega (C++11): o singura cale de initializare.
class Widget {
public:
    Widget() : Widget("fara-nume", 0) {}
    explicit Widget(const std::string& n) : Widget(n, 0) {}
    Widget(const std::string& n, int prio) : name_(n), priority_(prio) {}
    void print() const;
private:
    std::string name_;
    int         priority_;
};

// 5. Ordinea initializarii = ORDINEA DECLARARII, nu ordinea din lista!
class OrderDemo {
public:
    OrderDemo();
private:
    Noisy first_;    // declarat primul  => initializat primul
    Noisy second_;
};

// 6. Ordinea initializarii obiectelor statice din unitati de traducere diferite
//    este NESPECIFICATA. Solutia: Singleton Meyers (static local intr-o functie).
class FileSystem {
public:
    FileSystem();
    std::size_t numDisks() const { return numDisks_; }
private:
    std::size_t numDisks_;
};

FileSystem& tfs();   // inlocuieste "extern FileSystem tfs;"

class Directory {
public:
    Directory();
    std::size_t disksSeen() const { return disks_; }
private:
    std::size_t disks_;
};

Directory& tempDir();

void run_demo();

}  // namespace item04
