#ifndef FARE_SYSTEM_HPP
#define FARE_SYSTEM_HPP

#include <array>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string_view>

namespace metro {

using Money = std::int64_t; // paise

constexpr Money kMinimumBalancePaise = 5000;
constexpr int kPeakSurchargePercent = 20;
constexpr int kConcessionPercent = 50; // explicit assignment assumption
constexpr int kWeekendDiscountPercent = 10;

enum class Zone : std::uint8_t { Inner = 1, Middle = 2, Outer = 3, Airport = 4 };
enum class PassengerKind : std::uint8_t { Regular, Student, Senior };
enum class FareMode : std::uint8_t { Weekday, Weekend, MonthlyPass };

struct TimeOfDay {
    int hour{};
    int minute{};

    bool valid() const noexcept {
        return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59;
    }

    bool peak() const noexcept {
        const int minutes = hour * 60 + minute;
        return (minutes >= 8 * 60 && minutes < 10 * 60) ||
               (minutes >= 17 * 60 && minutes < 20 * 60);
    }
};

inline constexpr std::array<Money, 4> kBaseFarePaise{{1000, 2000, 3000, 6000}};

constexpr std::string_view zoneName(Zone zone) {
    switch (zone) {
    case Zone::Inner: return "Inner";
    case Zone::Middle: return "Middle";
    case Zone::Outer: return "Outer";
    case Zone::Airport: return "Airport";
    }
    return "Unknown";
}

constexpr Money baseFare(Zone zone) {
    switch (zone) {
    case Zone::Inner: return kBaseFarePaise[0];
    case Zone::Middle: return kBaseFarePaise[1];
    case Zone::Outer: return kBaseFarePaise[2];
    case Zone::Airport: return kBaseFarePaise[3];
    }
    throw std::invalid_argument("unknown zone");
}

struct FareQuote {
    Money amountPaise{};
    bool monthlyPass{};
    bool peakSurchargeApplied{};
    bool concessionApplied{};
    bool weekendDiscountApplied{};
};

inline FareQuote calculateFare(Zone zone, TimeOfDay time,
                               PassengerKind passenger = PassengerKind::Regular,
                               FareMode mode = FareMode::Weekday) {
    if (!time.valid()) {
        throw std::invalid_argument("time must be between 00:00 and 23:59");
    }
    if (passenger != PassengerKind::Regular && passenger != PassengerKind::Student &&
        passenger != PassengerKind::Senior) {
        throw std::invalid_argument("unknown passenger kind");
    }
    if (mode != FareMode::Weekday && mode != FareMode::Weekend &&
        mode != FareMode::MonthlyPass) {
        throw std::invalid_argument("unknown fare mode");
    }
    if (mode == FareMode::MonthlyPass) {
        return FareQuote{0, true, false, false, false};
    }

    Money amount = baseFare(zone);
    const bool concession = passenger != PassengerKind::Regular;
    if (concession) {
        amount = amount * (100 - kConcessionPercent) / 100;
    }

    if (mode == FareMode::Weekend) {
        amount = amount * (100 - kWeekendDiscountPercent) / 100;
        return FareQuote{amount, false, false, concession, true};
    }

    const bool peak = time.peak();
    if (peak) {
        // Integer-only percentage arithmetic. Rounding is to the nearest paise.
        amount = (amount * (100 + kPeakSurchargePercent) + 50) / 100;
    }
    return FareQuote{amount, false, peak, concession, false};
}

inline bool canTravel(Money balancePaise, const FareQuote& quote) noexcept {
    if (quote.amountPaise < 0 || quote.monthlyPass) {
        return false; // entitlement belongs to the card, not to a fare quote
    }
    return balancePaise >= quote.amountPaise &&
           balancePaise - quote.amountPaise >= kMinimumBalancePaise;
}

class SmartCard {
public:
    explicit SmartCard(Money initialBalancePaise, bool monthlyPass = false)
        : balancePaise_(initialBalancePaise), monthlyPass_(monthlyPass) {
        if (initialBalancePaise < 0) {
            throw std::invalid_argument("initial balance cannot be negative");
        }
    }

    Money balancePaise() const noexcept { return balancePaise_; }
    bool hasMonthlyPass() const noexcept { return monthlyPass_; }

    bool canTravel(const FareQuote& quote) const noexcept {
        if (quote.amountPaise < 0) {
            return false;
        }
        return monthlyPass_ || metro::canTravel(balancePaise_, quote);
    }

    bool deduct(const FareQuote& quote) noexcept {
        if (quote.amountPaise < 0) {
            return false;
        }
        if (monthlyPass_) {
            return true;
        }
        if (!metro::canTravel(balancePaise_, quote)) {
            return false;
        }
        balancePaise_ -= quote.amountPaise;
        return true;
    }

    bool recharge(Money amountPaise) noexcept {
        if (amountPaise <= 0 ||
            balancePaise_ > std::numeric_limits<Money>::max() - amountPaise) {
            return false;
        }
        balancePaise_ += amountPaise;
        return true;
    }

private:
    Money balancePaise_;
    bool monthlyPass_;
};

} // namespace metro

#endif
