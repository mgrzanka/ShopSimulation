#include "MenagerGivesRiseEvent.hpp"
#include "RandomEvent.hpp"
#include <algorithm>
#include <memory>
#include <vector>


MenagerGivesRise::MenagerGivesRise(Store& store, unsigned int menager_index, unsigned int employee_indx):
RandomEvent(store)
{
    Manager* manager = dynamic_cast<Manager*>(store.on_shift_occupied_employees[menager_index].get());
    if(manager)
    {
        this->menager = std::make_unique<Manager>(*manager);
    }
    else throw std::invalid_argument("Something went wrong in event generator - this employee is not a menager!");

    this->employee = std::move(store.on_shift_occupied_employees[employee_indx]);
    store.on_shift_occupied_employees.erase(std::remove(store.on_shift_occupied_employees.begin(), store.on_shift_occupied_employees.end(),
    nullptr), store.on_shift_occupied_employees.end());
}

void MenagerGivesRise::end_message() const
{
    menager->display_rise_message(employee->get_name(), employee->get_bonus());
}

void MenagerGivesRise::perform_action()
{
    menager->praise_employee(employee->get_name());
    menager->interaction_while_giving_rise(employee->get_name());
    employee->get_raise(employee->get_bonus());
}

void MenagerGivesRise::return_elements()
{
    auto& employees = store.on_shift_occupied_employees;

    // Find the original manager pointer
    auto original_manager_it = std::find_if(employees.begin(), employees.end(),
        [&](const std::unique_ptr<Employee>& emp) {
            Manager* manager_emp = dynamic_cast<Manager*>(emp.get());
            return manager_emp &&
                   manager_emp->calculate_hours_worked() == menager->calculate_hours_worked() &&
                   manager_emp->calculate_weekly_salary() == menager->calculate_weekly_salary() &&
                   manager_emp->get_name() == menager->get_name() &&
                   manager_emp->get_bonus() == menager->get_bonus();
        });
    // Move the original manager back to on_shift_employees
    if (original_manager_it != employees.end())
    {
        store.on_shift_employees.push_back(std::move(*original_manager_it));
        employees.erase(original_manager_it); // Erase the old pointer
    }
    store.on_shift_employees.push_back(std::move(employee));
}
