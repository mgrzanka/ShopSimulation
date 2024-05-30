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
        MenagerGivesRise(Store& store, float probability, std::unique_ptr<Manager>& menager, std::unique_ptr<Employee>& employee);
        virtual void end_message() const override;
        virtual void perform_action() override;
        virtual void restore() override;
        virtual bool check_action() const override;
};

#endif
