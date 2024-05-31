#ifndef _DAIRY_PRODUCT_HPP_
#define _DAIRY_PRODUCT_HPP_

#include "Product.hpp"
#include "../Structures.hpp"

class DairyProduct : public Product
{
    private:
        double protein_content;
    public:
        DairyProduct(std::string name, Money price_netto, double protein_content);
        int find_shelf() const override;
        Money calculate_price() const override;

        ~DairyProduct() = default;
};

#endif