# Task 11 — Recommended production design

Use enum class Zone, a single fare-policy module with named percentage and balance constants, signed 64-bit integer paise, and a SmartCard with private balance. Keep fare calculation separate from balance mutation so quotes can be checked and explained before they are deducted. Store journey records in a vector only when a report or audit trail is required.

The design remains correct as the network grows because the tested network total is 6.6 billion paise, within int64_t and above the 32-bit signed limit. Fare lookup remains O(1) per trip; n trips take O(n). The class and fixed fare table use O(1) memory, with O(n) memory only for a retained report. Tests cover policy boundaries and invalid values.

Change fare values through one table and revise the boundary tests alongside them. A startup configuration file could avoid recompiling after a fare revision, but requires parsing, validation, error recovery, and a defined policy for missing or malformed configuration. Reading four 64-bit fares adds only 32 bytes of raw values and O(4) startup work. For a four-zone student assignment, compiled constants are simpler to validate; a production operator-facing system might choose validated configuration. The recommendation is based on the measured output in Task 10 and passing test rows in Task 9.
