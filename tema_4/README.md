# Effective C++ - Itemii 4, 5, 6

| Item | Fisiere | Ce demonstreaza |
|------|---------|-----------------|
| 4 - initializare inainte de utilizare | `include/item04.hpp`, `src/item04.cpp` | built-in neinitializate, lista de init vs atribuire, const/ref, ctori delegati, ordinea declararii, Singleton Meyers pentru statice |
| 5 - functiile scrise silentios | `include/item05.hpp`, `src/item05.cpp` | cele 6 functii generate, cand NU sunt generate (ctor declarat, ref/const, baza cu operator= deleted), destructor declarat => mutarea devine copiere, Regula celor 5 / lui 0, destructor virtual |
| 6 - interzicerea functiilor nedorite | `include/item06.hpp`, `src/item06.cpp` | private fara definitie (C++98), `Uncopyable`, `= delete`, non-movable, move-only, overload-uri / specializari deleted, StackOnly / HeapOnly |

`include/common.hpp` contine `Noisy`, o clasa care afiseaza fiecare apel de ctor/copy/move/dtor.
Multe verificari se fac la compilare cu `static_assert` + `<type_traits>`.

## Build
```
cmake -S . -B build -DENABLE_SANITIZERS=ON
cmake --build build
./build/effective_cpp
```
sau direct: `g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o effective_cpp`

## Exercitiu
Decomenteaza liniile marcate `// EROARE` din `src/item06.cpp` si `include/item0[45].hpp`, pe rand, si observa mesajele compilatorului.
