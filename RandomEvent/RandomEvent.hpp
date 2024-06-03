#ifndef _RANDOM_EVENT_HPP_
#define _RANDOM_EVENT_HPP_
#include <iostream>
#include <memory>


#include "../Store/Store.hpp"


class RandomEvent
{
    protected:
        Store& store;
    public:
        RandomEvent(Store& store);
        virtual ~RandomEvent() = default;

        virtual void start_message() const;
        virtual void end_message() const;

        virtual void perform_action() = 0;
        virtual void return_elements() = 0;
};



#endif
