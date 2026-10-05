#ifndef DATE_H
#define DATE_H

#include <ostream>

// ---------------------------------------------------------------
// Date : a simple day/month/year value.                     (M4)
// ---------------------------------------------------------------
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date();                        // default constructor: today's date
    Date(int d, int m, int y);     // parameterised constructor

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    // operator overloading
    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;

    // friend: not a member, but allowed to read day/month/year directly
    friend std::ostream& operator<<(std::ostream& out, const Date& d);
};

#endif
