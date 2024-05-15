#include <iostream>
#include <cmath>

#include "Structures.hpp"



unsigned int Money::get_whole_part()
{
    return int(full_price / 100);
}

unsigned int Money::get_cents()
{
    return int(full_price % 100);
}

unsigned int StoreTime::get_iterations(unsigned int minutes)
{
    return static_cast<unsigned int>(ceil(minutes/minutes_per_iteration));
}
