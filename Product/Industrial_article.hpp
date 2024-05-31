#ifndef _INDUSTRIAL_ARTICLE_HPP_
#define _INDUSTRIAL_ARTICLE_HPP_

#include "Product.hpp"
#include "../Structures.hpp"

class IndustrialArticle : public Product
{
    public:
        IndustrialArticle(std::string name, Money price_netto);
        int find_shelf() const override;
        Money calculate_price() const override;

        ~IndustrialArticle() = default;
};

#endif