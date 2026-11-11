
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ==========================================
// SECTION 1: STRUCTS - A (TEAM LEADER)
// ==========================================

struct Product {
    string id;
    string name;
    string category;
    string brand;
    double price = 0;
    double rating = 0;
};

struct Event {
    string sessionId;
    string timestamp;
    string eventType;
    string productId;
};

struct Session {
    string id;
    int enter = -1;
    int exit = -1;

    int views = 0;
    int picks = 0;
    int returns = 0;
    int purchases = 0;
};

struct Interest {
    string productId;
    int score = 0;
};

// ==========================================
// SECTION 2: FUNCTION PROTOTYPES
// ==========================================

// T01 - A
bool toMinutes(const string& time, int& minutes);

// T02 - A
double percent(int numerator, int denominator);

// T03 - B
bool loadProducts(const string& path,
                  vector<Product>& products);

// T04 - B
int binarySearch(const vector<Product>& products,
                 const string& id,
                 int left, int right);

// T05 - C
bool loadEvents(const string& path,
                vector<Event>& events,
                const vector<Product>& products);

// T06 - C
void printReport(const vector<Session>& sessions,
                 const vector<Product>& products,
                 const vector<Interest>& interests);

// T07 - D
int findOrCreateSession(vector<Session>& sessions,
                        const string& id);

// T08 - D
void addInterest(vector<Interest>& interests,
                 const string& productId,
                 int points);

void sortInterest(vector<Interest>& interests);

// ==========================================
// SECTION 3: T01 - A
// Convert HH:MM to minutes
// ==========================================



// ==========================================
// SECTION 4: T02 - A
// Calculate dwell time and conversion rates
// ==========================================



// ==========================================
// SECTION 5: T03 - B
// Read products.csv
// ==========================================



// ==========================================
// SECTION 6: T04 - B
// Recursive binary search
// ==========================================



// ==========================================
// SECTION 7: T05 - C
// Read customer_events.csv
// ==========================================



// ==========================================
// SECTION 8: T06 - C
// Print final report
// ==========================================



// ==========================================
// SECTION 9: T07 - D
// Find or create session
// ==========================================



// ==========================================
// SECTION 10: T08 - D
// Calculate and sort interest scores
// ==========================================



// ==========================================
// SECTION 11: MAIN FUNCTION - A
// ==========================================

int main(int argc, char* argv[]) {

    // TODO: Process command line arguments

    // TODO: Load products

    // TODO: Load events

    // TODO: Group events into sessions

    // TODO: Calculate statistics

    // TODO: Calculate interest scores

    // TODO: Print report

    return 0;
}
