#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_
#include <iostream>
#include <vector>


#include "../Structures.hpp"
#include "../Store/Store.hpp"
#include "../FileHandler/FileHandler.hpp"
#include "../UserInterface/UserInterface.hpp"
#include "../RandomEvent/RandomEvent.hpp"


class Simulation
{
    unsigned int iterations_opened;
    unsigned int iterations_closed;
    unsigned int minutes_per_iteration;
    unsigned int starting_hour;
    unsigned int days;

    Store store;
    FileHandler file_handler;
    UserInterface simulation_interface;

    unsigned int draw_index(const std::vector<float>& probabilities) const;
    std::string get_hour(int i);

    public:
        const Store& get_store() const;
        Simulation(unsigned int days, unsigned int starting_hour, StoreTime hours_per_day, std::string path_to_data_file);
        void run();
};

#endif