#include <array>
#include <iostream>

enum class Zone { Inner, Middle, Outer };
constexpr std::array<long long, 3> fares{{1000, 2000, 3000}};
constexpr long long minimumBalance = 5000;

long long fareFor(Zone zone, bool peak) {
    const auto base = fares.at(static_cast<std::size_t>(zone));
    return peak ? base * 120 / 100 : base;
}

bool processJourney(long long& balance, Zone zone, bool peak) {
    const long long charge = fareFor(zone, peak);
    if (balance - charge < minimumBalance) return false;
    balance -= charge;
    return true;
}

int main() {
    long long balance = 10000;
    const std::array<Zone, 3> zones{{Zone::Inner, Zone::Outer, Zone::Middle}};
    const std::array<bool, 3> peaks{{false, true, false}};
    for (std::size_t i = 0; i < zones.size(); ++i) {
        const long long charge = fareFor(zones[i], peaks[i]);
        if (processJourney(balance, zones[i], peaks[i])) {
            std::cout << "Approved: " << charge << " paise; remaining "
                      << balance << " paise\n";
        } else {
            std::cout << "Denied; remaining " << balance << " paise\n";
        }
    }
}
