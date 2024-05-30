#include "CleanerCleansEvent.hpp"
#include "RandomEvent.hpp"
#include <memory>
#include <vector>


CleanerCleans::CleanerCleans(Store& store, float probability, std::unique_ptr<Cleaner> cleaner):
RandomEvent(store, probability)
{
    this->cleaner = std::move(cleaner);
    this->counter = cleaner->get_time_on_cleaning().get_iterations();
}

void CleanerCleans::start_message() const
{
    cleaner->start_message();
}

void CleanerCleans::end_message() const
{
    cleaner->end_message();
}

void CleanerCleans::perform_action()
{
    cleaner->clean_shop();
}

void CleanerCleans::restore()
{
    std::vector<std::unique_ptr<Cleaner>> c = {std::move(cleaner)};
    store.add_employee(c);
}
