#include "cleaner.hpp"

Cleaner::Cleaner(std::string new_name, std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule, Money new_bonus, Money new_base_hourly_wage):
Employee{new_name, new_weekly_schedule, new_bonus, new_base_hourly_wage}
{}

Money Cleaner::calculate_weekly_salary() const
{
    return (base_hourly_wage + bonus + Money(5)) * calculate_hours_worked();
}

void Cleaner::clean_shop()
{   employee_interface.print("Cleaner " + this->get_name() + ": Oh my! It got a little bit dirty here.\n");
    employee_interface.print("Cleaner " + this->get_name() + " has cleaned the shop.\n");
}


void Cleaner::start_message() const
{
    employee_interface.print("Cleaner " + this->get_name() + " has begun a shift.\n");
}

void Cleaner::end_message() const
{
    employee_interface.print("Cleaner " + this->get_name() + " has finished a shift.\n");

}
