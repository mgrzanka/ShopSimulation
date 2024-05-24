#include "store.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>


std::vector<std::unique_ptr<Product>>& Store::get_products() const
{
    return products;
}

std::vector<std::unique_ptr<Client>>& Store::get_clients() const
{
    return clients;
}

std::vector<std::unique_ptr<Employee>>& Store::get_employees() const
{
    return employees;
}

Money Store::get_money()
{
    return money;
}

std::vector<std::unique<Product>> Store::get_new_products()
{
    std::vector<std::unique<Product>> new_prod;
    // losowanie nowych produktów do dodania
    return new_prod;
}


void add_money(Money added_money)
{
    money += added_money;
}

void Store::add_products(std::vector<std::unique_ptr<Product>> new_products)
{
    std::for_each(new_products.begin(), new_products.end(),
                  [this](std::unique_ptr<Product>&& element) {products.push_back(std::move(element));});
}

void Store::add_clients(std::vector<std::unique_ptr<Client>> new_clients)
{
    std::for_each(new_clients.begin(), new_clients.end(),
                  [this](std::unique_ptr<Client>&& element) {clients.push_back(std::move(element));});
}

void Store::add_employees(std::vector<std::unique_ptr<Employee>> new_employees)
{
    std::for_each(new_employees.begin(), new_employees.end(),
                  [this](std::unique_ptr<Employee>&& element) {employees.push_back(std::move(element));});
}

std::vector<std::unique_ptr<RandomEvent>> Store::get_possible_events()
{
    std::vector<std::unique_ptr<RandomEvent>> possible_events;

    for (const auto& employee_ptr : employees) {
    if (std::unique_ptr<Cleaner> cleaner = std::dynamic_pointer_cast<Cleaner>(employee_ptr)) {
        float probability = 0.1f;
        possible_events.push_back(std::make_unique<CleanerCleans>(std::ref(store), probability, cleaner));}
    }
    for (const auto& employee_ptr : employees) {
    if (std::unique_ptr<Storekeeper> storekeeper = std::dynamic_pointer_cast<Storekeeper>(employee_ptr)) {
        float probability = 0.2f;
        std::vector<std::unique_ptr<Product>> new_prod = get_new_products();
        possible_events.push_back(std::make_unique<SupplierAddsProducts>(std::ref(store), probability, storekeeper, new_prod));}
    }
    auto it = std::find_if(employees.begin(), employees.end(), [](const std::unique_ptr<Employee>& employee) {
        return dynamic_cast<Manager*>(employee.get()) != nullptr;
    });
    if (it != employees.end()){
        for (const auto& employee_ptr : employees) {
        if (std::unique_ptr<Manager> manager != std::dynamic_pointer_cast<Manager>(employee_ptr)) {
            float probability = 0.2f;
            possible_events.push_back(std::make_unique<MenagerGivesRise>(std::ref(store), probability, it, employee_ptr));}
        }}
        //jeszcze event do kupowania
}


std::unique_ptr<RandomEvent> Store::draw_random_event()
{
    //losowanie zdarzenia
}