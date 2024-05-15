#ifndef _STRUCTURES_HPP_
#define _STRUCTURES_HPP_
#include <iostream>



struct Money
{
    std::string currency_name;
    unsigned int full_price;
    unsigned int get_whole_part();
    unsigned int get_cents();
};

struct StoreTime
{
    float minutes_per_iteration = 5.0;
    unsigned int get_iterations(unsigned int minutes);
};

#endif