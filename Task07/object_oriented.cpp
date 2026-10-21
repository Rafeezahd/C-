#include "../common/FareSystem.hpp"

#include <array>
#include <iostream>

struct Journey {
    metro::Zone zone;
    metro::TimeOfDay time;
};

int main() {
    metro::SmartCard card(10000);
    const std::array<Journey, 3> journeys{{
        {metro::Zone::Inner, {11, 0}},
        {metro::Zone::Outer, {8, 0}},
        {metro::Zone::Middle, {14, 0}}
    }};

    for (const Journey& journey : journeys) {
        const auto quote = metro::calculateFare(journey.zone, journey.time);
        if (card.deduct(quote)) {
            std::cout << "Approved: " << quote.amountPaise << " paise; remaining "
                      << card.balancePaise() << " paise\n";
        } else {
            std::cout << "Denied; remaining " << card.balancePaise() << " paise\n";
        }
    }
}
