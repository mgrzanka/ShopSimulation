#include "SupplierAddsProductsEvent.hpp"
#include "RandomEvent.hpp"
#include <algorithm>
#include <memory>
#include <vector>


SupplierAddsProducts::SupplierAddsProducts(Store& store, float probability, std::unique_ptr<Storekeeper> store_keeper, std::vector<std::unique_ptr<Product>> products):
RandomEvent(store, probability)
{
    this->store_keeper = std::move(store_keeper);
    std::for_each(products.begin(), products.end(),
                    [&](const auto& p){this->products.push_back(std::move(p));});
    this->counter = store_keeper->get_time_to_replenish().get_iterations();
}

void SupplierAddsProducts::restore()
{
    std::vector<std::unique_ptr<Storekeeper>> e = {std::move(store_keeper)};
    store.add_employees(e);
    store.add_products(products);
}

bool SupplierAddsProducts::check_action() const
{
    return products.size() >= counter;
}

void SupplierAddsProducts::perform_action()
{
    int products_in_iteration = products.size() / counter;
    std::vector<std::unique_ptr<Product>> to_add;
    for(int j=0; j < products_in_iteration; j++)
    {
        to_add.push_back(std::move(products[j]));
        store_keeper->display_replenishing_message(products[j]->get_name());
    }
    store.add_products(to_add);
}
