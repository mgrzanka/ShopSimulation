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
    double temp = 1.23 * price_netto.full_price;
    unsigned int final_price = (int)temp;
    if(final_price == 0)
    {
        throw std::invalid_argument("Wrong price");
    }
    return Money(final_price);
}

bool Beverage::operator==(const Beverage& other) const {
    return name == other.name && price_netto == other.price_netto.full_price;
}
