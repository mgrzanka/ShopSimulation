#ifndef _CLEANER_CLEANS_
#define _CLEANER_CLEANS_

#include "RandomEvent.hpp"
#include "../Employee/cleaner.hpp"
#include <memory>


class CleanerCleans: public RandomEvent
{
    std::unique_ptr<Cleaner> cleaner;
    public:
        CleanerCleans(Store& store, float probability, std::unique_ptr<Cleaner> cleaner);
        virtual void start_message() const override;
        virtual void end_message() const override;
        virtual void perform_action() override;
        virtual void restore() override;
};


#endif