#include "Date.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

// ---------- Internal helpers (not part of class) ----------
static bool validYMD(int y, int m, int d) {
    if (y < 0) return false;
    if (m < 1 || m > 12) return false;

    static const int base[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    bool leap = (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
    int dim = (m == 2) ? (leap ? 29 : 28) : base[m];

    return d >= 1 && d <= dim;
}

// ---------- Static utilities ----------
bool Date::isLeapYear(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

int Date::daysInMonth(int y, int m) {
    if (m < 1 || m > 12) throw std::out_of_range("Out of Range");
    static const int base[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    return (m == 2) ? (isLeapYear(y) ? 29 : 28) : base[m];
}

bool Date::isValid(int y, int m, int d) {
    return validYMD(y, m, d);
}

// ---------- Constructors ----------
Date::Date() : year(1970), month(1), day(1) {}

Date::Date(int y, int m, int d) {
    if (!validYMD(y, m, d)) throw std::out_of_range("Out of Range");
    year = y; month = m; day = d;
}

Date::Date(std::string formatted_date) {
    int m = 0, d = 0, y = 0;
    char s1 = 0, s2 = 0;
    std::istringstream in(formatted_date);
    if (!(in >> m >> s1 >> d >> s2 >> y) || s1 != '/' || s2 != '/') {
        throw std::out_of_range("Out of Range");
    }
    if (!validYMD(y, m, d)) throw std::out_of_range("Out of Range");
    year = y; month = m; day = d;
}

// ---------- Getters ----------
int Date::getDay()   const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear()  const { return year; }

// ---------- Setters ----------
void Date::setDay(int d) {
    if (!validYMD(year, month, d)) throw std::out_of_range("Out of Range");
    day = d;
}

void Date::setMonth(int m) {
    if (!validYMD(year, m, day)) throw std::out_of_range("Out of Range");
    month = m;
}

void Date::setYear(int y) {
    if (!validYMD(y, month, day)) throw std::out_of_range("Out of Range");
    year = y;
}

void Date::setDate(int y, int m, int d) {
    if (!validYMD(y, m, d)) throw std::out_of_range("Out of Range");
    year = y; month = m; day = d;
}

// ---------- String ----------
std::string Date::toString() const {
    std::ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << month
       << '/' << std::setw(2) << std::setfill('0') << day
       << '/' << std::setw(4) << std::setfill('0') << year;
    return ss.str();
}

// ---------- Comparisons ----------
bool Date::operator==(const Date& rhs) const {
    return year == rhs.year && month == rhs.month && day == rhs.day;
}
bool Date::operator!=(const Date& rhs) const { return !(*this == rhs); }
bool Date::operator<(const Date& rhs)  const {
    if (year  != rhs.year)  return year  < rhs.year;
    if (month != rhs.month) return month < rhs.month;
    return day < rhs.day;
}
bool Date::operator<=(const Date& rhs) const { return !(*this > rhs); }
bool Date::operator>(const Date& rhs)  const { return rhs < *this; }
bool Date::operator>=(const Date& rhs) const { return !(*this < rhs); }

// ---------- Stream output ----------
std::ostream& operator<<(std::ostream& out, const Date& date) {
    out << std::setw(2) << std::setfill('0') << date.getMonth()
        << '/' << std::setw(2) << std::setfill('0') << date.getDay()
        << '/' << std::setw(4) << std::setfill('0') << date.getYear();
    return out;
}
