# Task 7 — Procedural and object-oriented versions

procedural.cpp keeps a balance variable and uses free functions. object_oriented.cpp stores the balance inside SmartCard and changes it only through deduct(). Both process Inner off-peak, Outer peak, then Middle off-peak from Rs 100.00. They use integer paise and preserve the same Rs 50 minimum-balance rule.

The procedural version uses O(1) state for one card. The object-oriented card also uses O(1) state; a vector of journey details would add O(n) storage in either design. Both compute each fare in O(1) and process all n journeys in O(n). The practical difference is where the invariant is enforced: a free function can be bypassed by any caller that writes the balance variable, while private card state limits mutation to validated operations. A minimum-balance revision changes one shared constant and its tests; class encapsulation helps ensure every caller sees it.

The classes and free functions each have a clear role. Inheritance or virtual dispatch is unnecessary for the fixed passenger set; an enum class expresses the variants with less machinery. If balance were a public data member, runtime and storage would not change, but any code could set it below 5,000 paise or debit without checking. The access rule would no longer be protected.
