#ifndef STOREKEEPER_HPP
#define STOREKEEPER_HPP
#include "employee.hpp"
#include <vector>

class Storekeeper : public Employee
{
    public:
    Storekeeper(std::string name, std::map<std::string, std::tuple<unsigned int, unsigned int>> weekly_schedule, Money bonus, Money base_hourly_wage);

    Money calculate_weekly_salary() const override;
    void display_replenishing_message(std::vector<std::string> names, Money sum);

    void start_message() const override;
    void end_message() const override;

};
#endif