#pragma once

struct Date {
    int day;
    int month;
    int year;

    bool operator<(const Date& rhs) const {
        if(year != rhs.year) {
            return year < rhs.year;
        } else if(month != rhs.month) {
            return month < rhs.month;
        } else {
            return day < rhs.day;
        }
    }
    bool operator==(const Date& rhs) const {
        return ((year == rhs.year) && (month == rhs.month) && (day == rhs.day));
    }
    bool operator>(const Date& rhs) const {
        if(*this == rhs) {
            return false;
        } else {
            return !(*this < rhs);
        }
    }
    bool operator!=(const Date& rhs) const {
        return !(*this == rhs);
    }
};