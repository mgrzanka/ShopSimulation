#include "storekeeper.hpp"

Storekeeper::Storekeeper(std::string new_name, std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule, Money new_bonus, Money new_base_hourly_wage):
Employee{new_name, new_weekly_schedule, new_bonus, new_base_hourly_wage}
{
    for (auto pair : new_weekly_schedule) {
        if (pair.first == "sun" || pair.first == "sat") {
            throw std::invalid_argument("Storekeepers cannot work on weekends.");
        }
}

if (calculate_hours_worked()>30) {
        throw std::invalid_argument("Storekeepers cannot work more than 30 hours a week.");
    }
}


Money Storekeeper::calculate_weekly_salary() const
{
    return (base_hourly_wage + bonus + Money(8)) * calculate_hours_worked();
}

void Storekeeper::start_message() const
{
    employee_interface.print("Storekeeper " + this->get_name() + " has begun a shift.\n")
}

void Storekeeper::end_message() const
{
    employee_interface.print("Storekeeper " + this->get_name() + " has finished a shift.\n")
}