#include "Breadstuff.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

Breadstuff::Breadstuff(std::string name, Money price_netto, int glycemic_index) :
Product{name, price_netto},
glycemic_index{glycemic_index}
{}

int Breadstuff::find_shelf() const
{
    double i = glycemic_index * 0.2 + 100;
    int shelf_nr = static_cast<int>(i);
    return shelf_nr;
}

Money Breadstuff::calculate_price() const
{
    unsigned int final_price = 1.05 * price_netto;
    if(final_price == 0)
    {
        throw std::invalid_argument("Wrong price");
    }
    return Money(final_price);
}

bool Breadstuff::operator==(const Breadstuff& other) const {
    return name == other.name && price_netto == other.price_netto && glycemic_index == other.glycemic_index;
}

