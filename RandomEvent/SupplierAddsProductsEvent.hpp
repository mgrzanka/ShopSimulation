#ifndef _SUPPLIER_ADDS_PRODUCT_
#define _SUPPLIER_ADDS_PRODUCT_

#include "RandomEvent.hpp"
#include "../Employee/storekeeper.hpp"
#include "../Product/Product.hpp"
#include <memory>
#include <vector>


class SupplierAddsProducts: public RandomEvent
{
    std::unique_ptr<Storekeeper> store_keeper;
    std::vector<std::unique_ptr<Product>> products;
    unsigned int products_per_iteration;
    public:
        SupplierAddsProducts(Store& store, float probability, std::unique_ptr<Storekeeper>& store_keeper, std::vector<std::unique_ptr<Product>>& products);
        virtual void perform_action() override;
        virtual void restore() override;
        virtual bool check_action() const override;
};

#endif