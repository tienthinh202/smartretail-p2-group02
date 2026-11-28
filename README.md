# P2 – Customer Journey Analyzer
 
Fundamentals of Programming (C++) · MiiN-SmartRetail · Group F01-G02
 
## 1. Project, team and lecturer
 
| Member | GitHub | Role |
| --- | --- | --- |
| Hoàng Đình Triển | [@tienthinh202](https://github.com/tienthinh202) | Team leader |
| Nguyễn Ngọc Hoàng Yến | [@mickeyy08](https://github.com/mickeyy08) | Member |
| Đinh Thị Bảo Trâm | [@Katherine1810](https://github.com/Katherine1810) | Member |
| Tạ Chí Kiên | [@Sam649-hub](https://github.com/Sam649-hub) | Member |
 
Lecturer: Lê Văn Thể ([@vvvanthe](https://github.com/vvvanthe))
 
## 2. Problem specification
 
The program groups anonymous in-store events into sessions, then computes dwell time, conversion rates and an interest score per product.
 
### Input
 
The program reads 2 CSV files from the data folder given on the command line. The first line of each file is a header.
 
| File | Columns | Notes |
| --- | --- | --- |
| `customer_events.csv` | `session_id,timestamp,event,product_id` | `event` is `ENTER`, `VIEW`, `PICK`, `RETURN`, `PURCHASE` or `EXIT`. Time is `HH:MM`. `ENTER`/`EXIT` have product `-` |
| `products.csv` | `product_id,name,category,brand,price,rating` | Used to validate product codes and print product names |
 
### Processing
 
1. Read `products.csv` into `vector<Product>`, sort it by `product_id` (hand-written sort).
2. Read `customer_events.csv` line by line. Each valid line finds its session or creates a new one (`findOrCreateSession`), so interleaved sessions are grouped correctly. Product codes are checked with a recursive binary search.
3. Count `VIEW`, `PICK`, `RETURN`, `PURCHASE` per session and for the whole store.
4. Dwell time = `EXIT − ENTER` in minutes. A session without `ENTER` or `EXIT`, or with `EXIT` before `ENTER`, shows `n/a`, is left out of the average, and the number of excluded sessions is reported.
5. Rates, printed with `fixed` + `setprecision(2)`:
   - View-to-Pick = total PICK / total VIEW × 100%
   - Pick-to-Purchase = total PURCHASE / total PICK × 100%
   - Store conversion = sessions with at least 1 PURCHASE / total sessions × 100%
6. Interest score per product: VIEW +1, PICK +3, RETURN −1, PURCHASE +5. Sorted descending; equal scores by `product_id` ascending.
### Output
 
The report is printed to `cout`:
 
- the session table (dwell, view, pick, return, purchase);
- store totals and the 3 rates;
- the session detail (products viewed, picked, returned, bought);
- the interest score table and the product with the strongest interest, with its name.
Warnings and errors go to `cerr`. A bad line is skipped with a warning that includes the file name and line number. A missing file or a missing argument prints an error, and the program exits with code `1`.
 
Extension: `--export <file.csv>` writes the session table to CSV with header `session_id,dwell_min,view,pick,return,purchase`. An `n/a` session leaves `dwell_min` empty.
 
## 3. Build and run
 
From the repository root:
 
```bash
mkdir bin
g++ -std=c++17 -Wall -Wextra src/main.cpp -o bin/p2
```
 
Run (macOS / Linux / Git Bash):
 
```bash
./bin/p2 data/sample
./bin/p2 data/full
./bin/p2 data/edge/empty
./bin/p2 data/edge/dirty
./bin/p2 data/sample --export sessions.csv
```
 
Run (Windows PowerShell):
 
```powershell
.\bin\p2 data/sample
```
 
Unit tests for `toMinutes`:
 
```bash
g++ -std=c++17 -Wall -Wextra -pedantic tests/test_t02b.cpp -o bin/test_t02b
./bin/test_t02b
```
 
Test cases TC01–TC07 and their results are in [`tests/test_cases.md`](tests/test_cases.md). Flowcharts and pseudocode for every code task are in [`docs/flowcharts/`](docs/flowcharts/).
 
## 4. Assumptions and limitations
 
- All times in one file belong to the same day (`00:00`–`23:59`). A session that crosses midnight is treated as `EXIT` before `ENTER`, so its dwell time is `n/a`.
- If a session has more than one `ENTER` or `EXIT`, the later line overwrites the earlier one.
- A line is skipped with a warning when it has the wrong number of columns, an unknown event (e.g. `SCAN`), a bad time (e.g. `25:61`), a product code not in `products.csv` (e.g. `P999`), or a `VIEW`/`PICK`/`RETURN`/`PURCHASE` without a product.
- In `products.csv`, a line with the wrong number of columns or a duplicate `product_id` is skipped with a warning; the first occurrence is kept.
- Blank lines (including a lone `\r` from Windows files) are skipped without a warning. Line numbers in warnings still count them.
- Product lists in the session detail keep every event in file order, so a product viewed twice appears twice.
- When a denominator is 0 (no VIEW, no PICK or no session), the rate is not divided.
- When no session has a valid dwell time, the average dwell is not computed (`averageDwell` returns `-1.0`) and is not printed as a number.
- `price` and `rating` are stored as text and are not used in calculations.
- Fields contain no commas, no quotes and no Vietnamese diacritics, as stated in the brief.
- The program only uses sessions 1–7 of the course: functions, `struct`, `vector`, strings, file reading, hand-written sort and search. No classes, pointers, `map`, `std::sort` or exceptions.
## 5. Out of scope (boundaries)
 
- The program only answers "what happened in the store". It does **not** link anonymous sessions to real customers, does **not** open `identity_links.csv` and does **not** try to infer customer identity.
- It does not read the other CSV files in the data folder (inventory, sales, promotions, transactions, feedback, store layout, daily store); they are not needed for P2.
- It does not edit the data files, does not predict behaviour and does not recommend products.
- It has no menu or interactive input; all input comes from the command line and the CSV files.
## 6. Task assignment table
 
| ID | Task | Function / file | Assignee | Reviewer | Flowchart | PR |
| --- | --- | --- | --- | --- | --- | --- |
| T01 | Repo skeleton + README | `.gitignore`, PR template, `README.md` | Triển | Yến | not needed | [#2](https://github.com/tienthinh202/smartretail-p2-group02/pull/2) |
| T02a | Flowchart + pseudocode of core function (M1) | `docs/flowcharts/T02-to-minutes.md` | Yến | Triển | yes | [#3](https://github.com/tienthinh202/smartretail-p2-group02/pull/3) |
| T02b | Convert HH:MM to minutes (code) | `toMinutes()` | Yến | Triển | yes | [#7](https://github.com/tienthinh202/smartretail-p2-group02/pull/7) |
| T03 | Structs + read products.csv + main | `splitCsv()`, `containsProduct()`, `loadProducts()`, `main()` | Triển | Trâm | yes | [#8](https://github.com/tienthinh202/smartretail-p2-group02/pull/8) |
| T04 | Sort + recursive binary search | `sortProducts()`, `binarySearch()`, `findProduct()` | Trâm | Kiên | yes | [#10](https://github.com/tienthinh202/smartretail-p2-group02/pull/10) |
| T05 | Read and validate customer_events.csv | `isValidEvent()`, `checkEventLine()`, `loadEvents()` | Triển | Yến | yes | |
| T06 | Group events into sessions | `findOrCreateSession()`, `applyEvent()` | Kiên | Triển | yes | [#12](https://github.com/tienthinh202/smartretail-p2-group02/pull/12) |
| T07 | Dwell time + average | `dwellTime()`, `averageDwell()` | Kiên | Trâm | yes | |
| T08 | Conversion rates + store totals | `percent()`, `computeTotals()` | Yến | Kiên | yes | |
| T09 | Interest score per product | `findOrCreateInterest()`, `addInterest()` | Kiên | Yến | yes | |
| T10 | Sort interest scores | `comesBefore()`, `sortInterest()` | Trâm | Triển | yes | |
| T11 | Print session table + totals | `printSessionTable()`, `printTotals()` | Yến | Trâm | yes | |
| T12 | Print session detail + interest + report | `joinList()`, `printSessionDetail()`, `explainInterest()`, `printInterest()`, `printReport()` | Trâm | Yến | yes | |
| T13 | Extension `--export` | `exportCsv()` | Triển | Kiên | yes | |
| T14 | Test cases TC01–TC07 (Expected) | `tests/test_cases.md`, `tests/expected/`, `tests/run_tests.sh` | Yến | Trâm | not needed | |
| T15 | Architecture document | `docs/architecture.md` | Trâm | Triển | not needed | |
| T16 | Slides | `docs/slides.pdf` | Kiên | Triển | not needed | |
| T17 | README sections + AI declaration | `README.md`, `.gitignore` | Triển | Kiên | not needed | |
| T18 | Run all tests, fill Actual + Pass/Fail | `tests/test_cases.md` | Yến | Kiên | not needed | |
 
## 7. AI use and references
 
### AI tools
 
Each member states which tool they used, for what, and which part of the code or documents it suggested. Every PR also declares AI use in its "AI tools / references" section.
 
The shared design in [`docs/flowcharts/00-thiet-ke-chung.md`](docs/flowcharts/00-thiet-ke-chung.md) (struct layout, function names and signatures, flowchart conventions) was prepared with the help of Claude (Anthropic), as stated in that file. Every member's flowcharts follow it.
 
| Member | Tool | What it was used for | Parts affected |
| --- | --- | --- | --- |
| Triển | Claude (Anthropic) | Planning the task split; guidance on Git/GitHub workflow; suggesting the struct layout, `splitCsv`, `containsProduct`, `loadProducts` and `main` for T03; drawing the T03 flowcharts; reviewing teammates' PRs; drafting this README | T01, T03, T17, review comments. Code was typed, built and tested by Triển |
| Yến | Declared per PR | Each PR states the tool and the part it suggested in its "AI tools / references" section | T02a, T02b: see [#3](https://github.com/tienthinh202/smartretail-p2-group02/pull/3), [#7](https://github.com/tienthinh202/smartretail-p2-group02/pull/7), [#13](https://github.com/tienthinh202/smartretail-p2-group02/pull/13) |
| Trâm | Claude (Anthropic) | Suggesting code, pseudocode and flowcharts for T04 | T04. Code was read, built, tested and checked against the flowcharts by Trâm |
| Kiên | Declared per PR | Each PR states the tool and the part it suggested in its "AI tools / references" section | T06: see [#12](https://github.com/tienthinh202/smartretail-p2-group02/pull/12) |
 
### References
 
- Project brief P2 – Customer Journey Analyzer and the submission guide (MiiN-SmartRetail).
- Course slides, sessions 1–7.
- [cppreference.com](https://en.cppreference.com/) for `ifstream`, `getline`, `string::substr`, `fixed` and `setprecision`.
- [draw.io](https://app.diagrams.net/) for flowcharts.
 