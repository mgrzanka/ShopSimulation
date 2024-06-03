#ifndef _MENAGER_TALKS_
#define _MENAGER_TALKS_


#include "CleanerCleansEvent.hpp"
#include "RandomEvent.hpp"
#include "../Client/MenagersFriend.hpp"
#include "../Employee/manager.hpp"
#include <memory>


class MenagerGivesRise: public RandomEvent
{
    std::unique_ptr<Manager> menager;
    std::unique_ptr<Employee> employee;
    public:
        MenagerGivesRise(Store& store, unsigned int menager_index, unsigned int employee_indx);
        virtual void end_message() const override;
        virtual void perform_action() override;
        virtual void return_elements() override;
};

#endif
