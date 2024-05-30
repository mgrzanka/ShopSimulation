#ifndef _COSMETICS_HPP_
#define _COSMETICS_HPP_

#include "Product.hpp"
#include "../Structures.hpp"

class Cosmetics : public Product
{
    private:
        char type; // F (female) , M(male), other
    public:
        Cosmetics(std::string name, Money price_netto, char type);
        int find_shelf() const override;
        Money calculate_price() const override;
        bool operator==(const Cosmetics& other) const;
        ~Cosmetics() = default;
};

#endif