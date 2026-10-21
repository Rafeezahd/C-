#include <array>
#include <iomanip>
#include <iostream>
#include <stdexcept>

enum class Zone { Inner, Middle, Outer };

constexpr std::array<long long, 3> BASE_FARE_PAISE{{1000, 2000, 3000}};
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;

long long fare(Zone zone, bool peak) {
    long long base = 0;
    switch (zone) {
    case Zone::Inner: base = BASE_FARE_PAISE[0]; break;
    case Zone::Middle: base = BASE_FARE_PAISE[1]; break;
    case Zone::Outer: base = BASE_FARE_PAISE[2]; break;
    default: throw std::invalid_argument("unknown zone");
    }
    return peak ? (base * (100 + PEAK_SURCHARGE_PERCENT) + 50) / 100 : base;
}

bool canTravel(long long balance, long long f) {
    return balance >= f && balance - f >= MIN_BALANCE_PAISE;
}

int main() {
    long long balance = 10000; // Rs 100.00 stored as paise
    struct Trip { Zone zone; bool peak; };
    const std::array<Trip, 3> trips{{
        {Zone::Inner, false}, {Zone::Outer, true}, {Zone::Middle, false}
    }};

    for (const Trip& trip : trips) {
        const long long f = fare(trip.zone, trip.peak);
        if (canTravel(balance, f)) {
            balance -= f;
            std::cout << "Fare Rs " << std::fixed << std::setprecision(2)
                      << static_cast<double>(f) / 100.0
                      << " balance Rs " << static_cast<double>(balance) / 100.0 << '\n';
        } else {
            std::cout << "Denied (low balance) balance Rs "
                      << std::fixed << std::setprecision(2)
                      << static_cast<double>(balance) / 100.0 << '\n';
        }
    }
}
