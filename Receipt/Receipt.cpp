#include "Receipt.hpp"
#include <string>


Receipt::Receipt(Money total_price, Money price_without_tax, std::vector<std::string>& names, std::vector<Money>& prices):
names {names}, prices {prices}, receipt_interface{}
{
    this->total_price = total_price;
    this->price_without_tax = price_without_tax;
}

void Receipt::print_receipt()
{
    std::string header = "---- RECEIPT ------";
    std::string tp_ending = "---- total price: " + std::to_string(total_price.get_whole_part())+"."+std::to_string(total_price.get_cents())+total_price.currency_name+"\n";
    std::string no_tax_ending = "---- without tax: " + std::to_string(price_without_tax.get_whole_part())+"."+std::to_string(price_without_tax.get_cents())+price_without_tax.currency_name+"\n";

    receipt_interface.print(header);
    for(int i=0;i<names.size();i++)
    {
        receipt_interface.print("---- "+names[i]+": "+std::to_string(prices[i].get_whole_part())+":"+std::to_string(prices[i].get_cents())+prices[i].currency_name+"\n");
    }
    receipt_interface.print(tp_ending);
    receipt_interface.print(no_tax_ending);
}