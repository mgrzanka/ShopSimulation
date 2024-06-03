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
    std::vector<std::unique_ptr<Product>> products_to_add;
    public:
        SupplierAddsProducts(Store& store, unsigned int store_keeper_index, std::vector<std::unique_ptr<Product>>& products_to_add);
        virtual void perform_action() override;
        virtual void return_elements() override;
};

#endif