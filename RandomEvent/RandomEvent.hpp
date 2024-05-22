#ifndef _RANDOM_EVENT_HPP_
#define _RANDOM_EVENT_HPP_
#include <iostream>
#include <memory>


#include "../Store/Store.hpp"


class RandomEvent
{
    protected:
        unsigned int counter;
        float probability;  // probability bedzie zhardcodowane dla danego rodzaju eventu
        Store& store;
    public:
        RandomEvent(Store& store);
        virtual ~RandomEvent() = default;
        unsigned int get_counter();
        void decrease_counter();
        float get_probability();

        virtual bool check_action() const;

        virtual void start_message() const = 0;
        virtual void end_message() const = 0;
        virtual void perform_action() = 0;
        virtual void restore() = 0;
};



#endif