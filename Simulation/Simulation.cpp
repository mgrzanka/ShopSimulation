// #include "Simulation.hpp"
// #include <algorithm>
// #include <chrono>
// #include <memory>
// #include <random>
// #include <stdexcept>
// #include <string>
// #include <thread>
// #include <vector>



// Simulation::Simulation(unsigned int days, unsigned int starting_hour, StoreTime time_opened, std::string path_to_data_file):
// days {days}, starting_hour {starting_hour}, file_handler{path_to_data_file}, store {}, simulation_interface{}
// {
//     iterations_opened = time_opened.get_iterations();
//     time_opened.minutes = 24*60 - time_opened.minutes;
//     iterations_closed = time_opened.get_iterations();
//     minutes_per_iteration = time_opened.minutes_per_iteration;

//     std::vector<std::unique_ptr<Client>> clients = file_handler.load_clients();
//     std::vector<std::unique_ptr<Employee>> employees = file_handler.load_employees();
//     std::vector<std::unique_ptr<Product>> products = file_handler.load_products();
//     store.add_clients(clients);
//     store.add_employees(employees);
//     store.add_products(products);
// }

// std::string Simulation::get_hour(int i)
// {
//     unsigned int hour = starting_hour + int(i*minutes_per_iteration / 60);
//     unsigned int minutes = i*minutes_per_iteration % 60;
//     return std::to_string(hour) + ":" + std::to_string(minutes);
// }

// const Store& Simulation::get_store() const
// {
//     return store;
// }

// void Simulation::run()
// {
//     std::vector<std::unique_ptr<RandomEvent>> active_events; // inicialize active events on the begining
//     for (int d=0; d<days; d++)
//     {
//         simulation_interface.print("Day "+std::to_string(d)+" has began :)\n");
//         for (int i=0; i<iterations_opened; i++)
//         {
//             simulation_interface.print(":"+get_hour(i)+":");  // print current hour

//             // Create a new event (uwaga, mozemy ddac ze w jakiejs iteracji nie bedzie zadnego eventu, ale to moze pozniej)
//             std::unique_ptr<RandomEvent> event = std::move(store.draw_random_event());
//             event->start_message();
//             active_events.push_back(event);

//             // Deal with active events
//             for (const auto& active_event : active_events)
//             {
//                 if(active_event->check_action())
//                 {
//                     active_event->perform_action();
//                 }

//                 if(active_event->get_counter() == 0)
//                 {
//                     active_event->end_message();
//                     active_events.erase(std::remove(active_events.begin(), active_events.end(), active_event),
//                     active_events.end());
//                     active_event->restore();
//                 }

//                 active_event->decrease_counter();
//             }
//             std::this_thread::sleep_for(std::chrono::seconds(3)); // sleep, so the user won't get epilepsy
//         }
//         // end message for each active event - remaining events didne't have enough time to be performed, so we ignore them
//         for (const auto& active_event : active_events) active_event->end_message();
//         active_events.clear();

//         // time when store is closed
//         for(int i=0; i<iterations_closed; i++)
//         {
//             std::this_thread::sleep_for(std::chrono::seconds(3));
//             simulation_interface.print(":"+get_hour(i)+": The store is closed");
//         }
//     }
// }
