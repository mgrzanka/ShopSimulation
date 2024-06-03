#include "EventsGenerator.hpp"
#include "../FileHandler/FileHandler.hpp"
#include <algorithm>
#include <memory>
#include <numeric>
#include <random>
#include <stdexcept>
#include <system_error>
#include <tuple>
#include <utility>
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

int EventGenerator::draw_event_type(std::vector<int>& exclude_indexes) const
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<int> indexes_to_draw;
    std::vector<float> probabilities_to_draw;

    float sum = 0.0;
    for (auto i : events_indexes)
    {
        if (std::find(exclude_indexes.begin(), exclude_indexes.end(), i) == exclude_indexes.end())
        {
            indexes_to_draw.push_back(i);
            probabilities_to_draw.push_back(probabilities_of_events[i]);
            sum = sum + probabilities_of_events[i];
        }
    }
    if(sum == 0) return -1;

    std::discrete_distribution<> dis(probabilities_to_draw.begin(), probabilities_to_draw.end());
    int random_index = dis(gen);
    return indexes_to_draw[random_index];
}

std::unique_ptr<RandomEvent> EventGenerator::draw_event(std::vector<int> indexes)
{
    std::vector<int> excluded_indexes;
    std::unique_ptr<RandomEvent> event = nullptr;

    while(excluded_indexes.size() < events_indexes.size())
    {
        int event_index = draw_event_type(excluded_indexes);
        if(event_index == 0)
        {
            event = draw_cleaner_cleans(indexes);
            if(!event)
            {
                excluded_indexes.push_back(event_index);
                continue;
            }
            break;
        }
        else if(event_index == 1)
        {
            event = draw_supplier_adds(indexes);
            if(!event)
            {
                excluded_indexes.push_back(event_index);
                continue;
            }
            break;
        }
        else if(event_index == 2)
        {
            event = draw_manager_gives_raise(indexes);
            if(!event)
            {
                excluded_indexes.push_back(event_index);
                continue;
            }
            break;
        }
        else if(event_index == 3)
        {
            event = draw_client_buys(indexes);
            if(!event)
            {
                excluded_indexes.push_back(event_index);
                continue;
            }
            break;
        }
        else excluded_indexes.push_back(event_index);
    }
    return event;
}

// std::vector<unsigned int> EventGenerator::pick_products_indexes()
// {
//     std::vector<unsigned int> products_indexes;

//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(1, store_reference.products.size());
//     int number_of_products = dis(gen);
//     Money total_price;
//     Money current_money = store_reference.get_money();

//     for(int indx=0; indx < number_of_products; indx++)
//     {
//         int random_index = dis(gen)-1;
//         Money money = total_price + store_reference.products[random_index]->get_price_netto();
//         if(std::find(products_indexes.begin(), products_indexes.end(), random_index) == products_indexes.end() &&
//         money < current_money)
//         {
//             products_indexes.push_back(random_index);
//             total_price += money;
//         }
//     }
//     return products_indexes;
// }


std::vector<std::unique_ptr<Product>> EventGenerator::pick_new_products()
{
    FileHandler file_handler("../products.txt");
    std::vector<std::unique_ptr<Product>> new_prod;
    std::vector<std::unique_ptr<Product>> all_prod = file_handler.load_products();

    if (all_prod.empty()) {
        return new_prod;  // Zwraca pusty wektor, jeśli nie ma produktów
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    // Losowanie ilości produktów (od 20 do 30)
    std::uniform_int_distribution<> dist_count(20, 30);
    int num_prod = dist_count(gen);

    std::uniform_int_distribution<> dist_index(0, all_prod.size() - 1);

    for (int i = 0; i < num_prod; ++i) {
        int index = dist_index(gen);
        new_prod.push_back(std::move(all_prod[index]));
    }

    return new_prod;
}



std::unique_ptr<RandomEvent> EventGenerator::draw_cleaner_cleans(std::vector<int> indexes)
{
    int employee_indx = 0;
    std::vector<int> cleaner_indexes;

    for (int employee_indx=0; employee_indx<store_reference.on_shift_employees.size(); employee_indx++)
    {
        if (std::find(indexes.begin(), indexes.end(), employee_indx) != indexes.end()) continue;

        auto& employee = store_reference.on_shift_employees[employee_indx];
        if (Cleaner* cleaner = dynamic_cast<Cleaner*>(employee.get()))
        {
            cleaner_indexes.push_back(employee_indx);
        }
    }
    if(cleaner_indexes.empty()) return nullptr;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, cleaner_indexes.size()-1);

    int on_shift_index = dis(gen);
    store_reference.on_shift_occupied_employees.push_back(std::move(store_reference.on_shift_employees[cleaner_indexes[on_shift_index]]));
    int on_shift_occupied_index = store_reference.on_shift_occupied_employees.size() - 1;
    std::erase(store_reference.on_shift_employees, store_reference.on_shift_employees[cleaner_indexes[on_shift_index]]);

    return std::make_unique<CleanerCleans>(store_reference, on_shift_occupied_index);  // do napisania cleaner cleans
}

std::unique_ptr<RandomEvent> EventGenerator::draw_supplier_adds(std::vector<int> indexes)
{
    int employee_indx = 0;
    std::vector<int> supplier_indexes;
    for (int employee_indx=0; employee_indx<store_reference.on_shift_employees.size(); employee_indx++)
    {
        if (std::find(indexes.begin(), indexes.end(), employee_indx) != indexes.end()) continue;

        auto &employee = store_reference.on_shift_employees[employee_indx];
        if (Storekeeper* keeper = dynamic_cast<Storekeeper*>(employee.get()))
        {
            supplier_indexes.push_back(employee_indx);
        }
    }
    if(supplier_indexes.empty() || store_reference.products.empty()) return nullptr;
    std::vector<std::unique_ptr<Product>>> products_to_get = pick_new_products();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, supplier_indexes.size()-1);
    int on_shift_index = dis(gen);

    store_reference.on_shift_occupied_employees.push_back(std::move(store_reference.on_shift_employees[supplier_indexes[on_shift_index]]));
    int on_shift_occupied_index = store_reference.on_shift_occupied_employees.size() - 1;
    std::erase(store_reference.on_shift_employees, store_reference.on_shift_employees[supplier_indexes[on_shift_index]]);

    return std::make_unique<SupplierAddsProducts>(store_reference, on_shift_occupied_index, products_to_get);  // do napisania Random Event
}

std::unique_ptr<RandomEvent> EventGenerator::draw_manager_gives_raise(std::vector<int> indexes)
{
    int employee_indx = 0;
    std::vector<int> manager_indexes;
    std::vector<int> other_indexes;
    for (int employee_indx=0; employee_indx<store_reference.on_shift_employees.size(); employee_indx++)
    {
        if (std::find(indexes.begin(), indexes.end(), employee_indx) != indexes.end()) continue;

        auto &employee = store_reference.on_shift_employees[employee_indx];
        if (Manager* manager = dynamic_cast<Manager*>(employee.get()))
        {
            manager_indexes.push_back(employee_indx);
        }
        else other_indexes.push_back(employee_indx);
    }
    if(manager_indexes.empty() || other_indexes.empty()) return nullptr;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_manager(0, manager_indexes.size()-1);
    std::uniform_int_distribution<> dis_other(0, other_indexes.size()-1);
    int on_shift_index_manager = dis_manager(gen);
    int on_shift_index_other = dis_other(gen);

    Money clients_bonus(store_reference.on_shift_employees[other_indexes[on_shift_index_other]]->get_bonus());
    if(clients_bonus > store_reference.get_money()) return nullptr;

    store_reference.on_shift_occupied_employees.push_back(
        std::move(store_reference.on_shift_employees[manager_indexes[on_shift_index_manager]]));
    store_reference.on_shift_occupied_employees.push_back(
        std::move(store_reference.on_shift_employees[other_indexes[on_shift_index_other]]));
    store_reference.on_shift_employees.erase(std::remove(store_reference.on_shift_employees.begin(),
    store_reference.on_shift_employees.end(), nullptr),store_reference.on_shift_employees.end());

    return std::make_unique<MenagerGivesRise>(
        store_reference,
        store_reference.on_shift_occupied_employees.size() - 2,
        store_reference.on_shift_occupied_employees.size() - 1);
}

std::unique_ptr<RandomEvent> EventGenerator::draw_client_buys(std::vector<int> indexes)
{
    int employee_indx = 0;
    std::vector<int> cashier_indexes;
    for (int employee_indx=0; employee_indx<store_reference.on_shift_employees.size(); employee_indx++)
    {
        if (std::find(indexes.begin(), indexes.end(), employee_indx) != indexes.end()) continue;

        auto &employee = store_reference.on_shift_employees[employee_indx];
        if (Cashier* cashier = dynamic_cast<Cashier*>(employee.get()))
        {
            cashier_indexes.push_back(employee_indx);
        }
    }
    if(cashier_indexes.empty() || store_reference.available_clients.empty() || store_reference.products.empty()) return nullptr;

    std::vector<unsigned int> products_indexes = pick_products_indexes();
    Money total_sum;
    std::vector<std::unique_ptr<Product>> products;
    for(int index : products_indexes)
    {
        total_sum += store_reference.products[index]->get_price_netto();
        if(total_sum > store_reference.get_money()) break;
        products.push_back(std::move(store_reference.products[index]));
    }
    store_reference.products.erase(std::remove(store_reference.products.begin(), store_reference.products.end(),
    nullptr), store_reference.products.end());
    if(products.empty()) return nullptr;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_cashier(0, cashier_indexes.size()-1);
    std::uniform_int_distribution<> dis_client(0, store_reference.available_clients.size()-1);
    int on_shift_index_cashier = dis_cashier(gen);
    int available_client_index = dis_client(gen);

    store_reference.taken_clients.push_back(
        std::move(store_reference.available_clients[available_client_index]));
    store_reference.available_clients.erase(std::remove(store_reference.available_clients.begin(),
    store_reference.available_clients.end(), nullptr),store_reference.available_clients.end());

    return std::make_unique<ClientBuysEvent>(store_reference,
            store_reference.taken_clients.size() - 1,
            cashier_indexes[on_shift_index_cashier],
            products);  // do napisania Random Event
}
