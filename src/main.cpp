#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Each member writes only inside their own section.
// TODO: function names and parameters will follow docs/flowcharts/00-thiet-ke-chung.md (not added yet)

// ===== T03 – structs + function prototypes (Trien) =====

// ===== T02 – toMinutes (Yen) =====
bool toMinutes(const string& text, int& minutes, string& error) {
    if (text.length() != 5) {
        error = "Time must contain exactly 5 characters";
        return false;
    }

    if (text[2] != ':') {
    error ="Time must use HH:MM format";
    return false;
    }

    int i = 0;
    while (i <= 4) {
         if (i !=2) {
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

    int (hour > 23) {
         error = "Hour must be between 00 and 23";
         return false;
    }

    if (minute > 59) {
        error = "Minute must bewteen 00 and 59";
        return false;
    }

    minutes = hour * 60 + minute;
    error = "";
    return true;
}


// ===== T03 – splitCsv, loadProducts (Trien) =====

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
int main() {
    return 0;
}
