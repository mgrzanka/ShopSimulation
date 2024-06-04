#include "gtest/gtest.h"
#include <algorithm>
#include <memory>
#include <utility>
#include <vector>
#include "../Store/Store.hpp"

#include "../Client/Client.hpp"
#include "../Client/RegularClient.hpp"
#include "../Product/Beverage.hpp"

#include "../RandomEvent/CleanerCleansEvent.hpp"
#include "../RandomEvent/ClientBuysEvent.hpp"
#include "../EventsGenerator/EventsGenerator.hpp"
#include "../PeopleParser/PeopleParser.hpp"

#include "../Simulation/Simulation.hpp"
#include "../FileHandler/FileHandler.hpp"


TEST(Store, Store)
{
    Store store;
    std::unique_ptr<Client> client1 = std::make_unique<RegularClient>("M", "G", Money(100000000));
    std::unique_ptr<Client> client2 = std::make_unique<RegularClient>("I", "G", Money(1000));
    std::vector<std::unique_ptr<Client>> vec; vec.push_back(std::move(client1)); vec.push_back(std::move(client2));

    store.add_clients(vec);
    auto& products = store.get_products();
}

TEST(EventGenerator, EventGenerator)
{
    std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule;
    new_weekly_schedule["mon"] = std::make_tuple(9, 20);
    std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule2;
    new_weekly_schedule2["mon"] = std::make_tuple(9, 21);
    new_weekly_schedule2["tue"] = std::make_tuple(8, 14);
    new_weekly_schedule2["wed"] = std::make_tuple(14, 20);
    new_weekly_schedule2["thu"] = std::make_tuple(14, 20);
    new_weekly_schedule2["fri"] = std::make_tuple(8, 14);
    // new_weekly_schedule2["sat"] = std::make_tuple(14, 20);
    // new_weekly_schedule2["sun"] = std::make_tuple(14, 20);

    // Creating store
    std::unique_ptr<Client> client1 = std::make_unique<RegularClient>("M", "G", Money(100000000));
    std::unique_ptr<Client> client2 = std::make_unique<RegularClient>("I", "G", Money(1000));
    std::vector<std::unique_ptr<Client>> clients; clients.push_back(std::move(client1)); clients.push_back(std::move(client2));

    std::unique_ptr<Beverage> beverage1 = std::make_unique<Beverage>("Napoj", Money(12));
    std::unique_ptr<Beverage> beverage2 = std::make_unique<Beverage>("Drink", Money(120));
    std::vector<std::unique_ptr<Product>> products; products.push_back(std::move(beverage1)); products.push_back(std::move(beverage2));

    std::unique_ptr<Cashier> cashier = std::make_unique<Cashier>("Cashier", new_weekly_schedule2, Money(12), Money(123));
    std::unique_ptr<Cleaner> cleaner = std::make_unique<Cleaner>("Cleaner", new_weekly_schedule, Money(12), Money(10));
    std::unique_ptr<Storekeeper> store_keeper = std::make_unique<Storekeeper>("Keeper", new_weekly_schedule2, Money(12), Money(10));
    std::unique_ptr<Manager> manager = std::make_unique<Manager>("Manager", new_weekly_schedule, Money(12), Money(10));
    std::vector<std::unique_ptr<Employee>> employees; employees.push_back(std::move(store_keeper));
    employees.push_back(std::move(cashier)); employees.push_back(std::move(cleaner));
    employees.push_back(std::move(manager));

    // Store store(products, clients, employees, Money(1300));
    // store.add_money(Money(12));
    // EXPECT_EQ(store.get_money(), Money(1312));
    // store.take_money_out(Money(12));
    // EXPECT_EQ(store.get_money(), Money(1300));

    PeopleParser people_parser("/home/gosia/PROI/proi_24l_101_projekt/names.txt");
    std::vector<std::unique_ptr<Client>> xclients = people_parser.generate_clients();
    std::vector<std::unique_ptr<Employee>> xemployees = people_parser.generate_employees();

    // Powazniejszy test
    Store real_store(products, clients, employees, Money(12000000));
    std::vector<float> probabilities = {0.1, 0.4, 0.1, 0.4};
    EventGenerator event_generator(real_store, probabilities);
    FileHandler file_handler("/home/gosia/PROI/proi_24l_101_projekt/products.txt");

    Simulation simulation(2, 8, 20, real_store, probabilities, file_handler);
    simulation.run();

    // std::tuple<std::vector<int>,std::vector<int>> employees_tuple = real_store.check_employee_shift(1, 100, 8, 20);
    // real_store.update_employees_shift(employees_tuple);
    // std::vector<int> indexes = std::get<1>(employees_tuple);
    // real_store.update_employees_shift(employees_tuple);

    // auto event = std::move(event_generator.draw_event(indexes, file_handler));

    // if(event)
    // {
    //     event->start_message();
    //     event->perform_action();
    //     event->end_message();
    //     event->return_elements();
    // }

    // auto event2 = std::move(event_generator.draw_event(indexes));
    // if(event2)
    // {
    //     event2->start_message();
    //     event2->perform_action();
    //     event2->decrease_counter();
    //     event2->end_message();
    //     event2->check_action();
    //     event2->return_elements();
    // }

    // auto event3 = std::move(event_generator.draw_event(indexes));
    // if(event3)
    // {
    //     event3->start_message();
    //     event3->perform_action();
    //     event3->decrease_counter();
    //     event3->end_message();
    //     event3->check_action();
    //     event3->return_elements();
    // }

    // auto event4 = std::move(event_generator.draw_event(indexes));
    // if(event4)
    // {
    //     event4->start_message();
    //     event4->perform_action();
    //     event4->decrease_counter();
    //     event4->end_message();
    //     event4->check_action();
    //     event4->return_elements();
    // }

    // auto event5 = std::move(event_generator.draw_event(indexes));
    // if(event5)
    // {
    //     event5->start_message();
    //     event5->perform_action();
    //     event5->decrease_counter();
    //     event5->end_message();
    //     event5->check_action();
    //     event5->return_elements();
    // }

    // auto event6 = std::move(event_generator.draw_event(indexes));
    // if(event6)
    // {
    //     event6->start_message();
    //     event6->perform_action();
    //     event6->decrease_counter();
    //     event6->end_message();
    //     event6->check_action();
    //     event6->return_elements();
    // }

}