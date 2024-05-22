#include "cashier.hpp"
#include <stdexcept>

Cashier::Cashier(std::string new_name, std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule, Money new_bonus, Money new_base_hourly_wage):
Employee{new_name, new_weekly_schedule, new_bonus, new_base_hourly_wage}
{
    if (calculate_hours_worked()>48) {
        throw std::invalid_argument("Cashiers cannot work more than 48 hours a week.");
    }

    for (auto pair : new_weekly_schedule) {
        if (pair.first == "sun") {
            throw std::invalid_argument("Cashiers cannot work on Sundays.");
        }

}
}

Money Cashier::calculate_weekly_salary() const
{
    return (base_hourly_wage + bonus + Money(10)) * calculate_hours_worked();
}

void Cashier::serve_the_client(std::string product_name)
{
    employee_interface.print("Cashier " + this->get_name() + ": Here you go, sweetheart! Here you have your " + product_name + ".\n");
}

void Cashier::start_message() const
{
    employee_interface.print("Cashier " + this->get_name() + " has begun a shift.\n")
}

void Cashier::end_message() const
{
    employee_interface.print("Cashier " + this->get_name() + " has finished a shift.\n")
}
