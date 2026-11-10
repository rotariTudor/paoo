//compile - g++ -std=c++17 -Wall -Wextra -Wreorder main.cpp -o demo
//run - ./demo
#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

// ITEM 4: initializeaza obiectele inainte de folosire
namespace item4 {

// GRESIT: asignare in corpul constructorului
class BadEntry {
public:
    BadEntry(const string& name) {
        theName = name;
        numTimesConsulted = 0;
    }
private:
    string theName;
    int numTimesConsulted;
};

// CORECT: lista de initializare
class GoodEntry {
public:
    GoodEntry(const string& name) : theName(name), numTimesConsulted(0) {}
    int consulted() const { return numTimesConsulted; }
private:
    string theName;
    int numTimesConsulted;
};

// Ordinea initializarii = ordinea declararii membrilor
class Array {
public:
    Array(int low, int high)
        : lowerBound(low), upperBound(high), size(high - low + 1) {}
    int getSize() const { return size; }
private:
    int lowerBound;
    int upperBound;
    int size;   // depinde de primii doi, deci e declarat ultimul
};

// Singleton Meyers: obiect static local, construit la primul apel
class FileSystem {
public:
    FileSystem() { cout << "  [FileSystem construit]\n"; }
    size_t numDisks() const { return 4; }
};

FileSystem& tfs() {
    static FileSystem fs;
    return fs;
}

class Directory {
public:
    Directory() {
        size_t n = tfs().numDisks();
        cout << "  [Directory construit] discuri: " << n << "\n";
    }
};

Directory& tempDir() {
    static Directory td;
    return td;
}

void run() {
    cout << "=== ITEM 4: initializare ===\n";

    int y = 0;   // tipurile built-in se initializeaza manual
    cout << "  y = " << y << "\n";

    GoodEntry e("Ion");
    cout << "  GoodEntry::consulted() = " << e.consulted() << "\n";

    Array a(3, 10);
    cout << "  Array size = " << a.getSize() << "\n";

    cout << "  Apel tempDir():\n";
    tempDir();
}

}


// ITEM 5: functiile pe care C++ le scrie si le apeleaza silentios
namespace item5 {

class Empty {};   // primeste: ctor implicit, copy ctor, operator=, destructor

class Tracer {
public:
    Tracer()                         { cout << "  Tracer()\n"; }
    Tracer(const Tracer&)            { cout << "  Tracer(const Tracer&)\n"; }
    Tracer& operator=(const Tracer&) { cout << "  Tracer::operator=\n"; return *this; }
    ~Tracer()                        { cout << "  ~Tracer()\n"; }
};

class Holder {
    Tracer t;   // functiile generate copiaza membru cu membru
};

// Referinta si const => compilatorul nu genereaza operator=
template<typename T>
class NamedObject {
public:
    NamedObject(string& name, const T& val) : nameValue(name), objectValue(val) {}
private:
    string& nameValue;
    const T objectValue;
};

// Destructorul generat nu e virtual => il declari tu in clasa de baza
class Base {
public:
    virtual ~Base() { cout << "  ~Base()\n"; }
};
class Derived : public Base {
public:
    ~Derived() override { cout << "  ~Derived()\n"; }
};

void run() {
    cout << "\n=== ITEM 5: functii generate de compilator ===\n";

    static_assert(is_default_constructible<Empty>::value, "default ctor");
    static_assert(is_copy_constructible<Empty>::value,    "copy ctor");
    static_assert(is_copy_assignable<Empty>::value,       "copy assignment");
    static_assert(is_destructible<Empty>::value,          "destructor");

    cout << " Holder h1:\n";
    Holder h1;
    cout << " Holder h2(h1):\n";
    Holder h2(h1);
    cout << " h2 = h1:\n";
    h2 = h1;

    static_assert(!is_copy_assignable<NamedObject<int>>::value,
                  "membri ref/const => fara operator= generat");
    cout << " NamedObject<int> nu are copy assignment\n";

    cout << " Destructor virtual:\n";
    Base* p = new Derived;
    delete p;

    cout << " iesire din scope (destructori generati pentru h2, h1):\n";
}

}


// ITEM 6: interzice explicit functiile generate pe care nu le vrei
namespace item6 {

// Varianta din carte: clasa de baza Uncopyable
class Uncopyable {
protected:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

class HomeForSaleBase : private Uncopyable {
public:
    HomeForSaleBase() {}
};

// Varianta moderna: = delete
class HomeForSale {
public:
    HomeForSale(string adr = "necunoscuta") : address(move(adr)) {}
    HomeForSale(const HomeForSale&) = delete;
    HomeForSale& operator=(const HomeForSale&) = delete;
    const string& getAddress() const { return address; }
private:
    string address;
};

void run() {
    cout << "\n=== ITEM 6: interzicerea functiilor generate ===\n";

    HomeForSale h1("Str. Libertatii 10");
    cout << "  h1 la adresa: " << h1.getAddress() << "\n";

    // HomeForSale h2(h1);   // eroare: use of deleted function

    static_assert(!is_copy_constructible<HomeForSale>::value,     "= delete");
    static_assert(!is_copy_assignable<HomeForSale>::value,        "= delete");
    static_assert(!is_copy_constructible<HomeForSaleBase>::value, "Uncopyable");
    static_assert(!is_copy_assignable<HomeForSaleBase>::value,    "Uncopyable");

    cout << "  Copierea este interzisa in ambele variante\n";
}

} // namespace item6


int main() {
    item4::run();
    item5::run();
    item6::run();
    return 0;
}