#pragma once
// Item 5: Know what functions C++ silently writes and calls.
#include <algorithm>
#include <cstddef>
#include <string>
#include <type_traits>
#include "common.hpp"

namespace item05 {

// 1. O clasa "goala" nu e chiar goala. Compilatorul scrie (la nevoie):
//      Empty();  Empty(const Empty&);  Empty(Empty&&);   ~Empty();
//      Empty& operator=(const Empty&);  Empty& operator=(Empty&&);
class Empty {};

static_assert(std::is_default_constructible_v<Empty>,   "ctor implicit");
static_assert(std::is_copy_constructible_v<Empty>,      "copy ctor");
static_assert(std::is_move_constructible_v<Empty>,      "move ctor");
static_assert(std::is_copy_assignable_v<Empty>,         "copy assignment");
static_assert(std::is_move_assignable_v<Empty>,         "move assignment");
static_assert(std::is_destructible_v<Empty>,            "destructor");
static_assert(!std::has_virtual_destructor_v<Empty>,    "destructorul generat NU e virtual");

// 2. Functiile generate apeleaza functiile corespunzatoare ale membrilor.
class Person {
public:
    Person(std::string n, std::string a) : name_(std::move(n)), address_(std::move(a)) {}
private:
    Noisy name_;
    Noisy address_;
};

// 3. Daca declari TU orice constructor, compilatorul NU mai scrie ctorul implicit.
class NoDefault {
public:
    explicit NoDefault(int v) : v_(v) {}
private:
    int v_;
};
static_assert(!std::is_default_constructible_v<NoDefault>, "NoDefault nu are ctor implicit");
static_assert(std::is_copy_constructible_v<NoDefault>,     "dar copy ctor exista");

// 4. Operatorul de atribuire NU e generat cand ar fi ilegal:
//    membri referinta sau const.
template <typename T>
class NamedObject {
public:
    NamedObject(std::string& name, const T& value) : nameValue(name), objectValue(value) {}
private:
    std::string& nameValue;     // referinta  -> nu poate fi "re-legata"
    const T      objectValue;   // const      -> nu poate fi modificat
};
static_assert(std::is_copy_constructible_v<NamedObject<int>>,  "copierea merge");
static_assert(!std::is_copy_assignable_v<NamedObject<int>>,    "atribuirea e delete-ata implicit");
// NamedObject<int> p(a, 2), s(b, 36);  p = s;   // EROARE de compilare
//   (C++98: trebuia sa definesti singur operator=; in C++11 compilatorul il marcheaza deleted.)

// 5. Daca baza declara operator= privat/deleted, derivata nu mai primeste operator= generat.
class SealedBase {
public:
    SealedBase() = default;
    SealedBase& operator=(const SealedBase&) = delete;
};
class FromSealed : public SealedBase { int x_ = 0; };
static_assert(!std::is_copy_assignable_v<FromSealed>, "derivata nu e atribuibila");

// 6. Regula celor 5: un destructor declarat de utilizator SUPRIMA mutarea generata
//    (copierea ramane generata - dar e depreciata). Mutarea "cade" silentios pe copiere!
class WithDtor {
public:
    explicit WithDtor(std::string s) : n_(std::move(s)) {}
    ~WithDtor() { std::cout << "      ~WithDtor\n"; }   // declarat => NU exista move
private:
    Noisy n_;
};

class WithoutDtor {                   // Regula lui zero: nu declara nimic
public:
    explicit WithoutDtor(std::string s) : n_(std::move(s)) {}
private:
    Noisy n_;
};

// 7. Cand compilatorul NU ajunge: resurse brute (pointeri). Copierea implicita ar face
//    "shallow copy" (doi pointeri catre aceeasi memorie => double delete).
//    Solutie: Regula celor 5, scrise explicit.
class Buffer {
public:
    explicit Buffer(std::size_t n) : size_(n), data_(new int[n]()) {}
    ~Buffer() { delete[] data_; }

    Buffer(const Buffer& o) : size_(o.size_), data_(new int[o.size_]) {
        std::copy(o.data_, o.data_ + size_, data_);
        std::cout << "      Buffer: deep COPY\n";
    }
    Buffer& operator=(const Buffer& o) {
        if (this != &o) {
            Buffer tmp(o);                  // copy-and-swap
            std::swap(size_, tmp.size_);
            std::swap(data_, tmp.data_);
        }
        return *this;
    }
    Buffer(Buffer&& o) noexcept : size_(o.size_), data_(o.data_) {
        o.size_ = 0; o.data_ = nullptr;
        std::cout << "      Buffer: MOVE\n";
    }
    Buffer& operator=(Buffer&& o) noexcept {
        if (this != &o) {
            delete[] data_;
            size_ = o.size_; data_ = o.data_;
            o.size_ = 0; o.data_ = nullptr;
        }
        return *this;
    }
    int*        data()       { return data_; }
    const int*  data() const { return data_; }
    std::size_t size() const { return size_; }
private:
    std::size_t size_;
    int*        data_;
};

// 8. Baza polimorfica: destructorul generat nu e virtual => declara-l virtual.
struct PolyBase {
    virtual ~PolyBase() { std::cout << "      ~PolyBase\n"; }
};
struct PolyDerived : PolyBase {
    ~PolyDerived() override { std::cout << "      ~PolyDerived\n"; }
};

void run_demo();

}  // namespace item05
