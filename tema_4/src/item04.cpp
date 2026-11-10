#include "item04.hpp"
#include <iostream>

namespace item04 {

void Widget::print() const {
    std::cout << "      Widget{" << name_ << ", prio=" << priority_ << "}\n";
}

OrderDemo::OrderDemo()
    : first_("first"), second_("second") {}
// Chiar daca am scrie : second_("second"), first_("first")
// ordinea reala ar fi tot first_ -> second_ (compilatorul avertizeaza cu -Wreorder).
// Distrugerea se face in ordine inversa.

FileSystem::FileSystem() : numDisks_(4) {
    std::cout << "      FileSystem construit\n";
}

FileSystem& tfs() {
    static FileSystem fs;   // initializat la PRIMA apelare (thread-safe din C++11)
    return fs;
}

Directory::Directory() : disks_(tfs().numDisks()) {   // tfs() garanteaza ca exista
    std::cout << "      Directory construit\n";
}

Directory& tempDir() {
    static Directory d;
    return d;
}

void run_demo() {
    section("Item 4: initializare inainte de utilizare");

    sub("1. Tipuri built-in: initializare explicita");
    SafePoint s;
    RawPoint  r{};                // value-initialization => zero (fara {} ar fi gunoi)
    std::cout << "      SafePoint = (" << s.x << ", " << s.y << ")\n";
    std::cout << "      RawPoint{} = (" << r.x << ", " << r.y << ")\n";
    // RawPoint bad;  std::cout << bad.x;   // COMPORTAMENT NEDEFINIT

    Noisy addr("Str. Victoriei 1");

    sub("2a. Atribuire in corpul constructorului (BadEntry): default ctor + COPY assignment");
    { BadEntry b("Ana", addr); }

    sub("2b. Lista de initializare (GoodEntry): doar COPY constructor");
    { GoodEntry g("Ana", addr); }

    sub("3. Membri const / referinta (obligatoriu in lista de init)");
    {
        int counter = 0;
        Config c("cfg", counter);
        c.bump(); c.bump();
        std::cout << "      " << c.name() << ": counter = " << counter << '\n';
    }

    sub("4. Constructori care delega");
    Widget().print();
    Widget("alfa").print();
    Widget("beta", 7).print();

    sub("5. Ordinea initializarii = ordinea declararii");
    { OrderDemo o; }

    sub("6. Singleton Meyers: tempDir() declanseaza corect tfs() inaintea sa");
    const std::size_t seen = tempDir().disksSeen();   // intai construire, apoi afisare
    std::cout << "      Directory vede " << seen << " discuri\n";
}

}  // namespace item04
