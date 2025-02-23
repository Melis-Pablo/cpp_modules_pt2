## Type detection guidelines

### General rules
- Whitespace handling (should we trim?)
- Multiple decimal points are invalid
- Invalid characters in numbers are invalid
- Case sensitivity for special values (nan vs NAN)?
- Handle empty input
- Handle Null input
- a number with no decimal point is an integer
- negative -0 is just an integer 0
- only decimal notation is allowed

### Char Detection Rules:
Example: 'c', 'a'
- Single character in single quotes
- Non-displayable characters not allowed
- Must be exactly 3 characters long (including quotes)

### Float Detection Rules:
Example: 0.0f, -4.2f, 4.2f, nanf, +inff, -inff
- Any number with decimal point ending in 'f'
- Special literals: "nanf", "+inff", "-inff"
- Must be within FLT_MIN and FLT_MAX
- At least one digit required before and after decimal point
- Optional sign (+ or -)
- handle f at the end of the number with no decimal point

### Double Detection Rules:
Example: 0.0, -4.2, 4.2, nan, +inf, -inf
- Any number with decimal point (no 'f' suffix)
- Must be within DBL_MIN and DBL_MAX
- Special literals: "nan", "+inf", "-inf"
- At least one digit required before and after decimal point
- Optional sign (+ or -)

### Int Detection Rules:
Example: 0, -42, 42
- Any number of digits with optional sign
- Must be within INT_MIN and INT_MAX
- Can be derived from decimal numbers without fractional part (e.g., "42.0")
- No decimal point allowed in direct representation
