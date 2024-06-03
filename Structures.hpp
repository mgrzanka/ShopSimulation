#ifndef _STRUCTURES_HPP_
#define _STRUCTURES_HPP_
#include <iostream>
#include <ostream>



struct Money
{
    std::string currency_name;
    unsigned int full_price;
    Money();
    Money(unsigned int full_price);
    unsigned int get_whole_part() const;
    unsigned int get_cents() const;
    bool operator==(const Money& second) const;
};
std::ostream& operator<<(std::ostream& os, const Money& money);
Money& operator-=(Money& first, const Money& second);
Money& operator+=(Money& first, const Money& second);
Money operator+(Money& first, const Money& second);
Money operator*(const Money& first, int number);
Money operator+(const Money& first, const Money& second);
bool operator<(Money& first, const Money& second);
bool operator>(Money& first, const Money& second);

struct StoreTime
{
    unsigned int minutes;
    float minutes_per_iteration = 15.0;
    StoreTime(unsigned int minutes);
    unsigned int get_iterations() const;
    unsigned int get_minutes(unsigned int iterations);
    bool operator==(const StoreTime& second) const;
    bool operator>=(const StoreTime& other) const;
};
StoreTime operator+(const StoreTime& first, const StoreTime& second);
bool operator>(const StoreTime& one, const StoreTime& other);
std::ostream& operator<<(std::ostream& os, const StoreTime& time_spent);
StoreTime operator-(const StoreTime& first, const StoreTime& second);

#endif