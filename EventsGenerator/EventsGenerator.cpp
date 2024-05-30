#include "EventsGenerator.hpp"
#include <algorithm>
#include <memory>
#include <random>
#include <stdexcept>
#include <vector>


EventGenerator::EventGenerator(Store& store_reference,
                        std::vector<float> probabilities_of_events):
store_reference{store_reference}, probabilities_of_events{probabilities_of_events}
{
    float sum = 0;
    int indx = 0;
    for(auto prob : probabilities_of_events)
    {
        events_indexes.push_back(indx);
        indx++;
        sum += prob;
    }
    if (sum != 1) throw std::invalid_argument("Whole probability is different than 1!");
}

int EventGenerator::draw_event_type()
{
    float total_probability = 1;

    // 1- CleanerCleans
    // 2- SupplierAddsProducts
    // 3- MenagerGivesRise
    // 4- ClientBuysEvent

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, total_probability);
    float random_value = dis(gen);

    float cumulative_probability = 0;
    for (auto i : events_indexes)
    {
        cumulative_probability += probabilities_of_events[i];
        if (random_value <= cumulative_probability) {
            return i;
        }
    }
}

std::unique_ptr<RandomEvent>& EventGenerator::draw_event()
{
    auto& employees = store_reference.employees;
    while(true)
    {
        int event_indx = draw_event_type();
        if(event_indx == 0)
        {
            int cleaner_index = 0;
            std::vector<int> cleaner_indexes;
            for(auto& employee : employees)
            {
                if (Cleaner* cleaner = dynamic_cast<Cleaner*>(employee.get()))
                {
                    cleaner_indexes.push_back(cleaner_index);
                }
                cleaner_index++;
            }
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0, cleaner_indexes.size()-1);
            int index = dis(gen);

            std::unique_ptr<RandomEvent> event = std::make_unique<CleanerCleans>(store_reference,
            probabilities_of_events[event_indx], employees[cleaner_indexes[index]]);

            break;
        }
        else if (event_indx == 2)
        {
            int supplier_index = 0;
            std::vector<int> supplier_indexes;
            for(auto& employee : employees)
            {
                if (Storekeeper* storekeeper = dynamic_cast<Storekeeper*>(employee.get()))
                {
                    supplier_indexes.push_back(supplier_index);
                }
                supplier_index++;
            }
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0, supplier_indexes.size()-1);
            int index = dis(gen);

            auto& supplier = employees[supplier_indexes[index]];
        }
    }
}


std::unique_ptr<RandomEvent> Store::draw_random_event()
{
    int type = draw_event_type();
    if (type = 1)
    {
        std::vector<Employee> cleaners;
        for (const auto& employee_ptr : employees) {
        if (std::unique_ptr<Cleaner> cleaner = std::dynamic_pointer_cast<Cleaner>(employee_ptr)) {
        cleaners.push_back(cleaner);}
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dist(0, cleaners.size() - 1);
        int index = dist(gen);
        std::unique_ptr<Cleaner> my_cleaner = cleaners[index];
        float probability = 0.1f;
        std::unique_ptr<RandomEvent> event = std::make_unique<CleanerCleans>(std::ref(store), probability, my_cleaner);
    }}
    if (type = 2)
    {
        std::vector<Employee> storekeepers;
        for (const auto& employee_ptr : employees) {
        if (std::unique_ptr<Storekeeper> storekeeper = std::dynamic_pointer_cast<Storekeeper>(employee_ptr)) {
        storekeepers.push_back(storekeeper);}
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dist(0, storekeepers.size() - 1);
        int index = dist(gen);
        std::unique_ptr<Storekeeper> my_storekeeper = storekeepers[index];
        float probability = 0.1f;
        std::vector<std::unique_ptr<Product>> new_prod = get_new_products();
        std::unique_ptr<RandomEvent> event = std::make_unique<SupplierAddsProducts>(std::ref(store), probability, my_storekeeper, new_prod);
    }}
    if (type = 3)
    {
        std::vector<Employee> managers;
        for (const auto& employee_ptr : employees) {
        if (std::unique_ptr<Manager> manager = std::dynamic_pointer_cast<Manager>(employee_ptr)) {
        managers.push_back(manager);}
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, managers.size() - 1);
        int index = dist(gen);
        std::unique_ptr<Manager> my_manager = managers[index];

        std::vector<Employee> current_employees;
        for (const auto& employee_ptr : employees) {
        if (std::unique_ptr<Employee> employee != std::dynamic_pointer_cast<Manager>(employee_ptr)) {
        current_employees.push_back(employee);}
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, current_employees.size() - 1);
        int index = dist(gen);
        std::unique_ptr<Employee> my_employee = current_employees[index];

        float probability = 0.1f;
        std::unique_ptr<RandomEvent> event = std::make_unique<MenagerGivesRise>(std::ref(store), probability, my_manager, my_employee);
    }}}
    if (type = 4)
    {
        std::vector<Employee> cashiers;
        for (const auto& employee_ptr : employees) {
        if (std::unique_ptr<Cashier> cashier = std::dynamic_pointer_cast<Cashier>(employee_ptr)) {
        cashiers.push_back(cashier);}
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, cashiers.size() - 1);
        int index = dist(gen);
        std::unique_ptr<Cashier> my_cashier = cashiers[index];


        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, clients.size() - 1);
        int index = dist(gen);
        std::unique_ptr<Client> my_client = clients[index];

        float probability = 0.7f;
        std::vector<std::unique_ptr<Product>> prod_to_buy = get_products_to_buy();
        std::unique_ptr<RandomEvent> event = std::make_unique<ClientBuysEvent>(std::ref(store), probability, my_client, my_cashier, prod_to_buy);
    }}
    return event;
}






std::vector<std::unique<Product>> Store::get_new_products()
{
    std::vector<std::unique<Product>> new_prod;
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
        new_prod.push_back(std::move(all_prod[index]));
    }
    return new_prod;
}










std::vector<std::unique<Product>> Store::get_products_to_buy()
{
    std::vector<std::unique<Product>> selected_products;
    std::random_device rd;
    std::mt19937 gen(rd());

    // Losowanie ilości produktów (od 1 do 5)
    std::uniform_int_distribution<> dist_count(1, 5);
    int num_prod = dist_count(gen);

    std::uniform_int_distribution<> dist_index(0, products.size() - 1);

    for (int i = 0; i < num_prod; ++i) {
        int index = dist_index(gen);
        selected_products.push_back(std::move(products[index]));
    }
    return selected_products;
}
