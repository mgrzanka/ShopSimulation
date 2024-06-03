#ifndef _EVENT_GENERATOR_
#define _EVENT_GENERATOR_

#include "../Store/Store.hpp"
#include "../RandomEvent/RandomEvent.hpp"
#include "../RandomEvent/CleanerCleansEvent.hpp"
#include "../RandomEvent/ClientBuysEvent.hpp"
#include "../RandomEvent/MenagerGivesRiseEvent.hpp"
#include "../RandomEvent/SupplierAddsProductsEvent.hpp"
#include "../FileHandler/FileHandler.hpp"
#include <memory>
#include <random>
#include <vector>


class EventGenerator
{
    Store& store_reference;
    std::vector<float> probabilities_of_events;
    std::vector<int> events_indexes;

    int draw_event_type(std::vector<int>& exclude_indexes) const;

    std::unique_ptr<RandomEvent> draw_cleaner_cleans(std::vector<int> indexes);
    // std::unique_ptr<RandomEvent> draw_supplier_adds(std::vector<int> indexes);
    std::unique_ptr<RandomEvent> draw_supplier_adds(std::vector<int> indexes, FileHandler& file_handler);
    std::unique_ptr<RandomEvent> draw_manager_gives_raise(std::vector<int> indexes);
    std::unique_ptr<RandomEvent> draw_client_buys(std::vector<int> indexes);

    std::vector<unsigned int> pick_products_indexes();
    // std::vector<std::unique_ptr<Product>> pick_new_products();

    public:
        EventGenerator(Store& store_reference,
                        std::vector<float> probabilities_of_events);
        // std::unique_ptr<RandomEvent> draw_event(std::vector<int> indexes);
        std::unique_ptr<RandomEvent> draw_event(std::vector<int> indexes, FileHandler& file_handler);
    //std::vector<std::unique_ptr<Product>> pick_new_products();
    std::vector<std::unique_ptr<Product>> pick_new_products(FileHandler& file_handler);
};

#endif
