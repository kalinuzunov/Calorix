#pragma once
#include <string>
#include <stdexcept>

class Date {
private:
    unsigned year;
    unsigned month;
    unsigned day;

    bool isLeapYear(unsigned y) const;
    unsigned getDaysInMonth(unsigned m, unsigned y) const;
    bool isValid(unsigned y, unsigned m, unsigned d) const;

public:
    Date();
    Date(unsigned y, unsigned m, unsigned d);
    Date(const std::string& dateString);

    unsigned getYear() const;
    unsigned getMonth() const;
    unsigned getDay() const;

    std::string toString() const;
};