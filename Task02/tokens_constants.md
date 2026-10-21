# Task 2 — Tokens, names, and constants

## Five token categories

| Category | Example from this program | Role |
|---|---|---|
| Keyword | class, enum, switch, return | Reserved syntax that defines declarations or control flow. |
| Identifier | SmartCard, balancePaise, calculateFare | A programmer-chosen name for a type, function, or value. |
| Literal / constant | 5000, 0.10, "unknown zone" | A value written directly in source code. |
| Operator | -, >=, *, /, && | Performs arithmetic, comparison, or logical combination. |
| Punctuator | { }, ( ), ;, ::, , | Groups declarations and expressions or separates syntax. |

## Fare definitions in one place

The values kBaseFarePaise, kPeakSurchargePercent, kConcessionPercent, kWeekendDiscountPercent, and kMinimumBalancePaise are declared once in common/FareSystem.hpp. A future policy change edits the central fare rules instead of searching for repeated literals in each program. Task 6 separately shows the compact switch solution requested by the prompt.

- #define is textual substitution. It has no C++ type or normal scope, and an expression-like macro can repeat an argument or surprise with precedence. It usually creates no storage by itself.
- const creates a typed object that cannot be reassigned. Its initializer may be evaluated at runtime; storage is needed if the object has an observable address or otherwise must exist.
- constexpr creates a typed constant usable in constant expressions when initialized accordingly. It often needs no runtime storage when its value is substituted or folded, though an object may need storage when its address is used.
- enum class Zone gives the zone names a distinct scoped type. It prevents accidental implicit conversion to int and prevents enumerators such as Inner from leaking into the surrounding scope. A new Airport entry is handled visibly in the same fare policy.

An unscoped enum also creates named enumerators, but its values can convert to integers implicitly and its names are less contained. enum class requires an explicit conversion at a validated input boundary, which makes zone-versus-integer mistakes easier to catch.

## Names and conventions

Types use PascalCase (SmartCard, FareQuote). Functions and local variables use lower camel case (calculateFare, balancePaise). Constants use a k prefix with PascalCase (kMinimumBalancePaise), while the focused Task 6 example uses uppercase names to match the worksheet style. Units appear in money variable names so that paise is not mistaken for rupees.

## Alternative: macro, constant, or enum table

A switch with three fixed zones has bounded constant work; a compiler may lower it to branches or a jump table. An indexed std::array also has O(1) lookup and stores 24 bytes for three 64-bit fares (32 bytes for four zones). It takes an index check or validated enum mapping. A #define fare macro contributes no fare-table object, but it offers weaker type checking and can evaluate expressions unexpectedly. A constexpr array keeps the single-source values and compile-time checks while making the Airport extension a one-entry data change. The call cost is O(1) in each design for a fixed number of zones; memory differs by roughly one fare value per added zone.
