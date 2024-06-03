#ifndef _RECEIPT_HPP_
#define _RECEIPT_HPP_
#include <iostream>
#include <string>
#include <vector>


#include "../Structures.hpp"
#include "../UserInterface/UserInterface.hpp"


class Receipt
{
    Money total_price;
    Money price_without_tax;
    std::vector<std::string> names;
    std::vector<Money> prices;
    UserInterface receipt_interface;

    public:
        Receipt(Money total_price, Money pprice_without_tax,
        std::vector<std::string>& names, std::vector<Money>& prices);
        void print_receipt();
};

#endif