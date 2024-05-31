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

int EventGenerator::draw_event_type(std::vector<int> exclude_indexes)
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
        auto it = std::find_if(exclude_indexes.begin(), exclude_indexes.end(), [&](int indx){return indx == i;});
        if(it != exclude_indexes.end()) continue;

        cumulative_probability += probabilities_of_events[i];
        if (random_value <= cumulative_probability) {
            return i;
        }
    }
    return -1;
}

std::unique_ptr<RandomEvent> EventGenerator::draw_event()
{
    auto& employees = store_reference.employees;
    auto& products = store_reference.products;
    auto& clients = store_reference.clients;

    std::vector<int> excluded_indexes;
    std::unique_ptr<RandomEvent> event;

    while(excluded_indexes.size() != events_indexes.size())
    {
        int event_indx = draw_event_type(excluded_indexes);
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
            if(cleaner_indexes.empty())
            {
                excluded_indexes.push_back(event_indx);
                continue;
            }

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0, cleaner_indexes.size()-1);
            int index = dis(gen);
            std::unique_ptr<Cleaner> selected_cleaner = std::unique_ptr<Cleaner>(dynamic_cast<Cleaner*>(employees[cleaner_indexes[index]].release()));

            event = std::make_unique<CleanerCleans>(store_reference,
            probabilities_of_events[event_indx], selected_cleaner);
            break;
        }
        else if (event_indx == 2)
        {
            // get supplier
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
            if(supplier_indexes.empty())
            {
                excluded_indexes.push_back(event_indx);
                continue;
            }

            std::random_device rd1;
            std::mt19937 gen1(rd1());
            std::uniform_real_distribution<> dis1(0, supplier_indexes.size()-1);
            int index = dis1(gen1);

            std::unique_ptr<Storekeeper> selected_store_keeper = std::unique_ptr<Storekeeper>(dynamic_cast<Storekeeper*>(employees[supplier_indexes[index]].release()));
            std::vector<std::unique_ptr<Product>> selected_products = std::move(pick_products());

            event = std::make_unique<SupplierAddsProducts>(store_reference,
            probabilities_of_events[event_indx], selected_store_keeper, selected_products);

            break;
        }
        else if (event_indx == 3)
        {
            int manager_index = 0;
            std::vector<int> manager_indexes;
            std::vector<int> rest_indexes;
            for(auto& employee: employees)
            {
                if(Manager* manager = dynamic_cast<Manager*>(employee.get()))
                {
                    manager_indexes.push_back(manager_index);
                }
                else rest_indexes.push_back(manager_index);
                manager_index++;
            }
            if(manager_indexes.empty() || rest_indexes.empty())
            {
                excluded_indexes.push_back(event_indx);
                continue;
            }

            std::random_device rd_manager;
            std::mt19937 gen_manager(rd_manager());
            std::uniform_real_distribution<> dis_manager(0, manager_indexes.size()-1);
            int m_index = dis_manager(gen_manager);
            std::unique_ptr<Manager> selected_manager = std::unique_ptr<Manager>(dynamic_cast<Manager*>(employees[manager_indexes[m_index]].release()));

            std::random_device rd_employee;
            std::mt19937 gen_employee(rd_employee());
            std::uniform_real_distribution<> dis_employee(0, rest_indexes.size()-1);
            int e_index = dis_employee(gen_employee);
            std::unique_ptr<Employee>& selected_employee = employees[rest_indexes[e_index]];

            event = std::make_unique<MenagerGivesRise>(store_reference,
            probabilities_of_events[event_indx], selected_manager, selected_employee);
            break;
        }
        else
        {
            int cashier_index = 0;
            std::vector<int> cashier_indexes;
            for(auto& employee : employees)
            {
                if (Cashier* cashier = dynamic_cast<Cashier*>(employee.get()))
                {
                    cashier_indexes.push_back(cashier_index);
                }
                cashier_index++;
            }
            if(cashier_indexes.empty())
            {
                excluded_indexes.push_back(event_indx);
                continue;
            }
            std::random_device rd_cashier;
            std::mt19937 gen_cashier(rd_cashier());
            std::uniform_real_distribution<> dis_cashier(0, cashier_indexes.size()-1);
            int c_index = dis_cashier(gen_cashier);
            std::unique_ptr<Cashier> selected_cashier = std::unique_ptr<Cashier>(dynamic_cast<Cashier*>(employees[cashier_indexes[c_index]].release()));

            std::random_device rd_client;
            std::mt19937 gen_client(rd_client());
            std::uniform_real_distribution<> dis_client(0, clients.size()-1);
            int client_index = dis_cashier(gen_client);
            std::unique_ptr<Client>& selected_client = clients[client_index];

            std::vector<std::unique_ptr<Product>> selected_products = std::move(pick_products());

            event = std::make_unique<ClientBuysEvent>(store_reference,
            probabilities_of_events[event_indx], selected_client, selected_cashier, selected_products);
            break;
        }
    }
    return event;
}

std::vector<std::unique_ptr<Product>> EventGenerator::pick_products()
{
    std::vector<std::unique_ptr<Product>> picked_products;

    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_real_distribution<> dis2(0, store_reference.products.size());

    int number_of_products = dis2(gen2);
    for(int i=0; i<number_of_products;i++)
    {
        int products_index = dis2(gen2);
        picked_products.push_back(std::move(store_reference.products[products_index]));
    }

    return picked_products;
}





// std::unique_ptr<RandomEvent> Store::draw_random_event()
// {
//     int type = draw_event_type();
//     if (type = 1)
//     {
//         std::vector<Employee> cleaners;
//         for (const auto& employee_ptr : employees) {
//         if (std::unique_ptr<Cleaner> cleaner = std::dynamic_pointer_cast<Cleaner>(employee_ptr)) {
//         cleaners.push_back(cleaner);}
//         std::random_device rd;
//         std::mt19937 gen(rd());

//         std::uniform_int_distribution<> dist(0, cleaners.size() - 1);
//         int index = dist(gen);
//         std::unique_ptr<Cleaner> my_cleaner = cleaners[index];
//         float probability = 0.1f;
//         std::unique_ptr<RandomEvent> event = std::make_unique<CleanerCleans>(std::ref(store), probability, my_cleaner);
//     }}
//     if (type = 2)
//     {
//         std::vector<Employee> storekeepers;
//         for (const auto& employee_ptr : employees) {
//         if (std::unique_ptr<Storekeeper> storekeeper = std::dynamic_pointer_cast<Storekeeper>(employee_ptr)) {
//         storekeepers.push_back(storekeeper);}
//         std::random_device rd;
//         std::mt19937 gen(rd());

//         std::uniform_int_distribution<> dist(0, storekeepers.size() - 1);
//         int index = dist(gen);
//         std::unique_ptr<Storekeeper> my_storekeeper = storekeepers[index];
//         float probability = 0.1f;
//         std::vector<std::unique_ptr<Product>> new_prod = get_new_products();
//         std::unique_ptr<RandomEvent> event = std::make_unique<SupplierAddsProducts>(std::ref(store), probability, my_storekeeper, new_prod);
//     }}
//     if (type = 3)
//     {
//         std::vector<Employee> managers;
//         for (const auto& employee_ptr : employees) {
//         if (std::unique_ptr<Manager> manager = std::dynamic_pointer_cast<Manager>(employee_ptr)) {
//         managers.push_back(manager);}
//         std::random_device rd;
//         std::mt19937 gen(rd());
//         std::uniform_int_distribution<> dist(0, managers.size() - 1);
//         int index = dist(gen);
//         std::unique_ptr<Manager> my_manager = managers[index];

//         std::vector<Employee> current_employees;
//         for (const auto& employee_ptr : employees) {
//         if (std::unique_ptr<Employee> employee != std::dynamic_pointer_cast<Manager>(employee_ptr)) {
//         current_employees.push_back(employee);}
//         std::random_device rd;
//         std::mt19937 gen(rd());
//         std::uniform_int_distribution<> dist(0, current_employees.size() - 1);
//         int index = dist(gen);
//         std::unique_ptr<Employee> my_employee = current_employees[index];

//         float probability = 0.1f;
//         std::unique_ptr<RandomEvent> event = std::make_unique<MenagerGivesRise>(std::ref(store), probability, my_manager, my_employee);
//     }}}
//     if (type = 4)
//     {
//         std::vector<Employee> cashiers;
//         for (const auto& employee_ptr : employees) {
//         if (std::unique_ptr<Cashier> cashier = std::dynamic_pointer_cast<Cashier>(employee_ptr)) {
//         cashiers.push_back(cashier);}
//         std::random_device rd;
//         std::mt19937 gen(rd());
//         std::uniform_int_distribution<> dist(0, cashiers.size() - 1);
//         int index = dist(gen);
//         std::unique_ptr<Cashier> my_cashier = cashiers[index];


//         std::random_device rd;
//         std::mt19937 gen(rd());
//         std::uniform_int_distribution<> dist(0, clients.size() - 1);
//         int index = dist(gen);
//         std::unique_ptr<Client> my_client = clients[index];

//         float probability = 0.7f;
//         std::vector<std::unique_ptr<Product>> prod_to_buy = get_products_to_buy();
//         std::unique_ptr<RandomEvent> event = std::make_unique<ClientBuysEvent>(std::ref(store), probability, my_client, my_cashier, prod_to_buy);
//     }}
//     return event;
// }



// std::vector<std::unique_ptr<Product>> EventGenerator::get_new_products()
// {

//     std::vector<std::unique_ptr<Product>> new_products;
//     std::vector<std::unique_ptr<Product>> all_prod = store_reference.file_handler.load_products();

//     if (all_prod.empty()) {
//         return new_prod;  // Zwraca pusty wektor, jeśli nie ma produktów
//     }

//     std::random_device rd;
//     std::mt19937 gen(rd());

//     // Losowanie ilości produktów (od 10 do 20)
//     std::uniform_int_distribution<> dist_count(10, 20);
//     int num_prod = dist_count(gen);

//     std::uniform_int_distribution<> dist_index(0, products.size() - 1);

//     for (int i = 0; i < num_prod; ++i) {
//         int index = dist_index(gen);
//         new_prod.push_back(std::move(all_prod[index]));
//     }
//     return new_prod;

// }
