#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP
#include <string>
#include <map>
#include "../Structures.hpp"
#include "../UserInterface/UserInterface.hpp"




class Employee
{
    protected:
    std::string name;
    std::map<std::string, std::tuple<unsigned int, unsigned int>> weekly_schedule;
    Money base_hourly_wage;
    Money bonus;
    UserInterface employee_interface;

    public:
    Employee(std::string new_name, std::map<std::string, std::tuple<unsigned int,  unsigned int>> new_weekly_schedule, Money new_bonus, Money new_base_hourly_wage);

    //getters and setters
    std::string get_name() const;
    Money get_base_hourly_wage() const;
    std::map<std::string, std::tuple<unsigned int, unsigned int>> get_weekly_schedule() const;
    Money get_bonus() const;

    void set_name(std::string new_name);
    void set_base_hourly_wage(Money new_hourly_wage);
    void set_weekly_schedule(std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule);
    void set_bonus(Money new_bonus);


    void get_raise(const Money& raise_money);
    int calculate_hours_worked() const;
    virtual Money calculate_weekly_salary() const;

    virtual void start_message() const = 0;
    virtual void end_message() const = 0;

};

std::ostream& operator<<(std::ostream& os, const Employee& client);

#endif
