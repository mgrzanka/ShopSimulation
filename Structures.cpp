#include <iostream>
#include <cmath>

#include "Structures.hpp"



int Money::get_whole_part()
{
    return int(full_price / 100);
}

int Money::get_cents()
{
    return int(full_price % 100);
}

int StoreTime::get_iterations(int minutes)
{
    return static_cast<int>(ceil(minutes/minutes_per_iteration));
}
