# Task 9 — Fare validation plan

test_fare.cpp runs a table of fare inputs and expected values. It covers each base zone, peak and off-peak periods, exact boundary minutes 08:00, 10:00, 17:00, and 20:00, a student concession, weekend discount, monthly pass, the Rs 50 boundary, unknown zone, invalid time, and negative/zero recharge. The program prints expected and actual results and exits nonzero if a check fails.

Hand check: Inner off-peak costs 1,000 paise. Middle peak costs 2,000 * 120 / 100 = 2,400 paise. Outer peak costs 3,000 * 120 / 100 = 3,600 paise. A 6,100-paise balance cannot pay a 1,200-paise fare because 4,900 paise would remain, below the required 5,000. Balance therefore remains 6,100.

## Test table output

Captured output: outputs/task09_test_fare.txt. The suite checks each row in a loop; adding a zone or fare case requires adding a case rather than writing another special-purpose assertion block. The fare computation and each table row are O(1); the full table is O(n) in the number of test cases and uses O(n) case storage.
