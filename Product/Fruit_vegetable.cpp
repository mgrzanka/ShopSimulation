#include "Fruit_vegetable.hpp"
#include "Fruit_vegetable.hpp"

FruitVegetable::FruitVegetable(std::string name, Money price_netto, int amount_in_pack) :
Product{name, price_netto},
amount_in_pack{amount_in_pack}
{}

int FruitVegetable::find_shelf() const
{
    return (amount_in_pack * 25 + 300);
}

Money FruitVegetable::calculate_price() const
{
    return price_netto;
}

