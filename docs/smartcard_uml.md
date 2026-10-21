# Smart-card UML class diagram

~~~mermaid
classDiagram
    class TimeOfDay {
        +int hour
        +int minute
        +valid() bool
        +peak() bool
    }
    class Zone {
        <<enumeration>>
        Inner
        Middle
        Outer
        Airport
    }
    class PassengerKind {
        <<enumeration>>
        Regular
        Student
        Senior
    }
    class FareMode {
        <<enumeration>>
        Weekday
        Weekend
        MonthlyPass
    }
    class FareQuote {
        +Money amountPaise
        +bool monthlyPass
        +bool peakSurchargeApplied
        +bool concessionApplied
        +bool weekendDiscountApplied
    }
    class FarePolicy {
        +calculateFare(zone, time, passenger, mode) FareQuote
    }
    class SmartCard {
        -Money balancePaise
        -bool monthlyPass
        +balancePaise() Money
        +canTravel(quote) bool
        +deduct(quote) bool
        +recharge(amountPaise) bool
    }
    class Journey {
        +Zone zone
        +TimeOfDay time
        +PassengerKind passenger
        +FareMode mode
    }
    Journey --> Zone
    Journey --> TimeOfDay
    Journey --> PassengerKind
    Journey --> FareMode
    FarePolicy ..> FareQuote : creates
    FarePolicy ..> Zone : reads fare for
    SmartCard ..> FareQuote : validates and debits
~~~

The diagram describes responsibilities; FarePolicy is implemented as a namespace-level function group in common/FareSystem.hpp rather than a separate stateful class because it has no per-instance state.
