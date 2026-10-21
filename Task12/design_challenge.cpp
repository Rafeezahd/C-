#include "../common/FareSystem.hpp"

#include <array>
#include <iostream>

int main() {
    std::cout << "Revised four-zone smart-card design\n";
    metro::SmartCard card(10000);
    struct Journey {
        metro::Zone zone;
        metro::TimeOfDay time;
        metro::PassengerKind passenger;
        metro::FareMode mode;
    };
    const std::array<Journey, 4> journeys{{
        {metro::Zone::Inner, {8, 0}, metro::PassengerKind::Regular, metro::FareMode::Weekday},
        {metro::Zone::Middle, {9, 0}, metro::PassengerKind::Regular, metro::FareMode::Weekend},
        {metro::Zone::Outer, {12, 0}, metro::PassengerKind::Student, metro::FareMode::Weekend},
        {metro::Zone::Airport, {17, 0}, metro::PassengerKind::Regular, metro::FareMode::Weekday}
    }};

    int number = 1;
    for (const Journey& journey : journeys) {
        const auto quote = metro::calculateFare(journey.zone, journey.time,
                                                journey.passenger, journey.mode);
        const bool approved = card.deduct(quote);
        std::cout << number++ << ". " << metro::zoneName(journey.zone)
                  << " at " << journey.time.hour << ':'
                  << (journey.time.minute < 10 ? "0" : "") << journey.time.minute
                  << " -> " << quote.amountPaise << " paise, "
                  << (approved ? "approved" : "denied") << ", balance "
                  << card.balancePaise() << " paise\n";
    }

    metro::SmartCard passHolder(0, true);
    const auto airportFare = metro::calculateFare(metro::Zone::Airport, {18, 0});
    int approvedPassRides = 0;
    for (int ride = 0; ride < 100; ++ride) {
        approvedPassRides += passHolder.deduct(airportFare) ? 1 : 0;
    }
    std::cout << "Monthly pass: " << approvedPassRides
              << " airport journeys approved; stored balance "
              << passHolder.balancePaise() << " paise\n";
}
