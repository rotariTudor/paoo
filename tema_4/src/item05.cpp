#include "item05.hpp"
#include <iostream>
#include <memory>

namespace item05 {

void run_demo() {
    section("Item 5: ce functii scrie si apeleaza compilatorul in tacere");

    sub("1. Empty: toate cele 6 functii exista (verificate cu static_assert la compilare)");
    Empty e1;           // ctor implicit
    Empty e2(e1);       // copy ctor
    e1 = e2;            // copy assignment
    std::cout << "      sizeof(Empty) = " << sizeof(Empty) << '\n';

    sub("2. Person p1: ctor + 2 membri Noisy construiti");
    Person p1("Ion", "Cluj");
    sub("2. Person p2(p1): copy ctor GENERAT apeleaza copy ctor-ul fiecarui membru");
    Person p2(p1);
    sub("2. p2 = p1: operator= GENERAT apeleaza operator= pentru fiecare membru");
    p2 = p1;
    sub("2. Person p3(std::move(p1)): move ctor GENERAT muta fiecare membru");
    Person p3(std::move(p1));

    sub("6a. WithDtor: destructor declarat => std::move cade pe COPIERE");
    {
        WithDtor a("A");
        WithDtor b(std::move(a));
    }
    sub("6b. WithoutDtor: regula lui zero => std::move chiar MUTA");
    {
        WithoutDtor a("B");
        WithoutDtor b(std::move(a));
    }

    sub("7. Buffer: Regula celor 5 (copiere in adancime, mutare)");
    {
        Buffer b1(4);
        b1.data()[0] = 42;
        Buffer b2(b1);                      // deep copy
        b2.data()[0] = 99;
        std::cout << "      b1[0]=" << b1.data()[0] << " b2[0]=" << b2.data()[0]
                  << " (adrese diferite: " << (b1.data() != b2.data()) << ")\n";
        Buffer b3(std::move(b1));           // move
        std::cout << "      dupa move: b1.size()=" << b1.size()
                  << " b3.size()=" << b3.size() << '\n';
    }

    sub("8. Destructor virtual in baza polimorfica");
    {
        std::unique_ptr<PolyBase> p = std::make_unique<PolyDerived>();
    }
    std::cout << "\n  -- sfarsit demo item 5 (se distrug obiectele locale)\n";
}

}  // namespace item05
