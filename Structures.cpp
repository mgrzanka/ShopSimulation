#include <cmath>
#include <stdexcept>

#include "Structures.hpp"


// Money structure
unsigned int Money::get_whole_part() const
{
    return int(full_price / 100);
}

unsigned int Money::get_cents() const
{
    return int(full_price % 100);
}

Money::Money(): full_price{0} {}

Money::Money(unsigned int full_price): full_price{full_price} {}
std::ostream& operator<<(std::ostream& os, const Money& money)
{
    return os<<money.get_whole_part()<<"."<<money.get_cents()<<money.currency_name;
}
Money& operator-=(Money& first, const Money& second)
{
    unsigned int new_full_price = first.full_price - second.full_price;
    first.full_price = new_full_price;
    return first;
}
Money& operator+=(Money& first, const Money& second)
{
    unsigned int new_full_price = first.full_price + second.full_price;
    first.full_price = new_full_price;
    return first;
}

Money operator+(Money& first, const Money& second)
{
    unsigned int new_full_price = first.full_price + second.full_price;
    Money new_price(new_full_price);
    return new_price;
}
bool operator<(Money& first, const Money& second)
{
    return first.full_price < second.full_price;
}

Money operator*(const Money& first, int number)
{
    unsigned int new_full_price = first.full_price * number;
    Money new_price(new_full_price);
    return new_price;
}

Money operator+(const Money& first, const Money& second)
{
    return first.full_price + second.full_price;
}

// StoreTime structure
StoreTime::StoreTime(unsigned int minutes)
{
    if(minutes == 0) throw std::invalid_argument("You can't spent 0 minutes in the store!");
    this->minutes = minutes;
}

unsigned int StoreTime::get_iterations() const
{
    return static_cast<unsigned int>(ceil(minutes/minutes_per_iteration));
}
std::ostream& operator<<(std::ostream& os, const StoreTime& time_spent)
{
    return os<<time_spent.minutes<<" minutes";
}
