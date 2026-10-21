# Task 12 — Day challenge: fourth zone and new fare products

## A. Impact analysis

The Airport zone adds a fourth enumerator and a Rs 60.00 base fare (6,000 paise). The fare array and zone lookup gain one entry; input validation accepts zone 4; output names Airport. The switch example in Task 6 is deliberately scoped to the original three zones, while the shared production fare policy and Task 12 implementation support four.

The 10% weekend discount is represented by FareMode::Weekend. It replaces the weekday peak surcharge, so a weekend journey at 09:00 costs the discounted fare rather than a peak-adjusted fare. MonthlyPass is a separate mode with zero per-journey fare. SmartCard also records a pass entitlement and does not debit stored value for its trips. This is an explicit interpretation of “unlimited journeys.”

The concession amount was missing from the original brief; the documented 50% assumption is centralized. It is applied to the base fare first. On a weekend, the 10% discount is applied to that adjusted fare. On a weekday, the 20% peak surcharge applies after concession. This order is explicit so future policy review has one place to change it.

## B. Original design evaluation

A hard-coded three-way switch can compute the original fares but needs another case and revised input/output checks for Airport. A simple card can store the pass flag alongside balance, but should not make pass journeys depend on the stored-balance minimum. The revised SmartCard::deduct handles both paid cards and pass holders. For example, Airport at 17:00 is 7,200 paise; a stored-value balance of 7,000 is denied, while an Airport monthly-pass ride is approved with zero balance.

## C. Revised design

Zone is enum class with an explicit uint8_t underlying type. Base prices and percentages live in the shared header. FareQuote carries amount and rule flags. SmartCard privately owns stored balance and pass status. Fare calculation is O(1), card processing is O(1), and n journeys take O(n). The four-value table has constant space; storing n report rows costs O(n).

## D. Evidence and trade-offs

design_challenge.cpp demonstrates weekday peak fare, weekend fare, student weekend fare, an insufficient Airport fare, and 100 free monthly-pass journeys. Task 09 checks boundary hours and rule combinations. The trade-off is that compact compiled constants require a rebuild for policy changes; a validated configuration file would allow policy updates at startup but adds parsing and configuration-error handling. The selected design favors explicit, checked policy behavior for this assignment.
