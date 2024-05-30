#ifndef _EVENT_GENERATOR_
#define _EVENT_GENERATOR_

#include "../Store/Store.hpp"
#include "../RandomEvent/RandomEvent.hpp"
#include "../RandomEvent/CleanerCleansEvent.hpp"
#include "../RandomEvent/ClientBuysEvent.hpp"
#include "../RandomEvent/MenagerGivesRiseEvent.hpp"
#include "../RandomEvent/SupplierAddsProductsEvent.hpp"
#include <memory>
#include <vector>


class EventGenerator
{
    Store& store_reference;
    std::vector<float> probabilities_of_events;  // dany jako input programu od uzytkownika
    std::vector<int> events_indexes;

    int draw_event_type();

    public:
        EventGenerator(Store& store_reference,
                        std::vector<float> probabilities_of_events);
        std::unique_ptr<RandomEvent>& draw_event();
};

#endif
