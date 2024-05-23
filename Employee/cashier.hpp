#ifndef CASHIER_HPP
#define CASHIER_HPP
#include "employee.hpp"
#include <string>
#include <vector>


class Cashier : public Employee
{
    public:
    Cashier(std::string name, std::map<std::string, std::tuple<unsigned int, unsigned int>> weekly_schedule, Money bonus, Money base_hourly_wage);
    Money calculate_weekly_salary() const override;
    void serve_the_client();

    void start_message() const override;
    void end_message() const override;



};


#endif

