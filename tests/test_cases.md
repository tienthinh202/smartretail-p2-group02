# Test cases

## T02b — toMinutes()

- Tested on: 2026-11-21
- Environment: macOS, Apple clang 21.0.0
- Compiler flags: -std=c++17 -Wall -Wextra
- Tested implementation commit: 6acaa53
- Related PR: #7
- Result: 17/17 tests passed, no compiler warnings.

Before each test, `minutes` was set to -1 and `error` to
"Previous error". Each test checked the return value, minutes,
and exact error message.

### Error messages

- E1: Time must contain exactly 5 characters
- E2: Time must use HH:MM format
- E3: Hour and minute must contain only digits
- E4: Hour must be between 00 and 23
- E5: Minute must be between 00 and 59

### Results

Quotation marks delimit the input and are not part of it.
Spaces inside quotation marks are part of the input.

| ID | Input | Expected return | Expected minutes | Expected error | Result |
| --- | --- | --- | --- | --- | --- |
| T02b-01 | "00:00" | true | 0 | Empty | PASS |
| T02b-02 | "09:05" | true | 545 | Empty | PASS |
| T02b-03 | "12:30" | true | 750 | Empty | PASS |
| T02b-04 | "23:59" | true | 1439 | Empty | PASS |
| T02b-05 | "24:00" | false | -1 (unchanged) | E4 | PASS |
| T02b-06 | "00:60" | false | -1 (unchanged) | E5 | PASS |
| T02b-07 | "25:61" | false | -1 (unchanged) | E4 | PASS |
| T02b-08 | "" | false | -1 (unchanged) | E1 | PASS |
| T02b-09 | "9:05" | false | -1 (unchanged) | E1 | PASS |
| T02b-10 | "09:050" | false | -1 (unchanged) | E1 | PASS |
| T02b-11 | "09-05" | false | -1 (unchanged) | E2 | PASS |
| T02b-12 | "a9:05" | false | -1 (unchanged) | E3 | PASS |
| T02b-13 | "0a:05" | false | -1 (unchanged) | E3 | PASS |
| T02b-14 | "09:a5" | false | -1 (unchanged) | E3 | PASS |
| T02b-15 | "09:0a" | false | -1 (unchanged) | E3 | PASS |
| T02b-16 | " 9:05" | false | -1 (unchanged) | E3 | PASS |
| T02b-17 | "09:05 " | false | -1 (unchanged) | E1 | PASS |

### Scope

These are function-level tests using a temporary local C++ test
harness that calls the implementation in `src/main.cpp`.
The harness is not yet included in the repository.

Full application tests with `data/sample`, `data/full`, and
`data/edge` have not been run as part of this verification.
