#include "../common/FareSystem.hpp"

#include <iomanip>
#include <iostream>
#include <vector>

struct TestCase {
    const char* name;
    metro::Zone zone;
    metro::TimeOfDay time;
    metro::PassengerKind passenger;
    metro::FareMode mode;
    metro::Money balance;
    metro::Money expectedFare;
    bool expectedApproval;
};

int main() {
    const std::vector<TestCase> tests{
        {"inner off-peak", metro::Zone::Inner, {11, 0}, metro::PassengerKind::Regular, metro::FareMode::Weekday, 10000, 1000, true},
        {"middle peak", metro::Zone::Middle, {9, 0}, metro::PassengerKind::Regular, metro::FareMode::Weekday, 10000, 2400, true},
        {"middle off-peak", metro::Zone::Middle, {14, 0}, metro::PassengerKind::Regular, metro::FareMode::Weekday, 10000, 2000, true},
        {"outer peak", metro::Zone::Outer, {17, 30}, metro::PassengerKind::Regular, metro::FareMode::Weekday, 10000, 3600, true},
        {"outer off-peak", metro::Zone::Outer, {14, 0}, metro::PassengerKind::Regular, metro::FareMode::Weekday, 10000, 3000, true},
        {"exactly 08:00 is peak", metro::Zone::Inner, {8, 0}, metro::PassengerKind::Regular, metro::FareMode::Weekday, 10000, 1200, true},
        {"exactly 10:00 is off-peak", metro::Zone::Inner, {10, 0}, metro::PassengerKind::Regular, metro::FareMode::Weekday, 10000, 1000, true},
        {"exactly 17:00 is peak", metro::Zone::Inner, {17, 0}, metro::PassengerKind::Regular, metro::FareMode::Weekday, 10000, 1200, true},
        {"exactly 20:00 is off-peak", metro::Zone::Inner, {20, 0}, metro::PassengerKind::Regular, metro::FareMode::Weekday, 10000, 1000, true},
        {"concession", metro::Zone::Outer, {12, 0}, metro::PassengerKind::Student, metro::FareMode::Weekday, 10000, 1500, true},
        {"weekend ignores peak surcharge", metro::Zone::Outer, {9, 0}, metro::PassengerKind::Regular, metro::FareMode::Weekend, 10000, 2700, true},
        {"pass is free and unlimited", metro::Zone::Airport, {8, 0}, metro::PassengerKind::Regular, metro::FareMode::MonthlyPass, 0, 0, true},
        {"minimum remaining balance enforced", metro::Zone::Inner, {8, 0}, metro::PassengerKind::Regular, metro::FareMode::Weekday, 6100, 1200, false}
    };

    int failures = 0;
    std::cout << "Fare test table (money in paise)\n";
    for (const TestCase& test : tests) {
        const auto quote = metro::calculateFare(test.zone, test.time, test.passenger, test.mode);
        metro::SmartCard card(test.balance, test.mode == metro::FareMode::MonthlyPass);
        const bool approved = card.deduct(quote);
        const bool passed = quote.amountPaise == test.expectedFare && approved == test.expectedApproval;
        failures += passed ? 0 : 1;
        std::cout << (passed ? "PASS " : "FAIL ") << test.name
                  << " | expected " << test.expectedFare << ", actual " << quote.amountPaise
                  << " | expected " << (test.expectedApproval ? "approved" : "denied")
                  << ", actual " << (approved ? "approved" : "denied") << '\n';
    }

    bool invalidZoneRejected = false;
    try {
        (void)metro::baseFare(static_cast<metro::Zone>(99));
    } catch (const std::invalid_argument&) {
        invalidZoneRejected = true;
    }
    bool invalidTimeRejected = false;
    try {
        (void)metro::calculateFare(metro::Zone::Inner, {24, 0});
    } catch (const std::invalid_argument&) {
        invalidTimeRejected = true;
    }
    metro::SmartCard card(10000);
    const bool negativeRechargeRejected = !card.recharge(-1);
    const bool zeroRechargeRejected = !card.recharge(0);
    const metro::FareQuote invalidQuote{-1, false, false, false, false};
    const bool negativeFareRejected = !card.canTravel(invalidQuote) && !card.deduct(invalidQuote);
    const bool inputChecksPassed = invalidZoneRejected && invalidTimeRejected &&
                                   negativeRechargeRejected && zeroRechargeRejected &&
                                   negativeFareRejected;
    failures += inputChecksPassed ? 0 : 1;
    std::cout << (inputChecksPassed ? "PASS " : "FAIL ")
              << "invalid zone/time, non-positive recharge, and negative fare rejected\n";
    std::cout << "Summary: " << (tests.size() + 1 - failures) << '/'
              << (tests.size() + 1) << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
