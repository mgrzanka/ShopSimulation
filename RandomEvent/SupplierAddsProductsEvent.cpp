#include "SupplierAddsProductsEvent.hpp"
#include "RandomEvent.hpp"
#include "../Product/Beverage.hpp"
#include "../Product/Breadstuff.hpp"
#include "../Product/Cosmetics.hpp"
#include "../Product/Dairy_product.hpp"
#include "../Product/Fruit_vegetable.hpp"
#include "../Product/Industrial_article.hpp"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>


SupplierAddsProducts::SupplierAddsProducts(Store& store, unsigned int store_keeper_index, std::vector<unsigned int> products_indexes):
RandomEvent(store), products_indexes{products_indexes}
{
    Storekeeper* store_keeper = dynamic_cast<Storekeeper*>(store.on_shift_occupied_employees[store_keeper_index].get());
    if(store_keeper)
    {
        this->store_keeper = std::make_unique<Storekeeper>(*store_keeper);
    }
    else throw std::invalid_argument("Something went wrong in event generator - this employee is not a store keeper!");
}

void SupplierAddsProducts::perform_action()
{
    int products_in_iteration = products_indexes.size();
    std::vector<std::unique_ptr<Product>> to_add;
    Money sum;
    std::vector<std::string> products_names;
    for(int j=0; j < products_in_iteration; j++)
    {
        Money price = store.products[products_indexes[j]]->get_price_netto();
        store.take_money_out(price);
        sum += price;
        products_names.push_back(store.products[products_indexes[j]]->get_name());

        if(Beverage* beverage = dynamic_cast<Beverage*>(store.products[products_indexes[j]].get())) to_add.push_back(std::make_unique<Beverage>(*beverage));
        else if(Breadstuff* bread = dynamic_cast<Breadstuff*>(store.products[products_indexes[j]].get())) to_add.push_back(std::make_unique<Breadstuff>(*bread));
        else if(Cosmetics* cosmetics = dynamic_cast<Cosmetics*>(store.products[products_indexes[j]].get())) to_add.push_back(std::make_unique<Cosmetics>(*cosmetics));
        else if(DairyProduct* dairyProduct = dynamic_cast<DairyProduct*>(store.products[products_indexes[j]].get())) to_add.push_back(std::make_unique<DairyProduct>(*dairyProduct));
        else if(FruitVegetable* fruitvegetable = dynamic_cast<FruitVegetable*>(store.products[products_indexes[j]].get())) to_add.push_back(std::make_unique<FruitVegetable>(*fruitvegetable));
        else if(IndustrialArticle* industrialarticle = dynamic_cast<IndustrialArticle*>(store.products[products_indexes[j]].get())) to_add.push_back(std::make_unique<IndustrialArticle>(*industrialarticle));
        else throw std::invalid_argument("Error while converting Product in SupplierAddsProduct.perform_action.");
    }
    store_keeper->display_replenishing_message(products_names, sum);
    store.add_products(to_add);
}

void SupplierAddsProducts::return_elements()
{
    auto& employees = store.on_shift_occupied_employees;
    auto original_pointer = std::find_if(employees.begin(), employees.end(), [&](const std::unique_ptr<Employee>& emp) {return
    emp->calculate_hours_worked() == store_keeper->calculate_hours_worked() && emp->calculate_weekly_salary() == store_keeper->calculate_weekly_salary() &&
    emp->get_name() == store_keeper->get_name() && emp->get_bonus() == store_keeper->get_bonus();});

    store.on_shift_employees.push_back(std::move(*original_pointer));
    store.on_shift_occupied_employees.erase(original_pointer);
}
