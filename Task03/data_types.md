# Task 3 — Data types and compatibility

## Chosen types

| Value | Type | Common 64-bit GCC size | Range / reason |
|---|---:|---:|---|
| Approval or pass flag | bool | 1 byte | false or true; used only for logical state. |
| Single character | char | 1 byte | At least 8 bits; signedness is implementation-defined. |
| Zone | enum class Zone : uint8_t | 1 byte | Four enumerators fit, and the type cannot mix with ordinary integers implicitly. Validate external values before converting. |
| Journey count / time components | int | 4 bytes on the target ABI | Small bounded values; validate hours 0–23 and minutes 0–59. |
| Stored balance / fare | int64_t | 8 bytes | Exact signed integer paise; maximum 9,223,372,036,854,775,807, far above the tested totals. |
| Unsigned count | uint64_t | 8 bytes | Nonnegative counts when needed; avoid mixing it casually with signed values. |
| Fractional display only | double | 8 bytes | Used only to print paise as rupees; not used as the source of truth for money. |
| Approximate sensor-like measurement | float | 4 bytes | Not appropriate for money; has less precision than double. |
| Compiler-deduced local | auto | depends on deduced type | Reduces repeated type spelling; does not define a distinct storage size. |

Except for char being one byte, exact sizes depend on the implementation. The listed sizes are typical for GCC 13 on a 64-bit Windows/Linux ABI; record the target compiler's sizeof results if its ABI differs. The fixed-width int64_t / uint8_t names are used where exact width matters.

The measured sizes and numeric limits for the compiler used here (GCC 16.2.0, x64 w64devkit) are in outputs/task03_type_sizes.txt. They confirm the common 64-bit table above.

## Compatibility and narrowing

In int + double, int converts to double and the result is double. In arithmetic, bool promotes to int (false -> 0, true -> 1); assigning a nonzero integer to bool yields true. In a comparison between signed int and unsigned int of the same rank, the signed operand is converted to unsigned. Thus comparing -1 with 1u yields a surprising result because -1 becomes the maximum unsigned value. The compiler can issue a sign-comparison warning.

An implicit conversion from 3.7 to int discards the fraction. Brace initialization rejects narrowing such as int x{3.7}; use an explicit, justified cast only when that truncation is intended. Here, money remains in integer paise from input through fare and balance updates; conversion to double occurs only for formatted output.

## Integer paise versus double rupees

Both integer addition and double addition are O(1) per fare and O(n) across n journeys. A 64-bit integer and a double commonly each occupy 8 bytes. Integer paise exactly represents the fare and can be compared to the Rs 50 limit without rounding. IEEE binary double cannot exactly represent many decimal fractions such as Rs 0.10; repeated additions can accumulate a small error. The actual fare schedule in this assignment is whole-rupee-valued, so those particular totals remain exact as doubles at these sizes; Task 10 also measures a repeated Rs 0.10 example to expose the general risk. A 32-bit signed paise total overflows at the three-million-journey network case, while int64_t does not.
