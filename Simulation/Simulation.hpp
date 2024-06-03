#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_
#include <iostream>
#include <tuple>
#include <vector>

#include "../Client/RegularClient.hpp"
#include "../EventsGenerator/EventsGenerator.hpp"
#include "../Structures.hpp"
#include "../Store/Store.hpp"
#include "../FileHandler/FileHandler.hpp"
#include "../UserInterface/UserInterface.hpp"
#include "../RandomEvent/RandomEvent.hpp"
#include "../Product/Product.hpp"
#include "../Product/Breadstuff.hpp"
#include "../Product/Dairy_product.hpp"
#include "../Product/Fruit_vegetable.hpp"
#include "../Product/Cosmetics.hpp"
#include "../Product/Beverage.hpp"
#include "../Product/Industrial_article.hpp"

enum class Day
{
    monday, thuesday, wednesday, thursday, friday, saturday, sunday
};
Day& operator++(Day& d);


class Simulation
{
    unsigned int iteration_counter; unsigned int day_counter; Day day;
    unsigned int starting_hour; unsigned int ending_hour; unsigned int number_of_days;
    UserInterface simulation_interface;
    Store& store;
    std::vector<float> probabilities;
    FileHandler& file_handler;

    std::string day_to_string(int day) const;
    std::string get_hour(unsigned int i) const;
    bool if_new_event() const;

    public:
        Simulation(unsigned int days, unsigned int starting_hour, unsigned int ending_hour,
        Store& store, std::vector<float> probabilities, FileHandler& file_handler);
        void first_supply(std::vector<std::unique_ptr<Product>>& supply);
        FileHandler& get_file_handler() const;
        void run();
};


// class Simulation
// {
//     unsigned int iterations_opened;
//     unsigned int iterations_closed;
//     unsigned int minutes_per_iteration;
//     unsigned int starting_hour;
//     unsigned int days;

//     Store store;
//     FileHandler file_handler;
//     UserInterface simulation_interface;

//     std::string get_hour(int i);

//     public:
//         const Store& get_store() const;
//         Simulation(unsigned int days, unsigned int starting_hour, StoreTime hours_per_day, std::string path_to_data_file);
//         void run();
// };

#endif