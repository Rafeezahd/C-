# Task 5 — Precedence and expression output

## Prediction before execution

~~~text
11 16
9 6 4
6 4
3 1 -3 -1
18
~~~

## Operator order and results

1. x + y * 2: multiplication precedes addition, giving 5 + 6 = 11. Parentheses in (x + y) * 2 force the sum first, giving 16.
2. x++ + ++y: postfix increment yields old x (5), prefix increment first changes y to 4 and yields 4, so z=9; afterward x=6, y=4. These modify distinct variables, so this expression has no unsequenced modification conflict.
3. x > y ? x : y compares 6 and 4 and selects 6. In x % 4 * 2, remainder and multiplication have equal precedence and associate left-to-right: (6 % 4) * 2 = 4.
4. / and % associate left-to-right. Integer division truncates toward zero: 10/3=3, 10%3=1, -10/3=-3, and -10%3=-1. The remainder has the sign of the left operand.
5. The loop visits i=0,3,6,9 and adds them to k, giving 18. i += 3 is compound assignment; the loop stops when i is no longer less than 10.

## Readable peak check

Use a named function such as TimeOfDay::peak rather than embedding a complicated conditional expression. The equivalent interval predicate is (minutes >= 480 && minutes < 600) || (minutes >= 1020 && minutes < 1200). Since && has higher precedence than ||, the comparisons pair into each interval; parentheses make that grouping visible and short-circuit evaluation skips the second interval when the first matches. The expression is correct but harder to scan than the named function. A 24-element lookup table also answers in O(1), but takes 24 bytes if stored as bool, and needs a definition for minute-level precision or a 24-hour-only approximation. The predicate uses constant space and has at most four comparisons.
