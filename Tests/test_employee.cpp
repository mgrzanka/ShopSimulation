#include "catch_amalgamated.hpp"
#include "../Employee/cashier.hpp"
#include "../Employee/manager.hpp"
#include "../Employee/storekeeper.hpp"
#include "../Employee/cleaner.hpp"


TEST_CASE("Cashier class") {
    std::map<std::string, std::tuple<unsigned int, unsigned int>> weekly_schedule = {{"mon", {8, 16}}, {"tue", {8, 16}}, {"wed", {8, 16}}, {"thu", {8, 16}}, {"fri", {8, 16}}};
    Cashier cashier("John", weekly_schedule, Money(100), Money(20));
    REQUIRE(cashier.get_name() == "John");
    REQUIRE(cashier.get_base_hourly_wage().full_price == 20);
    REQUIRE(cashier.get_bonus().full_price == 100);
    REQUIRE(cashier.calculate_hours_worked() == 40);
    REQUIRE(cashier.calculate_weekly_salary().full_price == (20 + 100 + 10) * 40);
}

TEST_CASE("Cleaner class")
{
    std::map<std::string, std::tuple<unsigned int, unsigned int>> weekly_schedule = {{"mon", {8, 12}}, {"tue", {8, 12}}, {"wed", {8, 12}}, {"thu", {8, 12}}, {"fri", {8, 12}}};
    Cleaner cleaner("Alice", weekly_schedule, Money(100), Money(20));
    REQUIRE(cleaner.get_name() == "Alice");
    REQUIRE(cleaner.get_base_hourly_wage().full_price == 20);
    REQUIRE(cleaner.get_bonus().full_price == 100);
    REQUIRE(cleaner.calculate_hours_worked() == 20);
    REQUIRE(cleaner.calculate_weekly_salary().full_price == (20 + 100 + 5) * 20);
}

TEST_CASE("Manager class")
{
    std::map<std::string, std::tuple<unsigned int, unsigned int>> weekly_schedule = {{"mon", {9, 14}}, {"tue", {9, 14}}, {"wed", {9, 14}}, {"thu", {9, 14}}, {"fri", {9, 14}}};
    Manager manager("Alice", weekly_schedule, Money(100), Money(20));
    Cashier cashier("John", weekly_schedule, Money(100), Money(20));

    REQUIRE(manager.get_name() == "Alice");
    REQUIRE(manager.get_base_hourly_wage().full_price == 20);
    REQUIRE(manager.get_bonus().full_price == 100);
    REQUIRE(manager.calculate_hours_worked() == 25);
    REQUIRE(manager.calculate_weekly_salary().full_price == (20 + 100 + 20) * 25);
    manager.give_rise(cashier, Money(15));
    REQUIRE(cashier.get_bonus().full_price == 115);

}

TEST_CASE("Storekeeper class")
{
    std::map<std::string, std::tuple<unsigned int, unsigned int>> weekly_schedule = {{"mon", {8, 13}}, {"tue", {8, 13}}, {"wed", {8, 13}}, {"thu", {8, 13}}, {"fri", {8, 13}}};
    Storekeeper storekeeper("Alice", weekly_schedule, Money(100), Money(20));

    REQUIRE(storekeeper.get_name() == "Alice");
    REQUIRE(storekeeper.get_base_hourly_wage().full_price == 20);
    REQUIRE(storekeeper.get_bonus().full_price == 100);
    REQUIRE(storekeeper.calculate_hours_worked() == 25);
    REQUIRE(storekeeper.calculate_weekly_salary().full_price == (20 + 100 + 8) * 25);


}
