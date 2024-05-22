#ifndef CLEANER_HPP
#define CLEANER_HPP
#include "employee.hpp"


class Cleaner : public Employee
{
    public:
    Cleaner(std::string name, std::map<std::string, std::tuple<unsigned int, unsigned int>> weekly_schedule, Money bonus, Money base_hourly_wage);
    Money calculate_weekly_salary() const override;
    void clean_shop();

    void start_message() const override;
    void end_message() const override;


};

#endif