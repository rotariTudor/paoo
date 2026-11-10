#include "item06.hpp"
#include <iostream>
#include <utility>

namespace item06 {

bool isLucky(int number) { return number == 7; }

template <typename T>
void processPointer(T* ptr) {
    std::cout << "      processPointer: " << (ptr ? "ptr valid" : "nullptr") << '\n';
}

void run_demo() {
    section("Item 6: interzicerea explicita a functiilor generate");

    sub("1. Cele trei metode: copierea este imposibila la COMPILARE");
    HomeForSaleOld  h1;
    HomeForSaleBook h2;
    HomeForSale     h3("Str. Libertatii 5");
    (void)h1; (void)h2;
    std::cout << "      Casa (= delete): " << h3.address() << '\n';
    // HomeForSale   h4(h3);   // EROARE: use of deleted function
    // HomeForSale   h5; h5 = h3;  // EROARE
    // HomeForSaleBook h6(h2); // EROARE: copy ctor e privat in Uncopyable

    sub("2. Doar mutare (UniqueHandle)");
    UniqueHandle u1("handle");
    UniqueHandle u2(std::move(u1));
    // UniqueHandle u3(u2);    // EROARE: copiere interzisa

    sub("3. = delete pe overload-uri: isLucky");
    std::cout << "      isLucky(7) = " << std::boolalpha << isLucky(7) << '\n';
    // isLucky('a');    // EROARE: deleted
    // isLucky(true);   // EROARE: deleted
    // isLucky(3.5);    // EROARE: deleted

    sub("4. = delete pe specializari de sablon");
    int x = 5;
    processPointer(&x);
    // processPointer(static_cast<void*>(&x));  // EROARE
    // processPointer("abc");                   // EROARE: char*/const char*

    sub("5. StackOnly / HeapOnly");
    StackOnly so;                       // ok
    (void)so;
    // auto* p = new StackOnly;         // EROARE: operator new deleted
    HeapOnly* ho = HeapOnly::create();  // ok
    ho->destroy();
    // HeapOnly nope;                   // EROARE: constructor/destructor privat
    std::cout << "      ok\n";
}

}  // namespace item06
