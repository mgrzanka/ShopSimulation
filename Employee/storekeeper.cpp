#include "storekeeper.hpp"
#include <string>
#include <vector>

Storekeeper::Storekeeper(std::string new_name, std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule, Money new_bonus, Money new_base_hourly_wage):
Employee{new_name, new_weekly_schedule, new_bonus, new_base_hourly_wage}
{}


Money Storekeeper::calculate_weekly_salary() const
{
    return (base_hourly_wage + bonus + Money(8)) * calculate_hours_worked();
}

void Storekeeper::replenish_stock(std::string product_name)
{
    //tu będzie uzupełnienie sklepu
    // display_replenishing_message(product_name);
}


void Storekeeper::display_replenishing_message(std::vector<std::string> names, Money sum)
{
     employee_interface.print("Storekeeper " + this->get_name() + ": Those boxes are pretty heavy! I managed to replenish :");
     for(const auto& name : names) employee_interface.print(name+", ");
     employee_interface.print("for " + std::to_string(sum.get_whole_part())+"."+std::to_string(sum.get_cents())+sum.currency_name + ".\n");
}

void Storekeeper::start_message() const
{
    employee_interface.print("Storekeeper " + this->get_name() + " has begun a shift.\n");
}

void Storekeeper::end_message() const
{
    employee_interface.print("Storekeeper " + this->get_name() + " has finished a shift.\n");
}