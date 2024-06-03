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


SupplierAddsProducts::SupplierAddsProducts(Store& store, unsigned int store_keeper_index, std::vector<std::unique_ptr<Product>>& products_to_add):
RandomEvent(store), products_to_add{std::move(products_to_add)}
{
    Storekeeper* store_keeper = dynamic_cast<Storekeeper*>(store.on_shift_occupied_employees[store_keeper_index].get());
    if(store_keeper)
    {
        this->store_keeper = std::make_unique<Storekeeper>(*store_keeper);
    }
    else throw std::invalid_argument("Something went wrong in event generator - this employee is not a store keeper!");
}

// void SupplierAddsProducts::perform_action()
// {
//     int products_in_iteration = products_to_add.size();
//     std::vector<std::unique_ptr<Product>> to_add;
//     Money sum;
//     std::vector<std::string> products_names;
//     for(int j=0; j < products_in_iteration; j++)
//     {
//         //Money price = store.products[products_to_add[j]]->get_price_netto();
//         Money price = store.get_products()[products_to_add[j]].get()->get_price_netto();
//         store.take_money_out(price);
//         sum += price;
//         products_names.push_back(store.get_products()[products_to_add[j]]->get_name());

//         if(Beverage* beverage = dynamic_cast<Beverage*>(store.get_products()[products_to_add[j]].get())) to_add.push_back(std::make_unique<Beverage>(*beverage));
//         else if(Breadstuff* bread = dynamic_cast<Breadstuff*>(store.get_products()[products_to_add[j]].get())) to_add.push_back(std::make_unique<Breadstuff>(*bread));
//         else if(Cosmetics* cosmetics = dynamic_cast<Cosmetics*>(store.get_products()[products_to_add[j]].get())) to_add.push_back(std::make_unique<Cosmetics>(*cosmetics));
//         else if(DairyProduct* dairyProduct = dynamic_cast<DairyProduct*>(store.get_products()[products_to_add[j]].get())) to_add.push_back(std::make_unique<DairyProduct>(*dairyProduct));
//         else if(FruitVegetable* fruitvegetable = dynamic_cast<FruitVegetable*>(store.get_products()[products_to_add[j]].get())) to_add.push_back(std::make_unique<FruitVegetable>(*fruitvegetable));
//         else if(IndustrialArticle* industrialarticle = dynamic_cast<IndustrialArticle*>(store.get_products()[products_to_add[j]].get())) to_add.push_back(std::make_unique<IndustrialArticle>(*industrialarticle));
//         else throw std::invalid_argument("Error while converting Product in SupplierAddsProduct.perform_action.");
//     }
//     store_keeper->display_replenishing_message(products_names, sum);
//     store.add_products(to_add);
// }


// void SupplierAddsProducts::perform_action()
// {
//     int products_in_iteration = products_to_add.size();
//     std::vector<std::unique_ptr<Product>> to_add;
//     Money sum;
//     std::vector<std::string> products_names;
//     const auto& products = store.get_products();

//     for (int j = 0; j < products_in_iteration; j++)
//     {
//         Money price = products[products_to_add[j]]->get_price_netto();
//         store.take_money_out(price);
//         sum += price;
//         products_names.push_back(products[products_to_add[j]]->get_name());

//         // Tworzymy nową unikalną kopię obiektu w zależności od jego typu
//         if (Beverage* beverage = dynamic_cast<Beverage*>(products[products_to_add[j]].get()))
//             to_add.push_back(std::make_unique<Beverage>(*beverage));
//         else if (Breadstuff* bread = dynamic_cast<Breadstuff*>(products[products_to_add[j]].get()))
//             to_add.push_back(std::make_unique<Breadstuff>(*bread));
//         else if (Cosmetics* cosmetics = dynamic_cast<Cosmetics*>(products[products_to_add[j]].get()))
//             to_add.push_back(std::make_unique<Cosmetics>(*cosmetics));
//         else if (DairyProduct* dairyProduct = dynamic_cast<DairyProduct*>(products[products_to_add[j]].get()))
//             to_add.push_back(std::make_unique<DairyProduct>(*dairyProduct));
//         else if (FruitVegetable* fruitvegetable = dynamic_cast<FruitVegetable*>(products[products_to_add[j]].get()))
//             to_add.push_back(std::make_unique<FruitVegetable>(*fruitvegetable));
//         else if (IndustrialArticle* industrialarticle = dynamic_cast<IndustrialArticle*>(products[products_to_add[j]].get()))
//             to_add.push_back(std::make_unique<IndustrialArticle>(*industrialarticle));
//         else
//             throw std::invalid_argument("Error while converting Product in SupplierAddsProduct.perform_action.");
//     }

//     store_keeper->display_replenishing_message(products_names, sum);
//     store.add_products(std::move(to_add));
// }


// void SupplierAddsProducts::perform_action()
// {
//     int products_in_iteration = products_to_add.size();
//     std::vector<std::unique_ptr<Product>> to_add;
//     Money sum;
//     std::vector<std::string> products_names;
//     const auto& products = store.get_products();  // Pobierz stałą referencję do wektora produktów

//     for (int j = 0; j < products_in_iteration; j++)
//     {
//         // Znajdź produkt w wektorze za pomocą iteratora
//         auto it = products.begin();
//         std::advance(it, products_to_add[j]);

//         Money price = (*it)->get_price_netto();
//         store.take_money_out(price);
//         sum += price;
//         products_names.push_back((*it)->get_name());

//         // Tworzymy nową unikalną kopię obiektu w zależności od jego typu
//         if (Beverage* beverage = dynamic_cast<Beverage*>(it->get()))
//             to_add.push_back(std::make_unique<Beverage>(*beverage));
//         else if (Breadstuff* bread = dynamic_cast<Breadstuff*>(it->get()))
//             to_add.push_back(std::make_unique<Breadstuff>(*bread));
//         else if (Cosmetics* cosmetics = dynamic_cast<Cosmetics*>(it->get()))
//             to_add.push_back(std::make_unique<Cosmetics>(*cosmetics));
//         else if (DairyProduct* dairyProduct = dynamic_cast<DairyProduct*>(it->get()))
//             to_add.push_back(std::make_unique<DairyProduct>(*dairyProduct));
//         else if (FruitVegetable* fruitvegetable = dynamic_cast<FruitVegetable*>(it->get()))
//             to_add.push_back(std::make_unique<FruitVegetable>(*fruitvegetable));
//         else if (IndustrialArticle* industrialarticle = dynamic_cast<IndustrialArticle*>(it->get()))
//             to_add.push_back(std::make_unique<IndustrialArticle>(*industrialarticle));
//         else
//             throw std::invalid_argument("Error while converting Product in SupplierAddsProduct.perform_action.");
//     }

//     store_keeper->display_replenishing_message(products_names, sum);
//     store.add_products(std::move(to_add));
// }


void SupplierAddsProducts::perform_action()
{
    int products_in_iteration = products_to_add.size();
    std::vector<std::unique_ptr<Product>> to_add;
    Money sum;
    std::vector<std::string> products_names;
    //const auto& products = store.get_products();  // Pobierz stałą referencję do wektora produktów

    for (int j = 0; j < products_in_iteration; j++)
    {
        int product_index = j;

        Money price = products_to_add[product_index]->get_price_netto();
        store.take_money_out(price);
        sum += price;
        products_names.push_back(products_to_add[product_index]->get_name());

        // Tworzymy nową unikalną kopię obiektu w zależności od jego typu
        if (Beverage* beverage = dynamic_cast<Beverage*>(products_to_add[product_index].get()))
            to_add.push_back(std::make_unique<Beverage>(*beverage));
        else if (Breadstuff* bread = dynamic_cast<Breadstuff*>(products_to_add[product_index].get()))
            to_add.push_back(std::make_unique<Breadstuff>(*bread));
        else if (Cosmetics* cosmetics = dynamic_cast<Cosmetics*>(products_to_add[product_index].get()))
            to_add.push_back(std::make_unique<Cosmetics>(*cosmetics));
        else if (DairyProduct* dairyProduct = dynamic_cast<DairyProduct*>(products_to_add[product_index].get()))
            to_add.push_back(std::make_unique<DairyProduct>(*dairyProduct));
        else if (FruitVegetable* fruitvegetable = dynamic_cast<FruitVegetable*>(products_to_add[product_index].get()))
            to_add.push_back(std::make_unique<FruitVegetable>(*fruitvegetable));
        else if (IndustrialArticle* industrialarticle = dynamic_cast<IndustrialArticle*>(products_to_add[product_index].get()))
            to_add.push_back(std::make_unique<IndustrialArticle>(*industrialarticle));
        else
            throw std::invalid_argument("Error while converting Product in SupplierAddsProduct.perform_action.");
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
