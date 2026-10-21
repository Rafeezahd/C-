# Task 6 — Control structures and completed code

The completed switch-based integer-paise implementation is complete_code.cpp. The switch has a default error path so an unmatched zone cannot silently receive a zero fare.

## Pseudocode

~~~text
SET balance to 10,000 paise
FOR each journey
    SWITCH on zone
        Inner: base fare = 1,000 paise
        Middle: base fare = 2,000 paise
        Outer: base fare = 3,000 paise
        OTHERWISE: reject unknown zone
    IF peak
        fare = (base fare * 120 + 50) / 100 using integer arithmetic
    ELSE
        fare = base fare
    IF balance - fare >= 5,000 paise
        deduct fare and report fare plus new balance
    ELSE
        report denial and leave balance unchanged
END FOR
~~~

The named fare function and switch are easier to extend than a nested conditional expression. A range-for loop is appropriate when every journey must be processed; continue belongs after a rejected record if the loop should skip to the next journey, and break is appropriate only when the whole input stream should stop. A switch default is necessary for unexpected zone values.

For a fixed number of zones and journeys, fare lookup and each card update are O(1); processing n journeys is O(n). The fare table uses O(1) fixed space. A growing journey report uses O(n) space if retained in memory.

Use if/else for a boolean peak condition and balance approval, switch for a finite zone selection, and ?: only for a short value choice. A switch default must reject an unknown zone. The fare switch has three cases and constant work for the fixed network. Replacing it with a validated indexed array is also O(1) lookup; three 64-bit entries use 24 bytes (four use 32 bytes). A compiler may use a jump table for switch but does not promise one. Adding a zone requires another enumerator, fare entry/case, and tests. In a growing or data-driven network the array is easier to extend; at this small fixed size either design is constant time.
