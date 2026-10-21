# City Metro Smart-Card Fare System

**Student:** [Enter name]<br>
**Register number:** [Enter register number]<br>
**Course:** C++ Programming<br>
**Compiler used:** GCC 16.2.0 (portable w64devkit toolchain)<br>
**Submission date in brief:** 20 October 2026

**GitHub repository:** https://github.com/Rafeezahd/C-

This repository contains the completed 12-task assignment. Tasks 1–11 analyze and implement the original three-zone rules. Task 12 extends the design to the Airport zone, weekend discount, and monthly pass.

## Requirements and assumptions

- Money is stored as signed 64-bit integer paise. The 50-rupee minimum stored balance is 5,000 paise.
- Peak windows are half-open: 08:00–09:59 and 17:00–19:59. Thus exactly 08:00 and 17:00 are peak, while 10:00 and 20:00 are off-peak.
- The assignment does not give a concession percentage. This implementation states its assumption in one place: students and senior citizens receive 50% off the base fare, before any peak surcharge.
- A 10% weekend discount applies to the fare after any passenger concession and replaces the peak surcharge.
- A monthly pass makes each journey fare-free and bypasses the stored-value minimum-balance check. Its unlimited ride behavior is separate from the stored-value card.
- Percentages are calculated with integer paise arithmetic, rounded to the nearest paise for a surcharge.

## Folder guide

- common: shared fare rules and the encapsulated SmartCard class.
- Task01–Task03: object model, tokens/constants, and data type analysis.
- Task04–Task06: conversion output, precedence output, and completed switch-based fare program.
- Task07: procedural and object-oriented versions of the same journey sequence.
- Task08: robust console input and formatted journey report; sample input is in input.txt.
- Task09: table-driven executable fare tests and edge cases.
- Task10: totals for 20,000, 500,000, and 3,000,000 journeys plus floating-point comparison.
- Task11: final recommendation and trade-offs.
- Task12: revised fare model and executable day-challenge examples.
- outputs: captured program output and test results.
- docs: pseudocode, UML, and cross-task complexity analysis.

## Compile and run

Use GCC 13+ with C++17. From the repository root, compile the programs individually:

~~~sh
g++ --version
g++ -std=c++17 -Wall -Wextra -Wpedantic Task04/predict_output.cpp -o Task04/predict_output
g++ -std=c++17 -Wall -Wextra -Wpedantic Task05/expressions.cpp -o Task05/expressions
g++ -std=c++17 -Wall -Wextra -Wpedantic Task06/complete_code.cpp -o Task06/complete_code
g++ -std=c++17 -Wall -Wextra -Wpedantic Task03/type_sizes.cpp -o Task03/type_sizes
g++ -std=c++17 -Wall -Wextra -Wpedantic Task07/procedural.cpp -o Task07/procedural
g++ -std=c++17 -Wall -Wextra -Wpedantic Task07/object_oriented.cpp -o Task07/object_oriented
g++ -std=c++17 -Wall -Wextra -Wpedantic Task08/gate.cpp -o Task08/gate
g++ -std=c++17 -Wall -Wextra -Wpedantic Task09/test_fare.cpp -o Task09/test_fare
g++ -std=c++17 -Wall -Wextra -Wpedantic Task10/precision_benchmark.cpp -o Task10/precision_benchmark
g++ -std=c++17 -Wall -Wextra -Wpedantic Task12/design_challenge.cpp -o Task12/design_challenge
~~~

On Windows, replace each executable name with an .exe suffix. From the repository root, run it as ./Task09/test_fare (or .\Task09\test_fare.exe in PowerShell). The gate example reads the sample file with:

~~~sh
./Task08/gate < Task08/input.txt
~~~

Run each standalone program from the repository root:

~~~sh
./Task03/type_sizes
./Task04/predict_output
./Task05/expressions
./Task06/complete_code
./Task07/procedural
./Task07/object_oriented
./Task08/gate < Task08/input.txt
./Task09/test_fare
./Task10/precision_benchmark
./Task12/design_challenge
~~~

In PowerShell, run the corresponding .exe paths. For the gate sample, use `Get-Content Task08/input.txt | .\Task08\gate.exe`.

The history contains a separate commit for each task, as required by the brief.

## Task results

| Task | Program / evidence | Result |
|---|---|---|
| 1 | Task01/analysis.md | Identified card, passenger, journey, zone, and fare-policy responsibilities; documented invariants and OOP trade-offs. |
| 2 | Task02/tokens_constants.md | Defined token categories and centralized named fare constants; compared macro, const, constexpr, and enum choices. |
| 3 | Task03/type_sizes.cpp | Reported measured type sizes and ranges; selected exact integer paise for money. |
| 4 | Task04/predict_output.cpp | Predicted and confirmed conversion output; documented signed/unsigned behavior and the compiler warning. |
| 5 | Task05/expressions.cpp | Predicted and confirmed precedence, increment, division, remainder, and loop output. |
| 6 | Task06/complete_code.cpp | Completed the switch-based integer-paise fare and minimum-balance logic. |
| 7 | Task07/procedural.cpp and Task07/object_oriented.cpp | Both versions produced the same three journey decisions and balances. |
| 8 | Task08/gate.cpp | Formatted a journey report, rejected an unknown zone, and recovered after letter input. |
| 9 | Task09/test_fare.cpp | All 14 table and invalid-input checks passed. |
| 10 | Task10/precision_benchmark.cpp | Measured totals at 20,000, 500,000, and 3,000,000 journeys; detected 32-bit overflow threshold. |
| 11 | Task11/recommendation.md | Recommended encapsulated card state, integer paise, centralized fare rules, and evidence-based change control. |
| 12 | Task12/design_challenge.cpp | Added Airport, weekend discount, and a monthly pass; 100 pass rides were approved without stored-value debit. |

## Result evidence

The outputs folder contains captured standard output for the executable examples and the table-driven checks. PNG console-output captures are in outputs/screenshots and are rendered directly from those run transcripts. Fill in the student name and register number before submitting.

The formatted Word assignment report is `outputs/Assignment_Report.docx`. It includes the system design and UML, task analyses, pseudocode summary, execution evidence, measured totals, and final recommendation. Fill in the student name and register number on its cover before submitting.
