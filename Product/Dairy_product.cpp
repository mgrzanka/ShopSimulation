#include "Dairy_product.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

DairyProduct::DairyProduct(std::string name, Money price_netto, double protein_content) :
Product{name, price_netto},
protein_content{protein_content}
{}

int DairyProduct::find_shelf() const
{
    double i = protein_content * 10 + 200;
    int shelf_nr = static_cast<int>(i);
    return shelf_nr;
}

Money DairyProduct::calculate_price() const
{
    unsigned int final_price = 1.05 * price_netto.full_price;
    if(final_price == 0)
    {
        throw std::invalid_argument("Wrong price");
    }
    return Money(final_price);
}

