# Task 4 — Implicit conversions and predicted output

## Prediction before execution

~~~text
3 3.5
C 68
1 true
true true
~~~

## Explanation

- a / b is int / int, so integer division produces 3 before assignment to double. The explicit cast makes the second division 7.0 / 2 -> 3.5.
- 'A' + 2 promotes char to int for arithmetic; the value is then converted back to char as 'C'. In ch + 1, ch promotes to int, so the output is the character code 68 on ASCII-compatible targets.
- Assigning 5 to bool converts nonzero to true. Default bool output is 1; std::boolalpha changes the formatting of the second output to true.
- u < 2 is true. In s >= u, s is -1 and u is unsigned int, so s converts to unsigned. The converted value is much larger than 1; the comparison is true. std::boolalpha remains enabled on the stream, so both values print as true. GCC may warn about comparing signed and unsigned values.

## Explicit conversion alternative

Writing static_cast<double>(a) / b makes the intended floating-point operation clear. Brace initialization prevents accidental narrowing, for example int value{3.7} is rejected. The application keeps fare and balance in paise, then makes one explicit conversion only at display time.

Making every conversion explicit does not materially change running time or object memory; the compiler emits the same necessary conversions or optimizes them away. It moves mistakes such as narrowing into compile-time diagnostics when brace initialization is used. A cast can still intentionally truncate, so explicit syntax must be paired with a justified rule.
