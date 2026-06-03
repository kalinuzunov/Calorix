#include "Date.h"
#include "../Constants.h"
#include "CalorixExceptions.h"
#include <string>

using namespace Constants;

static const unsigned DAYS_IN_MONTHS[DateLimits::MAX_MONTHS + 1] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

bool Date::isLeapYear(unsigned y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

unsigned Date::getDaysInMonth(unsigned m, unsigned y) const {
    if (m == DateLimits::FEBRUARY_INDEX) {
        return DAYS_IN_MONTHS[DateLimits::FEBRUARY_INDEX] + isLeapYear(y);
    }
    return DAYS_IN_MONTHS[m];
}

bool Date::isValid(unsigned y, unsigned m, unsigned d) const {
    if (y == 0 || m == 0 || m > DateLimits::MAX_MONTHS || d == 0) return false;
    return d <= getDaysInMonth(m, y);
}

Date::Date()
    : year(DateLimits::DEFAULT_YEAR), month(DateLimits::DEFAULT_MONTH), day(DateLimits::DEFAULT_DAY) {}

Date::Date(unsigned y, unsigned m, unsigned d) {
    if (!isValid(y, m, d)) {
        throw InvalidDateException("Invalid date provided!");
    }
    year = y;
    month = m;
    day = d;
}

Date::Date(const std::string& dateString) {
    if (dateString.length() != DateLimits::EXPECTED_STRING_LENGTH ||
        dateString[4] != '-' || dateString[7] != '-') {
        throw InvalidDateException("Invalid date format! Expected: YYYY-MM-DD");
    }

    try {
        unsigned y = std::stoi(dateString.substr(DateLimits::YEAR_START_INDEX, DateLimits::YEAR_LENGTH));
        unsigned m = std::stoi(dateString.substr(DateLimits::MONTH_START_INDEX, DateLimits::MONTH_LENGTH));
        unsigned d = std::stoi(dateString.substr(DateLimits::DAY_START_INDEX, DateLimits::DAY_LENGTH));

        if (!isValid(y, m, d)) {
            throw InvalidDateException("Invalid date values provided!");
        }

        year = y;
        month = m;
        day = d;
    }
    catch (const std::exception& e) {
        throw InvalidDateException("Date string contains invalid characters or numbers out of range.");
    }
}

unsigned Date::getYear() const {
    return year;
}
unsigned Date::getMonth() const {
    return month;
}
unsigned Date::getDay() const {
    return day;
}

std::string Date::toString() const {
    std::string result = std::to_string(year) + "-";
    if (month < 10) result += "0";
    result += std::to_string(month) + "-";
    if (day < 10) result += "0";
    result += std::to_string(day);
    return result;
}