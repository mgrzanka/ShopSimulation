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
};
std::ostream& operator<<(std::ostream& os, const Money& money);
Money& operator-=(Money& first, const Money& second);
Money operator+(Money& first, const Money& second);
Money operator*(const Money& first, int number);
bool operator<(Money& first, const Money& second);

struct StoreTime
{
    unsigned int minutes;
    float minutes_per_iteration = 15.0;
    StoreTime(unsigned int minutes);
    unsigned int get_iterations() const;
};
std::ostream& operator<<(std::ostream& os, const StoreTime& time_spent);

#endif