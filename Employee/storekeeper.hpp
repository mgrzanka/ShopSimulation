#ifndef STOREKEEPER_HPP
#define STOREKEEPER_HPP
#include "employee.hpp"

class Storekeeper : public Employee
{
    StoreTime time_to_replenish;
    public:
    Storekeeper(std::string name, std::map<std::string, std::tuple<unsigned int, unsigned int>> weekly_schedule, Money bonus, Money base_hourly_wage, StoreTime time_to_replenish);

    StoreTime get_time_to_replenish();
    Money calculate_weekly_salary() const override;
    void replenish_stock(std::string product_name);
    void display_replenishing_message(std::string product_name);

    void start_message() const override;
    void end_message() const override;

};
#endif