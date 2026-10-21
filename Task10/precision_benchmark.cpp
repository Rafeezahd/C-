#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    constexpr std::int64_t faresPaise[] = {1000, 2000, 3000, 1200, 2400, 3600};
    constexpr std::int64_t counts[] = {20000, 500000, 3000000};
    std::cout << "Journeys | integer-paise total | double total (Rs) | schedule error (paise) | repeated Rs0.10 error (paise) | int32 overflow? | integer ns/add | double ns/add\n";
    for (const std::int64_t count : counts) {
        std::int64_t totalPaise = 0;
        double totalRupees = 0.0;

        const auto integerStart = std::chrono::steady_clock::now();
        for (std::int64_t i = 0; i < count; ++i) {
            const auto fare = faresPaise[i % (sizeof(faresPaise) / sizeof(faresPaise[0]))];
            totalPaise += fare;
        }
        const auto integerStop = std::chrono::steady_clock::now();

        const auto doubleStart = std::chrono::steady_clock::now();
        for (std::int64_t i = 0; i < count; ++i) {
            const auto fare = faresPaise[i % (sizeof(faresPaise) / sizeof(faresPaise[0]))];
            totalRupees += static_cast<double>(fare) / 100.0;
        }
        const auto doubleStop = std::chrono::steady_clock::now();

        double repeatedTenPaiseRupees = 0.0;
        for (std::int64_t i = 0; i < count; ++i) repeatedTenPaiseRupees += 0.10;
        const std::int64_t exactTenPaise = count * 10;
        const double scheduleErrorPaise = totalRupees * 100.0 - static_cast<double>(totalPaise);
        const double decimalErrorPaise = repeatedTenPaiseRupees * 100.0 - static_cast<double>(exactTenPaise);
        const auto integerNs = std::chrono::duration_cast<std::chrono::nanoseconds>(integerStop - integerStart).count();
        const auto doubleNs = std::chrono::duration_cast<std::chrono::nanoseconds>(doubleStop - doubleStart).count();
        const auto int32Maximum = static_cast<std::int64_t>(2147483647);

        std::cout << count << " | " << totalPaise << " | " << std::fixed << std::setprecision(2)
                  << totalRupees << " | " << std::setprecision(8) << scheduleErrorPaise
                  << " | " << decimalErrorPaise << " | "
                  << (totalPaise > int32Maximum ? "yes" : "no") << " | "
                  << std::setprecision(2) << static_cast<double>(integerNs) / count
                  << " | " << static_cast<double>(doubleNs) / count << '\n';
    }
}
