#include "Store.hpp"
#include "../FileHandler/FileHandler.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <random>


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

std::vector<std::unique<Product>*> Store::get_new_products()
{
    std::vector<std::unique<Product>*> new_prod;
    std::vector<std::unique_ptr<Product>> all_prod = file_handler.load_products();

    if (all_prod.empty()) {
        return new_prod;  // Zwraca pusty wektor, jeśli nie ma produktów
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    // Losowanie ilości produktów (od 10 do 20)
    std::uniform_int_distribution<> dist_count(10, 20);
    int num_prod = dist_count(gen);

    std::uniform_int_distribution<> dist_index(0, products.size() - 1);

    for (int i = 0; i < num_prod; ++i) {
        int index = dist_index(gen);
        new_prod.push_back(std::move(&all_prod[index]));
    }
    return new_prod;
}

std::vector<std::unique<Product>*> Store::get_products_to_buy()
{
    std::vector<std::unique<Product>*> selected_products;
    std::random_device rd;
    std::mt19937 gen(rd());

    // Losowanie ilości produktów (od 1 do 5)
    std::uniform_int_distribution<> dist_count(1, 5);
    int num_prod = dist_count(gen);

    std::uniform_int_distribution<> dist_index(0, products.size() - 1);

    for (int i = 0; i < num_prod; ++i) {
        int index = dist_index(gen);
        selected_products.push_back(std::move(&products[index]));
    }
    return selected_products;
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
        float probability = 0.1f;
        std::vector<std::unique_ptr<Product>> new_prod = get_new_products();
        possible_events.push_back(std::make_unique<SupplierAddsProducts>(std::ref(store), probability, storekeeper, new_prod));}
    }
    auto it = std::find_if(employees.begin(), employees.end(), [](const std::unique_ptr<Employee>& employee) {
        return dynamic_cast<Manager*>(employee.get()) != nullptr;
    });
    if (it != employees.end()){
        for (const auto& employee_ptr : employees) {
        if (std::unique_ptr<Manager> manager != std::dynamic_pointer_cast<Manager>(employee_ptr)) {
            float probability = 0.1f;
            possible_events.push_back(std::make_unique<MenagerGivesRise>(std::ref(store), probability, it, employee_ptr));}
        }}
    for (const auto& employee_ptr : employees) {
    if (std::unique_ptr<Cashier> cashier = std::dynamic_pointer_cast<Cashier>(employee_ptr)) {
        float probability = 0.7f;
        for (const auto& client_ptr : clients) {
        std::vector<std::unique_ptr<Product>> prod_to_buy = get_products_to_buy();
        possible_events.push_back(std::make_unique<ClientBuysEvent>(std::ref(store), probability, client_ptr, cashier, prod_to_buy));}
    }}
    return possible_events;
}


std::unique_ptr<RandomEvent> Store::draw_random_event()
{
    float total_probability = 0;
    std::vector<std::unique_ptr<RandomEvent>> events = get_possible_events();
    for (const auto& event : events) {
        total_probability += event->get_probability();
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, total_probability);
    float random_value = dis(gen);

    float cumulative_probability = 0;
    for (const auto& event : events) {
        cumulative_probability += event->get_probability();
        if (random_value <= cumulative_probability) {
            return std::make_unique<RandomEvent>(*event);
        }
    }
}
