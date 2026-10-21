#include "../common/FareSystem.hpp"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

long long readInteger(const std::string& prompt, long long minimum,
                      long long maximum) {
    for (;;) {
        std::cout << prompt << '\n';
        long long value = 0;
        if (std::cin >> value) {
            if (value >= minimum && value <= maximum) return value;
            std::cout << "Value out of range; try again.\n";
        } else if (std::cin.eof()) {
            throw std::runtime_error("input ended before the journey was complete");
        } else {
            std::cout << "Please enter a whole number; try again.\n";
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    try {
        const long long initial = readInteger("Starting balance (paise):", 0, 1000000000000LL);
        const bool hasPass = readInteger("Monthly pass on this card? (0 no, 1 yes):", 0, 1) == 1;
        metro::SmartCard card(initial, hasPass);
        const long long count = readInteger("Number of journeys:", 0, 10000);

        std::cout << "\nJourney report\n";
        std::cout << "#  Zone     Time   Fare (Rs)  Result        Balance (Rs)\n";
        for (long long i = 1; i <= count; ++i) {
            std::cout << "Journey " << i << '\n';
            const long long zoneValue = readInteger("Zone (1 Inner, 2 Middle, 3 Outer, 4 Airport):", -1000000, 1000000);
            const long long hour = readInteger("Hour (0-23):", 0, 23);
            const long long minute = readInteger("Minute (0-59):", 0, 59);
            const long long modeValue = readInteger("Fare mode (0 weekday, 1 weekend):", 0, 1);
            const long long passengerValue = readInteger("Passenger (0 regular, 1 student, 2 senior):", 0, 2);

            std::cout << i << "  ";
            try {
                if (zoneValue < 1 || zoneValue > 4) {
                    throw std::invalid_argument("unknown zone");
                }
                const auto zone = static_cast<metro::Zone>(zoneValue);
                const auto passenger = static_cast<metro::PassengerKind>(passengerValue);
                const auto mode = static_cast<metro::FareMode>(modeValue);
                const metro::TimeOfDay time{static_cast<int>(hour), static_cast<int>(minute)};
                const auto quote = metro::calculateFare(zone, time, passenger, mode);
                const bool approved = card.deduct(quote);
                const metro::Money chargedPaise = card.hasMonthlyPass() ? 0 : quote.amountPaise;
                std::cout << std::left << std::setw(9) << metro::zoneName(zone)
                          << std::right << std::setfill('0') << std::setw(2) << hour
                          << ':' << std::setw(2) << minute << std::setfill(' ')
                          << "   " << std::fixed << std::setprecision(2)
                          << static_cast<double>(chargedPaise) / 100.0
                          << "      " << (approved ? "Approved" : "Denied")
                          << "       " << static_cast<double>(card.balancePaise()) / 100.0
                          << '\n';
            } catch (const std::invalid_argument&) {
                std::cout << "Unknown  --:--     0.00      Invalid zone   "
                          << std::fixed << std::setprecision(2)
                          << static_cast<double>(card.balancePaise()) / 100.0 << '\n';
            }
        }
    } catch (const std::exception& error) {
        std::cerr << "Input error: " << error.what() << '\n';
        return 1;
    }
}
