#include "Store.hpp"
#include "../FileHandler/FileHandler.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <vector>
#include <random>


Store::Store(std::vector<std::unique_ptr<Product>>& products,
                std::vector<std::unique_ptr<Client>>& clients,
                std::vector<std::unique_ptr<Employee>>& employees,
                Money money)
{
    this->add_products(products);
    this->add_clients(clients);
    this->add_employees(employees);
    this->money = money;
}

const std::vector<std::unique_ptr<Product>>& Store::get_products() const
{
    return products;
}

const std::vector<std::unique_ptr<Client>>& Store::get_clients() const
{
    return clients;
}

const std::vector<std::unique_ptr<Employee>>& Store::get_employees() const
{
    return employees;
}

Money Store::get_money() const
{
    return money;
}

void Store::add_money(Money added_money)
{
    money += added_money;
}

void Store::add_products(std::vector<std::unique_ptr<Product>>& new_products)
{
    std::for_each(new_products.begin(), new_products.end(),
                  [&](std::unique_ptr<Product>& element) {products.push_back(std::move(element));});
}

void Store::add_clients(std::vector<std::unique_ptr<Client>>& new_clients)
{
    std::for_each(new_clients.begin(), new_clients.end(),
                  [&](std::unique_ptr<Client>& element) {clients.push_back(std::move(element));});
}

void Store::add_employees(std::vector<std::unique_ptr<Employee>>& new_employees)
{
    std::for_each(new_employees.begin(), new_employees.end(),
                  [&](std::unique_ptr<Employee>& element) {employees.push_back(std::move(element));});
}

void Store::take_money_out(Money to_take)
{
    if(to_take.full_price > money.full_price) throw std::invalid_argument("To expensive!");
    money -= to_take;
}
