#include "storekeeper.hpp"

Storekeeper::Storekeeper(std::string new_name, std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule, Money new_bonus, Money new_base_hourly_wage, StoreTime time_to_replenish):
Employee{new_name, new_weekly_schedule, new_bonus, new_base_hourly_wage}, time_to_replenish {time_to_replenish}
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

StoreTime Storekeeper::get_time_to_replenish()
{
    return time_to_replenish;
}


Money Storekeeper::calculate_weekly_salary() const
{
    return (base_hourly_wage + bonus + Money(8)) * calculate_hours_worked();
}

void Storekeeper::replenish_stock(std::string product_name)
{
    //tu będzie uzupełnienie sklepu
    display_replenishing_message(product_name);
}


void Storekeeper::display_replenishing_message(std::string product_name)
{
     employee_interface.print("Storekeeper " + this->get_name() + ": Those boxes are pretty heavy! I managed to replenish" + product_name + ".\n");
     employee_interface.print("Storekeeper " + this->get_name() +" has replenished" + product_name + ".\n");
}



void Storekeeper::start_message() const
{
    employee_interface.print("Storekeeper " + this->get_name() + " has begun a shift.\n");
}

void Storekeeper::end_message() const
{
    employee_interface.print("Storekeeper " + this->get_name() + " has finished a shift.\n");
}