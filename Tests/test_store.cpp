#include "catch_amalgamated.hpp"
#include "../Store/Store.hpp"
#include <numeric>
#include <stdexcept>
#include <vector>


TEST_CASE("Store tests")
{
    Store store;
    Money initial_money(10000);

    std::vector<std::unique_ptr<Product>> products;
    products.push_back(std::make_unique<Product>("Product1", Money(1000)));
    products.push_back(std::make_unique<Product>("Product2", Money(1500)));

    std::vector<std::unique_ptr<Client>> clients;
    clients.push_back(std::make_unique<Client>("Marian", "Piernik", Money(11200), StoreTime(5)));
    clients.push_back(std::make_unique<Client>("Pan", "Spod czworki", Money(123), StoreTime(10)));

    std::vector<std::unique_ptr<Employee>> employees;
    std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule;
    new_weekly_schedule["mon"] = std::make_tuple(8, 14);
    new_weekly_schedule["tue"] = std::make_tuple(8, 14);
    new_weekly_schedule["wed"] = std::make_tuple(14, 20);
    new_weekly_schedule["thu"] = std::make_tuple(14, 20);
    new_weekly_schedule["fri"] = std::make_tuple(8, 14);
    new_weekly_schedule["sat"] = std::make_tuple(14, 20);
    new_weekly_schedule["sun"] = std::make_tuple(14, 20);
    employees.push_back(std::make_unique<Employee>("Pani Krysia", new_weekly_schedule, Money(4000), Money(3000)));
    employees.push_back(std::make_unique<Employee>("Pani Jola", new_weekly_schedule, Money(3000), Money(2500)));

    store = Store(products, clients, employees, initial_money);

    SECTION("Store Initialization") {
        REQUIRE(store.get_money().full_price == 10000);
        REQUIRE(store.get_products().size() == 2);
        REQUIRE(store.get_clients().size() == 2);
        REQUIRE(store.get_employees().size() == 2);
    }

    SECTION("Add Products") {
        std::vector<std::unique_ptr<Product>> new_products;
        new_products.push_back(std::make_unique<Product>("Product3", Money(2000)));
        store.add_products(new_products);
        REQUIRE(store.get_products().size() == 3);
    }

    SECTION("Add Clients") {
        std::vector<std::unique_ptr<Client>> new_clients;
        new_clients.push_back(std::make_unique<Client>("Jan", "Kowalski", Money(500), StoreTime(3)));
        store.add_clients(new_clients);
        REQUIRE(store.get_clients().size() == 3);
    }

    SECTION("Add Employees") {
        std::vector<std::unique_ptr<Employee>> new_employees;
        new_employees.push_back(std::make_unique<Employee>("Pani Zosia", new_weekly_schedule, Money(2000), Money(1500)));
        store.add_employees(new_employees);
        REQUIRE(store.get_employees().size() == 3);
    }

    SECTION("Add Money") {
        Money added_money(5000);
        store.add_money(added_money);
        REQUIRE(store.get_money().full_price == 15000);
    }

    SECTION("Take Money Out") {
        Money to_take(3000);
        store.take_money_out(to_take);
        REQUIRE(store.get_money().full_price == 7000);
        REQUIRE_THROWS_AS(store.take_money_out(Money(20000)), std::invalid_argument);
    }
}

TEST_CASE("EventGenerator tests")
{
    Money initial_money(10000);

    std::vector<std::unique_ptr<Product>> products;
    products.push_back(std::make_unique<Product>("Product1", Money(1000)));
    products.push_back(std::make_unique<Product>("Product2", Money(1500)));

    std::vector<std::unique_ptr<Client>> clients;
    clients.push_back(std::make_unique<Client>("Marian", "Piernik", Money(11200), StoreTime(5)));
    clients.push_back(std::make_unique<Client>("Pan", "Spod czworki", Money(123), StoreTime(10)));

    std::vector<std::unique_ptr<Employee>> employees;
    std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule;
    new_weekly_schedule["mon"] = std::make_tuple(8, 14);
    new_weekly_schedule["tue"] = std::make_tuple(8, 14);
    new_weekly_schedule["wed"] = std::make_tuple(14, 20);
    new_weekly_schedule["thu"] = std::make_tuple(14, 20);
    new_weekly_schedule["fri"] = std::make_tuple(8, 14);
    new_weekly_schedule["sat"] = std::make_tuple(14, 20);
    new_weekly_schedule["sun"] = std::make_tuple(14, 20);
    employees.push_back(std::make_unique<Employee>("Pani Krysia", new_weekly_schedule, Money(4000), Money(3000)));
    employees.push_back(std::make_unique<Employee>("Pani Jola", new_weekly_schedule, Money(3000), Money(2500)));

    Store store(products, clients, employees, initial_money);

    std::vector<float> probabilities_of_events = {0.25, 0.25, 0.25, 0.25};
    EventGenerator event_generator(store, probabilities_of_events);

    SECTION("Draw event type with no exclusions") {
        std::vector<int> exclude_indexes;
        std::map<int, int> event_counts;

        for (int i = 0; i < 1000; ++i) {
            int event_type = event_generator.draw_event_type(exclude_indexes);
            REQUIRE(event_type >= 0);
            REQUIRE(event_type < 4);
            event_counts[event_type]++;
        }

        for (const auto& pair : event_counts) {
            REQUIRE(pair.second > 0);
        }
    }

    SECTION("Draw event type with some exclusions") {
        std::vector<int> exclude_indexes = {0, 1};
        std::map<int, int> event_counts;

        for (int i = 0; i < 1000; ++i) {
            int event_type = event_generator.draw_event_type(exclude_indexes);
            REQUIRE((event_type == 2 || event_type == 3));
            event_counts[event_type]++;
        }

        REQUIRE(event_counts[0] == 0);
        REQUIRE(event_counts[1] == 0);
    }

    SECTION("Draw event type with all exclusions except one") {
        std::vector<int> exclude_indexes = {0, 1, 2};

        for (int i = 0; i < 1000; ++i) {
            int event_type = event_generator.draw_event_type(exclude_indexes);
            REQUIRE(event_type == 3);
        }
    }}