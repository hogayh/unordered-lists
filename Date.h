#ifndef DATE_H
#define DATE_H

#include <string>
#include <ostream>

/**
 * @brief Represents a calendar date (month/day/year).
 */
class Date {
private:
    int year;
    int month;
    int day;

public:
    // ---- Constructors ----
    Date();                                 // Default: 01/01/1970
    Date(int year, int month, int day);     // From integers
    Date(std::string formatted_date);       // From "MM/DD/YYYY"

    // ---- Getters ----
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    // ---- Setters ----
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
    void setDate(int year, int month, int day);

    // ---- String ----
    std::string toString() const;

    // ---- Comparison operators ----
    bool operator==(const Date &rhs) const;
    bool operator!=(const Date &rhs) const;
    bool operator<(const Date &rhs) const;
    bool operator<=(const Date &rhs) const;
    bool operator>(const Date &rhs) const;
    bool operator>=(const Date &rhs) const;

    // ---- Utilities ----
    static bool isValid(int year, int month, int day);

private:
    static bool isLeapYear(int year);
    static int  daysInMonth(int year, int month);
};

// ---- Non-member stream operator ----
std::ostream &operator<<(std::ostream &out, const Date &date);

#endif // DATE_H