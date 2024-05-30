#ifndef MANAGER_HPP
#define MANAGER_HPP
#include "employee.hpp"


class Manager : public Employee
{
    StoreTime time_promoting_employee;
    public:
    Manager(std::string name, std::map<std::string, std::tuple<unsigned int, unsigned int>> weekly_schedule, Money bonus, Money base_hourly_wage, StoreTime time_promoting_employee);

    StoreTime get_time_promoting_employee();

    Money calculate_weekly_salary() const override;
    void tell_off_employee(std::string employee_name);
    void praise_employee(std::string employee_name);

    // void give_rise(Employee& employee, const Money& rise); trzeba to robic z poziomu pracownika
    void interaction_while_giving_rise(std::string employee_name);
    void display_rise_message(std::string employee_name);

    void start_message() const override;
    void end_message() const override;


};

#endif