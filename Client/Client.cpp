#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "Client.hpp"



std::string Client::get_name() const
{
    return name + " " + vorname;
}

Money Client::get_money() const
{
    return money;
}

StoreTime Client::get_storetime() const
{
    return time_spent;
}

Client::Client(std::string name, std::string vorname, Money money, StoreTime time_spent):
money {money}, time_spent {time_spent}
{
    if (name.empty() || vorname.empty()) throw std::invalid_argument("Empty name or vorname!");
    else
    {
        this->name = name;
        this->vorname = vorname;
    }
    std::unique_ptr<UserInterface> client_interface = std::make_unique<ClientInterface>();
}

void Client::buy_somethig(std::string employee_name, std::string product_name, Money product_price)
{
    this->interaction_while_paying(employee_name);
    this->display_buying_message(employee_name, product_name, product_price);
    this->update_money(product_price);
}

void Client::interaction_while_paying(std::string employee_name) const
{
    client_interface->print(this->get_name() + ": Goodmorning!");
}

void Client::update_money(Money product_price)
{
    if(product_price < money) throw std::invalid_argument("Something wrong, product price > client's budget");
    else money -= product_price;
}

void Client::display_buying_message(std::string employee_name, std::string product_name, Money product_price) const
{
    client_interface->print(this->get_name() + " is buing " + product_name +
    " for " + std::to_string(product_price.get_whole_part()) + "." + std::to_string(product_price.get_cents()) +
    product_price.currency_name + "being served by " + employee_name);
}

std::ostream& operator<<(std::ostream& os, const Client& client)
{
    return os<<"Client "<<client.get_name()<<" with budget "<<client.get_money()<<" that will spend "<<client.get_storetime()<< "iteration at the store.";
}
