#include "Product.hpp"
#include <iostream>

Product::Product(std::string new_name, Money new_price_netto) :
name{new_name}, price_netto{new_price_netto}
{
    if (new_name.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }

    if(new_price_netto.full_price == 0)
    {
        throw std::invalid_argument("Zero price value");
    }
}

std::string Product::get_name() const
{
    return name;
}

Money Product::get_price_netto() const
{
    return price_netto;
}


void Product::set_name(std::string new_name)
        {
            if (new_name.length() != 0)
            {name = new_name;}
            else
            {
                throw std::invalid_argument("Wrong name");
            }
        }

void Product::set_price_netto(double new_price_netto)
    {
        if (new_price_netto <= 0)
        {
            throw std::invalid_argument("Wrong price");
        }
        else
        {price_netto = new_price_netto;}
    }

Money Product::calculate_price() const
{
    return Money(price_netto);
}

int Product::find_shelf() const
{
    return 0;
}
