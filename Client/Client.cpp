#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Client.hpp"



std::string Client::get_name() const
{
    return name + " " + vorname;
}

Money Client::get_money() const
{
    return money;
}

Client::Client(std::string name, std::string vorname, Money money):
money {money}, client_interface {}
{
    if (name.empty() || vorname.empty()) throw std::invalid_argument("Empty name or vorname!");
    else
    {
        this->name = name;
        this->vorname = vorname;
    }
}

void Client::buy_somethig(std::string employee_name, std::vector<std::string> product_names, const Money& product_price)
{
    this->interaction_while_paying(employee_name);
    this->display_buying_message(employee_name, product_names, product_price);
    this->take_money(product_price.full_price);
}

void Client::interaction_while_paying(std::string employee_name) const
{
    client_interface.print(this->get_name() + ": Goodmorning dear " + employee_name+ "!");
}

void Client::take_money(unsigned int amount)
{
    if(amount > money.full_price) throw std::invalid_argument("Something wrong, product price > client's budget");
    money.full_price = money.full_price - amount;
}

void Client::add_money(unsigned int amount)
{
    money.full_price = money.full_price + amount;
}

void Client::display_buying_message(std::string employee_name, std::vector<std::string> product_names, const Money& product_price) const
{
    client_interface.print(this->get_name() + " is buing ");
    for(const auto& name: product_names) client_interface.print(name+", ");
    client_interface.print(" for " + std::to_string(product_price.get_whole_part()) + "." + std::to_string(product_price.get_cents()) +
    product_price.currency_name + " and is being served by " + employee_name+"\n");
}

std::ostream& operator<<(std::ostream& os, const Client& client)
{
    return os<<"Client "<<client.get_name()<<" with budget "<<client.get_money();
}
