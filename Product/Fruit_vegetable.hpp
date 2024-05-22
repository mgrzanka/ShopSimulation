#ifndef _FRUIT_VEGETABLE_HPP_
#define _FRUIT_VEGETABLE_HPP_

#include "Product.hpp"
#include "../Structures.hpp"

class FruitVegetable : public Product
{
    private:
        int amount_in_pack;
    public:
        FruitVegetable(std::string name, Money price_netto, int amount_in_pack);
        int find_shelf() const override;
        Money calculate_price() const override;
        bool operator==(const FruitVegetable& other) const;
        ~FruitVegetable() = default;
};

#endif