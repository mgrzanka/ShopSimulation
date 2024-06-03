#include "CleanerCleansEvent.hpp"
#include "RandomEvent.hpp"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>


CleanerCleans::CleanerCleans(Store& store, unsigned int cleaner_index): RandomEvent(store)
{
    Cleaner* cleaner = dynamic_cast<Cleaner*>(store.on_shift_occupied_employees[cleaner_index].get());
    if(cleaner)
    {
        this->cleaner = std::make_unique<Cleaner>(*cleaner);
    }
    else throw std::invalid_argument("Something went wrong in event generator - this employee is not a cleaner!");
}

void CleanerCleans::perform_action()
{
    cleaner->clean_shop();
}

void CleanerCleans::return_elements()
{
    auto& employees = store.on_shift_occupied_employees;
    auto original_pointer = std::find_if(employees.begin(), employees.end(), [&](const std::unique_ptr<Employee>& emp) {return
    emp->calculate_hours_worked() == cleaner->calculate_hours_worked() && emp->calculate_weekly_salary() == cleaner->calculate_weekly_salary() &&
    emp->get_name() == cleaner->get_name() && emp->get_bonus() == cleaner->get_bonus();});

    store.on_shift_employees.push_back(std::move(*original_pointer));
    store.on_shift_occupied_employees.erase(original_pointer);
}