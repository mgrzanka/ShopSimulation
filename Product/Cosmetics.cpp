#include "Cosmetics.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

Cosmetics::Cosmetics(std::string name, Money price_netto, char type) :
Product{name, price_netto},
type{type}
{}

int Cosmetics::find_shelf() const
{
    if (type == 'F') return 578;
    else if (type == 'M') return 579;
    else return 580;
}

Money Cosmetics::calculate_price() const
{
    double temp =  1.03 * price_netto.full_price;
    unsigned int final_price = (int)temp;
    if(final_price == 0)
    {
        throw std::invalid_argument("Wrong price");
    }
    return Money(final_price);
}

bool Cosmetics::operator==(const Cosmetics& other) const {
    return name == other.name && price_netto == other.price_netto.full_price && type == other.type;
}

