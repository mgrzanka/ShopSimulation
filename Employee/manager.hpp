#ifndef MANAGER_HPP
#define MANAGER_HPP
#include "employee.hpp"


class Manager : public Employee
{
    public:
    Manager(std::string name, std::map<std::string, std::tuple<unsigned int, unsigned int>> weekly_schedule, Money bonus, Money base_hourly_wage);

    Money calculate_weekly_salary() const override;
    void praise_employee(std::string employee_name);

    void give_rise(Employee& employee, const Money& rise);
    void interaction_while_giving_rise(std::string employee_name);
    void display_rise_message(std::string employee_name, Money sum);

    void start_message() const override;
    void end_message() const override;


};

#endif