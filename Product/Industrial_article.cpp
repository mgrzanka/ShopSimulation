#include "Industrial_article.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

IndustrialArticle::IndustrialArticle(std::string name, Money price_netto) :
Product{name, price_netto}
{}

int IndustrialArticle::find_shelf() const
{
    return 726;
}

Money IndustrialArticle::calculate_price() const
{
    unsigned int final_price = 1.08 * price_netto;
    if(final_price == 0)
    {
        throw std::invalid_argument("Wrong price");
    }
    return Money(final_price);
}

bool IndustrialArticle::operator==(const IndustrialArticle& other) const {
    return name == other.name && price_netto == other.price_netto;
}
