#include "cleaner.hpp"

Cleaner::Cleaner(std::string new_name, std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule, Money new_bonus, Money new_base_hourly_wage, StoreTime time_on_cleaning):
Employee{new_name, new_weekly_schedule, new_bonus, new_base_hourly_wage}, time_on_cleaning {time_on_cleaning}
{
    for (auto pair : new_weekly_schedule) {
        if (std::get<0>(pair.second) < 5 || std::get<0>(pair.second) > 18 ) {
            throw std::invalid_argument("Cleaners can work only between 5AM and 6PM.");
        }
}
    if (calculate_hours_worked()>30) {
        throw std::invalid_argument("Cleaners cannot work more than 30 hours a week.");
    }
}

StoreTime Cleaner::get_time_on_cleaning()
{
    return time_on_cleaning;
}

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
