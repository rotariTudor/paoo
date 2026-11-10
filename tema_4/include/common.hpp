#pragma once
// Utilitare comune: o clasa "zgomotoasa" care isi afiseaza fiecare operatie
// speciala (constructor, copiere, mutare, atribuire, destructor). Ne permite
// sa VEDEM ce functii apeleaza (sau scrie) compilatorul.
#include <iostream>
#include <string>
#include <utility>

class Noisy {
public:
    Noisy() : id_("<implicit>") { log("constructor implicit"); }
    explicit Noisy(std::string id) : id_(std::move(id)) { log("constructor"); }
    Noisy(const Noisy& o) : id_(o.id_) { log("COPY constructor"); }
    Noisy(Noisy&& o) noexcept : id_(std::move(o.id_)) { log("MOVE constructor"); }
    Noisy& operator=(const Noisy& o) {
        id_ = o.id_;
        log("COPY assignment");
        return *this;
    }
    Noisy& operator=(Noisy&& o) noexcept {
        id_ = std::move(o.id_);
        log("MOVE assignment");
        return *this;
    }
    ~Noisy() { log("destructor"); }

private:
    void log(const char* what) const {
        std::cout << "      [Noisy '" << id_ << "'] " << what << '\n';
    }
    std::string id_;
};

inline void section(const char* title) {
    std::cout << "\n=== " << title << " ===\n";
}
inline void sub(const char* title) {
    std::cout << "\n  -- " << title << '\n';
}
