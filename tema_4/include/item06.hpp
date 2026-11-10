#pragma once
// Item 6: Explicitly disallow the use of compiler-generated functions you do not want.
#include <memory>
#include <new>
#include <string>
#include <type_traits>
#include "common.hpp"

namespace item06 {

// ---- Metoda C++98: declarare privata, FARA definitie -------------------------
// Prietenii/membrii pot totusi apela functia => eroare doar la LINKARE.
class HomeForSaleOld {
public:
    HomeForSaleOld() {}
private:
    HomeForSaleOld(const HomeForSaleOld&);              // doar declarata
    HomeForSaleOld& operator=(const HomeForSaleOld&);   // doar declarata
};

// ---- Metoda din carte: clasa de baza Uncopyable (ca boost::noncopyable) ------
// Eroarea apare la COMPILARE, chiar daca copierea e incercata dintr-un membru/friend,
// pentru ca versiunea generata pentru derivata ar apela versiunea privata din baza.
class Uncopyable {
protected:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

class HomeForSaleBook : private Uncopyable {
public:
    HomeForSaleBook() {}
};

// ---- Metoda moderna (C++11): = delete  ---------------------------------------
// Public + deleted => cel mai clar mesaj de eroare ("use of deleted function").
class HomeForSale {
public:
    HomeForSale() = default;
    explicit HomeForSale(std::string addr) : address_(std::move(addr)) {}
    HomeForSale(const HomeForSale&)            = delete;
    HomeForSale& operator=(const HomeForSale&) = delete;
    const std::string& address() const { return address_; }
private:
    std::string address_;
};

static_assert(!std::is_copy_constructible_v<HomeForSaleOld>,   "C++98: privat");
static_assert(!std::is_copy_assignable_v<HomeForSaleOld>,      "C++98: privat");
static_assert(!std::is_copy_constructible_v<HomeForSaleBook>,  "Uncopyable");
static_assert(!std::is_copy_assignable_v<HomeForSaleBook>,     "Uncopyable");
static_assert(!std::is_copy_constructible_v<HomeForSale>,      "= delete");
static_assert(!std::is_copy_assignable_v<HomeForSale>,         "= delete");

// ---- Nici copiere, nici mutare: obiect fixat in memorie ----------------------
// (ex.: contine mutex, sau alti pointeri catre el insusi)
class Pinned {
public:
    Pinned() = default;
    Pinned(Pinned&&)                 = delete;   // sterge IMPLICIT si copierea
    Pinned& operator=(Pinned&&)      = delete;
    Pinned(const Pinned&)            = delete;   // explicit, pentru claritate
    Pinned& operator=(const Pinned&) = delete;
};
static_assert(!std::is_copy_constructible_v<Pinned> && !std::is_move_constructible_v<Pinned>,
              "Pinned nu se copiaza si nu se muta");

// ---- Doar mutare (ownership unic), ca std::unique_ptr -------------------------
class UniqueHandle {
public:
    explicit UniqueHandle(std::string name) : name_(std::move(name)) {}
    UniqueHandle(const UniqueHandle&)            = delete;
    UniqueHandle& operator=(const UniqueHandle&) = delete;
    UniqueHandle(UniqueHandle&&) noexcept            = default;
    UniqueHandle& operator=(UniqueHandle&&) noexcept = default;
private:
    Noisy name_;
};
static_assert(!std::is_copy_constructible_v<UniqueHandle>, "nu se copiaza");
static_assert(std::is_nothrow_move_constructible_v<UniqueHandle>, "se muta");

// ---- = delete pentru ORICE functie: interzice conversii implicite nedorite ----
bool isLucky(int number);
bool isLucky(char)   = delete;     // respinge 'a'
bool isLucky(bool)   = delete;     // respinge true / false
bool isLucky(double) = delete;     // respinge 3.5 (si float, prin promovare)

// ---- = delete pe sabloane: interzice anumite instantieri ----------------------
template <typename T> void processPointer(T* ptr);
template <> void processPointer<void>(void*)  = delete;   // void* nu are sens
template <> void processPointer<char>(char*)  = delete;   // c-string => altceva

// ---- Interzicerea alocarii pe heap (obiecte doar pe stiva) --------------------
class StackOnly {
public:
    StackOnly() = default;
    static void* operator new(std::size_t)   = delete;
    static void* operator new[](std::size_t) = delete;
};

// ---- Interzicerea alocarii pe stiva (destructor privat => doar heap) ---------
class HeapOnly {
public:
    static HeapOnly* create() { return new HeapOnly; }
    void destroy() { delete this; }
private:
    HeapOnly() = default;
    ~HeapOnly() = default;
};

void run_demo();

}  // namespace item06
