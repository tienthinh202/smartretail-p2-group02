# Thiết kế chung – P2 Customer Journey Analyzer

Mọi flowchart trong thư mục này dùng đúng tên struct, tên hàm và tên biến dưới đây. Ai code task nào thì khai báo đúng chữ ký hàm như bảng, để code khớp flowchart (thầy trừ điểm nếu flowchart không khớp code). Nếu khi code bạn đổi logic, phải sửa lại flowchart của mình trong cùng PR.

## Struct (T03 – Triển khai báo ở đầu `src/main.cpp`)

```cpp
struct Product {
    string id, name, category, brand, price, rating;   // giữ dạng chuỗi, chỉ cần id và name
};

struct Session {
    string id;
    int enter = -1, exit = -1;          // -1 = chưa thấy ENTER/EXIT
    int views = 0, picks = 0, returns = 0, purchases = 0;
    vector<string> viewed, picked, returned, bought;
};

struct Interest {
    string productId;
    int views = 0, picks = 0, returns = 0, purchases = 0, score = 0;
};

struct Totals {
    int views = 0, picks = 0, returns = 0, purchases = 0, buyers = 0, sessions = 0;
    double viewToPick = 0.0, pickToPurchase = 0.0, conversion = 0.0;
};
```

## Chữ ký hàm theo task

| Task | Người làm | Hàm |
| --- | --- | --- |
| T02 | Yến | `bool toMinutes(const string& text, int& minutes, string& error)` |
| T03 | Triển | `vector<string> splitCsv(const string& line)` · `bool containsProduct(const vector<Product>& products, const string& id)` · `bool loadProducts(const string& path, vector<Product>& products)` · `int main(int argc, char* argv[])` |
| T04 | Trâm | `void sortProducts(vector<Product>& products)` · `int binarySearch(const vector<Product>& products, const string& id, int lo, int hi)` (đệ quy) · `int findProduct(const vector<Product>& products, const string& id)` |
| T05 | Triển | `bool isValidEvent(const string& ev)` · `bool checkEventLine(const vector<string>& f, const vector<Product>& products, int& minutes, string& error)` · `bool loadEvents(const string& path, const vector<Product>& products, vector<Session>& sessions, vector<Interest>& interests)` |
| T06 | Kiên | `int findOrCreateSession(vector<Session>& sessions, const string& id)` · `void applyEvent(Session& s, const string& ev, int minutes, const string& pid)` |
| T07 | Kiên | `int dwellTime(const Session& s)` (-1 = n/a) · `double averageDwell(const vector<Session>& sessions, int& excluded)` (-1.0 = không có phiên hợp lệ) |
| T08 | Yến | `double percent(int a, int b)` · `void computeTotals(const vector<Session>& sessions, Totals& t)` |
| T09 | Kiên | `int findOrCreateInterest(vector<Interest>& interests, const string& pid)` · `void addInterest(vector<Interest>& interests, const string& pid, const string& ev)` |
| T10 | Trâm | `bool comesBefore(const Interest& a, const Interest& b)` · `void sortInterest(vector<Interest>& v)` |
| T11 | Yến | `void printSessionTable(const vector<Session>& sessions)` · `void printTotals(const Totals& t, double avg, int excluded)` |
| T12 | Trâm | `string joinList(const vector<string>& list)` · `void printSessionDetail(const vector<Session>& sessions)` · `string explainInterest(const Interest& it)` · `void printInterest(const vector<Interest>& interests, const vector<Product>& products)` · `void printReport(...)` |
| T13 | Triển | `bool exportCsv(const string& path, const vector<Session>& sessions)` |

Vì toàn bộ chương trình nằm trong một tệp, nên đặt khai báo prototype của mọi hàm ngay sau các struct (T03 thêm sẵn). Như vậy ai cũng gọi được hàm của người khác dù hàm đó viết ở dưới.

## Sơ đồ gọi hàm (dùng cho `docs/architecture.md`)

```
main
├── loadProducts
│   ├── splitCsv
│   └── containsProduct      (bỏ product_id trùng)
├── sortProducts
├── loadEvents
│   ├── splitCsv
│   ├── checkEventLine
│   │   ├── isValidEvent
│   │   ├── toMinutes
│   │   └── findProduct
│   │       └── binarySearch      (đệ quy)
│   ├── findOrCreateSession
│   ├── applyEvent
│   └── addInterest
│       └── findOrCreateInterest
├── computeTotals
│   └── percent
├── averageDwell
│   └── dwellTime
├── sortInterest
│   └── comesBefore
├── printReport
│   ├── printSessionTable
│   │   └── dwellTime
│   ├── printTotals
│   ├── printSessionDetail
│   │   └── joinList
│   └── printInterest
│       ├── explainInterest
│       └── findProduct
└── exportCsv                     (chỉ khi có --export)
    └── dwellTime
```

## Danh sách flowchart

| Tệp | Hàm |
| --- | --- |
| [T02-to-minutes.md](T02-to-minutes.md) | toMinutes |
| [T03-load-products.md](T03-load-products.md) | main, splitCsv, containsProduct, loadProducts |
| [T04-sort-binary-search.md](T04-sort-binary-search.md) | sortProducts, binarySearch, findProduct |
| [T05-load-events.md](T05-load-events.md) | isValidEvent, checkEventLine, loadEvents |
| [T06-sessions.md](T06-sessions.md) | findOrCreateSession, applyEvent |
| [T07-dwell.md](T07-dwell.md) | dwellTime, averageDwell |
| [T08-totals.md](T08-totals.md) | percent, computeTotals |
| [T09-interest.md](T09-interest.md) | findOrCreateInterest, addInterest |
| [T10-sort-interest.md](T10-sort-interest.md) | comesBefore, sortInterest |
| [T11-print-table.md](T11-print-table.md) | printSessionTable, printTotals |
| [T12-print-detail.md](T12-print-detail.md) | joinList, printSessionDetail, explainInterest, printInterest, printReport |
| [T13-export.md](T13-export.md) | exportCsv |

## Quy ước đã áp dụng (mục 2.6)

- Một ô Bắt đầu ghi tên hàm và tham số; ô Kết thúc ghi giá trị trả về (`return ...`).
- Mỗi ô điều kiện có đúng hai nhánh, nhãn Yes / No; chữ trong ô dùng đúng phép so sánh trong code.
- Vòng lặp: mũi tên quay ngược về ô điều kiện của vòng lặp. Đường đi không cắt nhau.
- Gọi hàm con đã có flowchart riêng: ký hiệu Gọi hàm con (hình chữ nhật hai vạch dọc). Nhập/xuất (`getline`, `cout`, `cerr`): hình bình hành.
- Không dùng Mermaid. Mỗi hình là tệp `.drawio.png` có kèm bản sơ đồ, mở lại được trong draw.io; tệp `.drawio` cùng tên là bản dự phòng.

## Khai báo AI (bắt buộc)

Các flowchart và mã giả này được tạo với sự hỗ trợ của Claude (Anthropic). Mỗi PR có flowchart phải ghi vào mục "AI tools / references", ví dụ: *"Flowchart + pseudocode của T07 tạo bằng Claude từ thiết kế chung của nhóm; tôi đã đối chiếu với code và sửa ..."*. README cũng phải có dòng này. Không khai báo là vi phạm liêm chính học thuật.
