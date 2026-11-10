#include <iostream>

namespace item04 { void run_demo(); }
namespace item05 { void run_demo(); }
namespace item06 { void run_demo(); }

int main() {
    std::cout << "Effective C++ - Itemii 4, 5 si 6\n";
    item04::run_demo();
    item05::run_demo();
    item06::run_demo();
    return 0;
}
