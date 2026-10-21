# Task 1 — Object-oriented analysis

## Objects, data, and behavior

| Object | Data it owns | Behavior and rule it protects |
|---|---|---|
| SmartCard | Stored balance in paise; monthly-pass flag | Quotes/debits a fare, recharges, and preserves the minimum-balance rule. A failed journey does not change balance. |
| Passenger | Passenger kind: regular, student, or senior | Supplies eligibility for a concession. It does not own or mutate a card balance. |
| Journey | Zone and time; in the extension, fare mode | Represents one requested trip and supplies the inputs for a fare quote. |
| Zone | Inner, Middle, Outer; Airport in Task 12 | Identifies the destination band and selects its base fare. |
| Fare table / FarePolicy | Base fares and percentage rules | Calculates a quote consistently from one set of policy values. |

The fare amounts in the original three-zone scenario are Rs 10, Rs 20, and Rs 30. A weekday peak journey adds 20%; the peak window is 08:00–10:00 and 17:00–20:00 under the half-open boundary convention stated in README. A paid journey is allowed only when balance minus fare is at least Rs 50. Student/senior concession percentage was not specified, so the code labels its chosen 50% assumption rather than presenting it as a supplied rule.

## OOP principles applied

- Encapsulation: SmartCard keeps its balance and pass status private; callers use validated debit and recharge operations.
- Abstraction: calculateFare returns a FareQuote so the gate does not duplicate percentage arithmetic or know how policy is applied.
- Inheritance: not used because student/senior eligibility is one small category value and there is no distinct behavior requiring a subtype.
- Polymorphism: not used because all fare calculations share one policy function; virtual dispatch would add complexity without changing the result.

## Procedural versus object-oriented design

A procedural implementation can keep a balance variable and call free functions such as fareFor(zone, time) and canTravel(balance, fare). For one card, this uses O(1) state and processes each journey in O(1). It is compact, but every caller that can modify a public balance must remember the Rs 50 invariant.

The object-oriented version stores the balance privately in SmartCard. Its deduct operation checks eligibility and mutates the balance only after approval. Encapsulation makes the rule harder to bypass; inheritance is not needed for the small fixed set of passenger kinds, and polymorphism would add dispatch machinery without changing the fare rule. A vector of n journey records uses O(n) storage, while each card still uses O(1) storage. Both designs remain O(1) per journey and O(n) for n journeys overall.

## Correctness invariant

For a stored-value card, every successful paid journey leaves balance >= 5,000 paise. Denied or invalid journeys leave balance unchanged. A pass journey costs zero and is not charged to stored value. Recharges must be positive and must not overflow the signed 64-bit balance. Zone and time values are validated before fare lookup.
