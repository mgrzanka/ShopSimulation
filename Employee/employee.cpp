#include "employee.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

Employee::Employee(std::string new_name, std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule, Money new_bonus, Money new_base_hourly_wage)
{
    if (new_name == "") {
        throw std::invalid_argument("Name cannot be empty.");
    }

    else {
        name = new_name;
    }

    std::vector<std::string> week_days;
    week_days = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"};

    if (new_weekly_schedule.size() > 7) {
            throw std::invalid_argument("Incorrect schedule format.");
        }

    for (auto pair : new_weekly_schedule) {
        auto finder = std::find(week_days.begin(), week_days.end(), pair.first);
        if (finder == week_days.end()) {
            throw std::invalid_argument("Incorrect day name. Days must be writte in a following way: mon, tue, wed, thu, fri, sat, sun.");
        }


    weekly_schedule = new_weekly_schedule;
    bonus = new_bonus;
    base_hourly_wage = new_base_hourly_wage;

}}

std::string Employee::get_name() const
{
    return name;
}
Money Employee::get_base_hourly_wage() const
{
    return base_hourly_wage;
}

std::map<std::string, std::tuple<unsigned int, unsigned int>> Employee::get_weekly_schedule() const
{
    return weekly_schedule;
}

Money Employee::get_bonus() const
{
    return bonus;
}
void Employee::set_name(std::string new_name)
{
    if (new_name == "") {
        throw std::invalid_argument("Name cannot be empty.");
    }

    else {
        name = new_name;
    }
}

void Employee::set_base_hourly_wage(Money new_base_hourly_wage)
{
    base_hourly_wage = new_base_hourly_wage;

}

void Employee::set_weekly_schedule(std::map<std::string, std::tuple<unsigned int, unsigned int>> new_weekly_schedule)
{
    std::vector<std::string> week_days;
    week_days = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"};

    if (new_weekly_schedule.size() == 7) {
            throw std::invalid_argument("Employee must have at least one day off during a week.");
        }

    if (new_weekly_schedule.size() > 7) {
            throw std::invalid_argument("Incorrect schedule format.");
        }

    for (auto pair : new_weekly_schedule) {
        auto finder = std::find(week_days.begin(), week_days.end(), pair.first);
        if (finder == week_days.end()) {
            throw std::invalid_argument("Incorrect day name. Days must be writte in a following way: mon, tue, wed, thu, fri, sat, sun.");
        }}


    weekly_schedule = new_weekly_schedule;
}

void Employee::set_bonus(Money new_bonus)
{

    bonus = new_bonus;
}

int Employee::calculate_hours_worked() const
{
     unsigned int hours_worked = 0;
    for (auto pair : weekly_schedule) {
        hours_worked += std::abs(static_cast<int>(std::get<0>(pair.second) - std::get<1>(pair.second)));
    }
    return hours_worked;

}

Money Employee::calculate_weekly_salary() const
{
    return base_hourly_wage * calculate_hours_worked();
}

std::ostream& operator<<(std::ostream& os, const Employee& client)
{
    return os<<"Employee "<<client.get_name(); //tu cos jeszcze dodam
}
