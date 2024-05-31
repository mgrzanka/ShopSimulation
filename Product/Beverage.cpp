#include "Beverage.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

Beverage::Beverage(std::string name, Money price_netto) :
Product{name, price_netto}
{}

int Beverage::find_shelf() const
{
    if (name.length() <= 5)
    {return 439;}
    else
    {return 440;}
}

Money Beverage::calculate_price() const
{
    unsigned int final_price = 1.23 * price_netto.full_price;
    if(final_price == 0)
    {
        throw std::invalid_argument("Wrong price");
    }
    return Money(final_price);
}
