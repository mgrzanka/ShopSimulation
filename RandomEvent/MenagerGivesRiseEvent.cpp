#include "MenagerGivesRiseEvent.hpp"
#include "RandomEvent.hpp"
#include <memory>
#include <vector>


MenagerGivesRise::MenagerGivesRise(Store& store, float probability, std::unique_ptr<Manager> menager, std::unique_ptr<Employee> employee):
RandomEvent(store, probability)
{
    this->menager = std::move(menager);
    this->employee = std::move(employee);
    this->counter = menager->get_time_promoting_employee().get_iterations();
}

void MenagerGivesRise::end_message() const
{
    menager->display_rise_message(employee->get_name());
}

void MenagerGivesRise::perform_action()
{
    if(counter != 0 && counter % 2 == 0) menager->praise_employee(employee->get_name());
    else if (counter == 0)
    {
        menager->interaction_while_giving_rise(employee->get_name());
        employee->get_raise(Money(50000)); // narazie zhardodowane, mozna pomyslec nad randomową ilością
    }
}

bool MenagerGivesRise::check_action() const
{
    return counter % 2 == 0;
}

void MenagerGivesRise::restore()
{
    std::vector<std::unique_ptr<Employee>> e = {std::move(employee), std::move(menager)};
    store.add_employee(e);
}
