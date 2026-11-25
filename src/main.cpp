#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Each member writes only inside their own section.
// Function names and parameters follow docs/flowcharts/00-thiet-ke-chung.md

// ===== T03 – structs + function prototypes (Trien) =====
struct Product {
    string id;
    string name;
    string category;
    string brand;
    string price;
    string rating;
};

struct Session {
    string id;
    int enter = -1;
    int exit = -1;
    int views = 0;
    int picks = 0;
    int returns = 0;
    int purchases = 0;
    vector<string> viewed;
    vector<string> picked;
    vector<string> returned;
    vector<string> bought;
};

struct Interest {
    string productId;
    int views = 0;
    int picks = 0;
    int returns = 0;
    int purchases = 0;
    int score = 0;
};

struct Totals {
    int views = 0;
    int picks = 0;
    int returns = 0;
    int purchases = 0;
    int buyers = 0;
    int sessions = 0;
    double viewToPick = 0.0;
    double pickToPurchase = 0.0;
    double conversion = 0.0;
};

bool toMinutes(const string& text, int& minutes, string& error);
vector<string> splitCsv(const string& line);
bool containsProduct(const vector<Product>& products, const string& id);
bool loadProducts(const string& path, vector<Product>& products);
void sortProducts(vector<Product>& products);
int binarySearch(const vector<Product>& products, const string& id, int lo, int hi);
int findProduct(const vector<Product>& products, const string& id);
bool isValidEvent(const string& ev);
bool checkEventLine(const vector<string>& f, const vector<Product>& products, int& minutes, string& error);
bool loadEvents(const string& path, const vector<Product>& products, vector<Session>& sessions, vector<Interest>& interests);
int findOrCreateSession(vector<Session>& sessions, const string& id);
void applyEvent(Session& s, const string& ev, int minutes, const string& pid);
int dwellTime(const Session& s);
double averageDwell(const vector<Session>& sessions, int& excluded);
double percent(int a, int b);
void computeTotals(const vector<Session>& sessions, Totals& t);
int findOrCreateInterest(vector<Interest>& interests, const string& pid);
void addInterest(vector<Interest>& interests, const string& pid, const string& ev);
bool comesBefore(const Interest& a, const Interest& b);
void sortInterest(vector<Interest>& v);
void printSessionTable(const vector<Session>& sessions);
void printTotals(const Totals& t, double avg, int excluded);
string joinList(const vector<string>& list);
void printSessionDetail(const vector<Session>& sessions);
string explainInterest(const Interest& it);
void printInterest(const vector<Interest>& interests, const vector<Product>& products);
void printReport(const vector<Session>& sessions, const Totals& t, double avg, int excluded, const vector<Interest>& interests, const vector<Product>& products);
bool exportCsv(const string& path, const vector<Session>& sessions);

// ===== T02 – toMinutes (Yen) =====
bool toMinutes(const string& text, int& minutes, string& error) {
    if (text.length() != 5) {
        error = "Time must contain exactly 5 characters";
        return false;
    }

    if (text[2] != ':') {
        error = "Time must use HH:MM format";
        return false;
    }

        int i = 0;
    while (i <= 4) {
        if (i != 2) {
            if (text[i] < '0' || text[i] > '9') {
                error = "Hour and minute must contain only digits";
                return false;
            }
        }
        i = i + 1;
    }
    string hourText = text.substr(0,2);
    string minuteText = text.substr(3,2);

    int hour = (hourText[0] - '0') * 10 + (hourText[1] - '0'); // - '0': turn a digit character to a number: '0' start with 48, cont, ex: '5' is 53, 53 - 48 is exactly 5, if it dont have - '0' the number will be 53.
    int minute = (minuteText[0] - '0') * 10 + (minuteText[1] - '0');

        if (hour > 23) {
        error = "Hour must be between 00 and 23";
        return false;
    }
    }

        if (minute > 59) {
        error = "Minute must be between 00 and 59";
        return false;
    }

    minutes = hour * 60 + minute;
    error = "";
    return true;
}


// ===== T03 – splitCsv, loadProducts (Trien) =====
vector<string> splitCsv(const string& line) {
    vector<string> fields;
    string field = "";
    int i = 0;
    while (i < (int)line.length()) {
        if (line[i] == ',') {
            fields.push_back(field);
            field = "";
        } else if (line[i] != '\r') {
            field = field + line[i];
        }
        i = i + 1;
    }
    fields.push_back(field);
    return fields;
}

bool containsProduct(const vector<Product>& products, const string& id) {
    int i = 0;
    while (i < (int)products.size()) {
        if (products[i].id == id) {
            return true;
        }
        i = i + 1;
    }
    return false;
}
bool loadProducts(const string& path, vector<Product>& products) {
    ifstream fin(path);
    if (!fin) {
        cerr << "Error: cannot open " << path << endl;
        return false;
    }

    string line;
    getline(fin, line); // skip header
    int lineNo = 1;

    while (getline(fin, line)) {
        lineNo = lineNo + 1;
        if (line != "" && line != "\r") {
            vector<string> fields = splitCsv(line);

            if (fields.size() != 6) {
                cerr << "Warning: products.csv line " << lineNo << ": expected 6 columns, found " << fields.size() << " -> skipped" << endl;
            } else if (containsProduct(products, fields[0])) {
                cerr << "Warning: products.csv line " << lineNo << ": duplicate product_id " << fields[0] << " -> skipped" << endl;
            } else {
                Product p;
                p.id = fields[0];
                p.name = fields[1];
                p.category = fields[2];
                p.brand = fields[3];
                p.price = fields[4];
                p.rating = fields[5];
                products.push_back(p);
            }
        }
    }
    return true;
}

// ===== T04 – sortProducts, binarySearch, findProduct (Tram) =====

// ===== T05 – isValidEvent, checkEventLine, loadEvents (Trien) =====

// ===== T06 – findOrCreateSession, applyEvent (Kien) =====

// ===== T07 – dwellTime, averageDwell (Kien) =====

// ===== T08 – percent, computeTotals (Yen) =====

// ===== T09 – findOrCreateInterest, addInterest (Kien) =====

// ===== T10 – comesBefore, sortInterest (Tram) =====

// ===== T11 – printSessionTable, printTotals (Yen) =====

// ===== T12 – joinList, printSessionDetail, explainInterest, printInterest, printReport (Tram) =====

// ===== T13 – exportCsv (Trien) =====

// ===== T03 – main (Trien) =====
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: p2 <data_folder> [--export <file.csv>]" << endl;
        return 1;
    }

    string folder = argv[1];
    vector<Product> products;

    bool ok = loadProducts(folder + "/products.csv", products);
    if (!ok) {
        return 1;
    }

    return 0;
}
