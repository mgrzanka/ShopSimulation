#ifndef _PRODUCT_HPP_
#define _PRODUCT_HPP_
#pragma once
#include <string>
#include "../Structures.hpp"

class Product
{
    protected:
        std::string name;
        Money price_netto;

    public:
        Product(std::string name, Money price_netto);
        std::string get_name() const;
        Money get_price_netto() const;

        void set_name(std::string new_name);
        void set_price_netto(double new_price_netto);

        virtual Money calculate_price() const = 0;
        virtual int find_shelf() const = 0;
        virtual ~Product() = default;
};

#endif