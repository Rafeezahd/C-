# Task 8 — Safe input and formatted output

gate.cpp reads integer input through a retrying helper. When extraction fails on letters, it checks eof, calls clear() to reset the stream error state, discards the invalid input line with ignore(), and asks again. Values outside their allowed ranges are also rejected. An unknown zone is printed as an invalid journey and does not change the card balance. Monthly-pass entitlement is an explicit card input, so selecting a fare mode cannot grant a pass.

The output uses fixed precision with two decimal places for rupees. Fare arithmetic remains in paise; only display converts to double. The sample input includes three normal cases, an unknown zone, and an x in the hour field followed by a valid retry. The captured report is in outputs/task08.txt.

Reading a full line with getline and parsing it with stoi also takes O(L) time for a line of L characters. It needs O(L) temporary space to hold the line, while formatted extraction can process a token using stream buffering. stoi can report invalid text with an exception; the current >> approach clears failbit and discards the rest of the bad line before retrying. Both can recover safely when the failed input is consumed and re-prompted.

## UML class view

See docs/smartcard_uml.md. SmartCard privately owns its value balance and pass flag. FareQuote and TimeOfDay carry immutable-style value data between fare calculation and the card operation.
