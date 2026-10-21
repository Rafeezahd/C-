#include "../common/FareSystem.hpp"

#include <iomanip>
#include <iostream>
#include <limits>
#include <type_traits>

template <typename T>
void printType(const char* name) {
    using Limits = std::numeric_limits<T>;
    std::cout << std::left << std::setw(12) << name
              << " size=" << sizeof(T) << " byte(s)";
    if constexpr (std::is_same_v<T, char>) {
        std::cout << " range=[" << static_cast<int>(Limits::lowest()) << ','
                  << static_cast<int>(Limits::max()) << ']';
    } else {
        std::cout << " range=[" << Limits::lowest() << ',' << Limits::max() << ']';
    }
    std::cout << '\n';
}

int main() {
    std::cout << std::scientific << std::setprecision(6);
    printType<bool>("bool");
    printType<char>("char");
    printType<int>("int");
    printType<long long>("long long");
    printType<unsigned int>("unsigned");
    printType<float>("float");
    printType<double>("double");
    printType<metro::Money>("Money/paise");
    std::cout << std::left << std::setw(12) << "Zone"
              << " size=" << sizeof(metro::Zone) << " byte(s), four scoped values\n";
    const auto deducedCount = 1;
    std::cout << std::left << std::setw(12) << "auto count"
              << " size=" << sizeof(deducedCount) << " byte(s), deduced as int\n";
}
