#ifndef _BEVERAGE_HPP_
#define _BEVERAGE_HPP_

#include "Product.hpp"
#include "../Structures.hpp"

class Beverage : public Product
{
    public:
        Beverage(std::string name, Money price_netto);
        int find_shelf() const override;
        Money calculate_price() const override;
        bool operator==(const Beverage& other) const;
        ~Beverage() = default;
};

#endif