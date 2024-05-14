#ifndef _STRUCTURES_HPP_
#define _STRUCTURES_HPP_
#include <iostream>



struct Money
{
    std::string currency_name;
    int full_price;
    int get_whole_part();
    int get_cents();
};

struct StoreTime
{
    float minutes_per_iteration = 5.0;
    int get_iterations(int minutes);
};

#endif