#ifndef _BREADSTUFF_HPP_
#define _BREADSTUFF_HPP_

#include "Product.hpp"
#include "../Structures.hpp"

class Breadstuff : public Product
{
    private:
        int glycemic_index;
    public:
        Breadstuff(std::string name, Money price_netto, int glycemic_index);
        int find_shelf() const override;
        Money calculate_price() const override;
        bool operator==(const Breadstuff& other) const;
        ~Breadstuff() = default;
};

#endif