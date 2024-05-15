#include <iostream>
#include <stdexcept>

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
}

void Client::buy_somethig(const std::unique_ptr<Employee>& employee_ptr, const std::unique_ptr<Product>& product_ptr)
{
    this->display_buying_message(employee_ptr, product_ptr);
    this->talk_to_employee(employee_ptr);
    this->update_money(product_ptr);
}

void Client::talk_to_employee(const std::unique_ptr<Employee>& employee_ptr) const
{

}