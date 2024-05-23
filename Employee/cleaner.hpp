#ifndef CLEANER_HPP
#define CLEANER_HPP
#include "employee.hpp"


class Cleaner : public Employee
{
    StoreTime time_on_cleaning;
    public:
    Cleaner(std::string name, std::map<std::string, std::tuple<unsigned int, unsigned int>> weekly_schedule, Money bonus, Money base_hourly_wage, StoreTime time_on_cleaning);
    Money calculate_weekly_salary() const override;
    StoreTime get_time_on_cleaning();
    void clean_shop();

    void start_message() const override;
    void end_message() const override;


};

#endif