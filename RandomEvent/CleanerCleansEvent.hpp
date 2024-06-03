#ifndef _CLEANER_CLEANS_
#define _CLEANER_CLEANS_

#include "RandomEvent.hpp"
#include "../Employee/cleaner.hpp"
#include <memory>


class CleanerCleans: public RandomEvent
{
    std::unique_ptr<Cleaner> cleaner;
    public:
        CleanerCleans(Store& store, unsigned int cleaner_index);
        virtual void perform_action() override;
        virtual void return_elements() override;
};


#endif