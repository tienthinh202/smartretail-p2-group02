# Test cases

## Function tests – T02b

- Tested on: 2026-11-24
- Environment: macOS, Apple clang 21.0.0
- Tested commit: 3dcb7d4
- Related PR: #7
- Test harness: `tests/test_t02b.cpp`
- Result: 17/17 tests passed.
- Compilation: no errors or warnings with `-std=c++17 -Wall -Wextra -pedantic`.

### How to run

Run these commands from the repository root:

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic tests/test_t02b.cpp -o /tmp/test_t02b
/tmp/test_t02b
```

The executable runs all 17 cases. Match each output line to its test ID.

Before each case, `minutes` is set to -1 and `error` is set to
"Previous error". The test checks the return value, minutes,
and exact error message.

### Expected error messages

- E1: Time must contain exactly 5 characters
- E2: Time must use HH:MM format
- E3: Hour and minute must contain only digits
- E4: Hour must be between 00 and 23
- E5: Minute must be between 00 and 59

In Expected, values are listed as return value, minutes, and error.
For invalid input, minutes must remain -1.
Quotation marks delimit inputs; spaces inside them are part of the input.

### Results

| ID | Scenario | Input (command) | Expected | Actual | Pass/Fail |
| --- | --- | --- | --- | --- | --- |
| T02b-01 | Midnight / lower boundary | `/tmp/test_t02b` — case 01: `"00:00"` | true; 0; empty error | `return=true, minutes=0, error=""` | PASS |
| T02b-02 | Valid time with leading zeros | `/tmp/test_t02b` — case 02: `"09:05"` | true; 545; empty error | `return=true, minutes=545, error=""` | PASS |
| T02b-03 | Valid midday time | `/tmp/test_t02b` — case 03: `"12:30"` | true; 750; empty error | `return=true, minutes=750, error=""` | PASS |
| T02b-04 | Upper valid boundary | `/tmp/test_t02b` — case 04: `"23:59"` | true; 1439; empty error | `return=true, minutes=1439, error=""` | PASS |
| T02b-05 | Hour exceeds 23 | `/tmp/test_t02b` — case 05: `"24:00"` | false; -1; E4 | `return=false, minutes=-1, error="Hour must be between 00 and 23"` | PASS |
| T02b-06 | Minute exceeds 59 | `/tmp/test_t02b` — case 06: `"00:60"` | false; -1; E5 | `return=false, minutes=-1, error="Minute must be between 00 and 59"` | PASS |
| T02b-07 | Both ranges invalid; hour checked first | `/tmp/test_t02b` — case 07: `"25:61"` | false; -1; E4 | `return=false, minutes=-1, error="Hour must be between 00 and 23"` | PASS |
| T02b-08 | Empty input | `/tmp/test_t02b` — case 08: `""` | false; -1; E1 | `return=false, minutes=-1, error="Time must contain exactly 5 characters"` | PASS |
| T02b-09 | Input too short | `/tmp/test_t02b` — case 09: `"9:05"` | false; -1; E1 | `return=false, minutes=-1, error="Time must contain exactly 5 characters"` | PASS |
| T02b-10 | Input too long | `/tmp/test_t02b` — case 10: `"09:050"` | false; -1; E1 | `return=false, minutes=-1, error="Time must contain exactly 5 characters"` | PASS |
| T02b-11 | Incorrect separator | `/tmp/test_t02b` — case 11: `"09-05"` | false; -1; E2 | `return=false, minutes=-1, error="Time must use HH:MM format"` | PASS |
| T02b-12 | Non-digit at index 0 | `/tmp/test_t02b` — case 12: `"a9:05"` | false; -1; E3 | `return=false, minutes=-1, error="Hour and minute must contain only digits"` | PASS |
| T02b-13 | Non-digit at index 1 | `/tmp/test_t02b` — case 13: `"0a:05"` | false; -1; E3 | `return=false, minutes=-1, error="Hour and minute must contain only digits"` | PASS |
| T02b-14 | Non-digit at index 3 | `/tmp/test_t02b` — case 14: `"09:a5"` | false; -1; E3 | `return=false, minutes=-1, error="Hour and minute must contain only digits"` | PASS |
| T02b-15 | Non-digit at index 4 | `/tmp/test_t02b` — case 15: `"09:0a"` | false; -1; E3 | `return=false, minutes=-1, error="Hour and minute must contain only digits"` | PASS |
| T02b-16 | Space replaces first digit | `/tmp/test_t02b` — case 16: `" 9:05"` | false; -1; E3 | `return=false, minutes=-1, error="Hour and minute must contain only digits"` | PASS |
| T02b-17 | Extra trailing space | `/tmp/test_t02b` — case 17: `"09:05 "` | false; -1; E1 | `return=false, minutes=-1, error="Time must contain exactly 5 characters"` | PASS |

Actual values above were transcribed from the test run.

```text
Result: 17/17 tests passed
```

### Scope

These are function-level tests calling `toMinutes()` from
`src/main.cpp`. The test harness is included in the repository.

Full application tests with `data/sample`, `data/full`, and
`data/edge` have not been run as part of this verification.
