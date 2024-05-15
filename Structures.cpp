#include <cmath>

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
bool operator<(Money& first, const Money& second)
{
    return first.full_price < second.full_price;
}


// StoreTime structure
StoreTime::StoreTime(unsigned int minutes): minutes{minutes} {}

unsigned int StoreTime::get_iterations() const
{
    return static_cast<unsigned int>(ceil(minutes/minutes_per_iteration));
}
std::ostream& operator<<(std::ostream& os, const StoreTime& time_spent)
{
    return os<<time_spent.minutes<<" minutes";
}
