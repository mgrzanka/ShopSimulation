#include "Store.hpp"
#include "../FileHandler/FileHandler.hpp"
#include <iostream>
#include <algorithm>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
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

Store::Store(std::vector<std::unique_ptr<Client>>& clients,
                std::vector<std::unique_ptr<Employee>>& employees,
                Money money)
{
    this->add_clients(clients);
    this->add_employees(employees);
    this->money = money;
}

const std::vector<std::unique_ptr<Product>>& Store::get_products() const
{
    return products;
}

const std::vector<std::unique_ptr<Client>>& Store::get_available_clients() const
{
    return available_clients;
}

const std::vector<std::unique_ptr<Client>>& Store::get_taken_clients() const
{
    return taken_clients;
}

const std::vector<std::unique_ptr<Employee>>& Store::get_on_shift_employees() const
{
    return on_shift_employees;
}

const std::vector<std::unique_ptr<Employee>>& Store::get_on_shift_occupied_employees() const
{
    return on_shift_occupied_employees;
}

const std::vector<std::unique_ptr<Employee>>& Store::get_on_break_employees() const
{
    return on_break_employees;
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
                  [&](std::unique_ptr<Client>& element) {available_clients.push_back(std::move(element));});
}

void Store::add_employees(std::vector<std::unique_ptr<Employee>>& new_employees)
{
    std::for_each(new_employees.begin(), new_employees.end(),
                  [&](std::unique_ptr<Employee>& element) {on_break_employees.push_back(std::move(element));});
}

void Store::take_money_out(Money to_take)
{
    if(to_take.full_price > money.full_price)
    {
        throw std::invalid_argument("To expensive!");
    }
    money -= to_take;
}

std::tuple<std::vector<int>, std::vector<int>> Store::check_employee_shift(unsigned int day, unsigned int iterations, unsigned int starting_hour, unsigned int closing_hour)
{
    std::vector<int> currently_active;
    std::vector<int> currently_inactive;
    int x = on_break_employees.size();
    for(int i=0; i<x; i++)
    {
        std::tuple<unsigned int, unsigned int> hours;
        switch(day)
        {
            case 1: hours = on_break_employees[i]->get_weekly_schedule()["mon"]; break;
            case 2: hours = on_break_employees[i]->get_weekly_schedule()["tue"]; break;
            case 3: hours = on_break_employees[i]->get_weekly_schedule()["wed"]; break;
            case 4: hours = on_break_employees[i]->get_weekly_schedule()["thu"]; break;
            case 5: hours = on_break_employees[i]->get_weekly_schedule()["fri"]; break;
            case 6: hours = on_break_employees[i]->get_weekly_schedule()["sat"]; break;
            case 7: hours = on_break_employees[i]->get_weekly_schedule()["sun"]; break;
        }
        unsigned int minutes = 60*(std::get<0>(hours) - starting_hour);
        unsigned int iterations_to_start = StoreTime(minutes).get_iterations();
        if(iterations == iterations_to_start) currently_inactive.push_back(i);
    }
    int y = on_shift_employees.size();
    for(int i=0; i<y; i++)
    {
        std::tuple<unsigned int, unsigned int> hours;
        switch(day)
        {
            case 1: hours = on_shift_employees[i]->get_weekly_schedule()["mon"]; break;
            case 2: hours = on_shift_employees[i]->get_weekly_schedule()["tue"]; break;
            case 3: hours = on_shift_employees[i]->get_weekly_schedule()["wed"]; break;
            case 4: hours = on_shift_employees[i]->get_weekly_schedule()["thu"]; break;
            case 5: hours = on_shift_employees[i]->get_weekly_schedule()["fri"]; break;
            case 6: hours = on_shift_employees[i]->get_weekly_schedule()["sat"]; break;
            case 7: hours = on_shift_employees[i]->get_weekly_schedule()["sun"]; break;
        }
        unsigned int minutes = 60*(std::get<1>(hours) - starting_hour);
        unsigned int iterations_to_stop = StoreTime(minutes).get_iterations();
        unsigned int iterations_to_closing = StoreTime(closing_hour*60).get_iterations();

        if(iterations >= iterations_to_stop || iterations >= iterations_to_closing) currently_active.push_back(i);
    }
    std::tuple<std::vector<int>, std::vector<int>> to_print_tuple = {currently_inactive, currently_active};
    return to_print_tuple;
}

void Store::update_employees_shift(std::tuple<std::vector<int>,std::vector<int>> employees)
{
    std::vector<int> currently_inactive = std::get<0>(employees);
    std::vector<int> currently_active = std::get<1>(employees);
    for(auto employee_indx : currently_inactive) on_shift_employees.push_back(std::move(on_break_employees[employee_indx]));
    on_break_employees.erase(std::remove(on_break_employees.begin(), on_break_employees.end(), nullptr), on_break_employees.end());
    for(auto employee_indx : currently_active) on_break_employees.push_back(std::move(on_shift_employees[employee_indx]));
    for(auto employee_indx : currently_active) on_shift_employees.erase(on_shift_employees.begin() + employee_indx);
}

void Store::pay_employees()
{
    for(auto& employee : on_break_employees)
    {
        Money to_take = employee->get_base_hourly_wage();
        if(to_take > money) throw (std::invalid_argument("Not enough money to pay the employee!"));
        take_money_out(employee->get_base_hourly_wage());
    }
}