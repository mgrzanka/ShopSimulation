#include "manager.hpp"
#include <stdexcept>

Manager::Manager(std::string new_name, std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule, Money new_bonus, Money new_base_hourly_wage):
Employee{new_name, new_weekly_schedule, new_bonus, new_base_hourly_wage}
{}

Money Manager::calculate_weekly_salary() const
{
    return (base_hourly_wage + bonus + Money(20)) * calculate_hours_worked();
}

void Manager::praise_employee(std::string employee_name)
{
    employee_interface.print("Manager " + this->get_name() + ":" + employee_name + ", I'm really pleased with the work your're doing. Well done!\n");
}
void Manager::give_rise(Employee& employee, const Money& rise){
 interaction_while_giving_rise(employee.get_name());
 employee.set_bonus(employee.get_bonus() + rise);
 display_rise_message(employee.get_name());

}

void Manager::interaction_while_giving_rise(std::string employee_name)
{
    employee_interface.print("Manager " + this->get_name() + ":" + employee_name + ", you've been doing your job really well lately. I'm happy to raise your hourly wage.\n");
}


void Manager::display_rise_message(std::string employee_name)
{
    employee_interface.print("Manager " + this->get_name() +" gave" + employee_name + " a rise.\n");
}

void Manager::start_message() const
{
    employee_interface.print("Manager " + this->get_name() + " has begun a shift.\n");
}

void Manager::end_message() const
{
    employee_interface.print("Manager " + this->get_name() + " has finished a shift.\n");
}