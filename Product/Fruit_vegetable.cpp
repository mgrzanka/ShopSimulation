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
    return Money(price_netto);
}

bool FruitVegetable::operator==(const FruitVegetable& other) const {
    return name == other.name && price_netto.full_price == other.price_netto.full_price && amount_in_pack == other.amount_in_pack;
}

