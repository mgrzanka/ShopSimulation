#include "Simulation.hpp"
#include <chrono>
#include <memory>
#include <string>
#include <random>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>


Day& operator++(Day& d) {
    d = static_cast<Day>((static_cast<int>(d) + 1) % 7);
    return d;
}

Simulation::Simulation(unsigned int days, unsigned int starting_hour, unsigned int ending_hour,
Store& store, std::vector<float> probabilities):
store{store}, simulation_interface{}
{
    this->number_of_days = days;
    this->ending_hour = ending_hour;
    this->starting_hour = starting_hour;
    this->probabilities = probabilities;

    this->iteration_counter = 0;
    this->day_counter = 0;
    this->day = Day::monday;
}

std::string Simulation::day_to_string(int day) const
{
    const std::string WeekDays[] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"};
    return WeekDays[day];
}

std::string Simulation::get_hour(unsigned int i) const
{
    StoreTime temp_time_obj(1);
    unsigned int minutes = temp_time_obj.get_minutes(i);

    unsigned int time_hours = (starting_hour + int(minutes/60)) % 24;
    unsigned int time_minutes = minutes % 60;

    return std::to_string(time_hours)+":"+std::to_string(time_minutes);
}

bool Simulation::if_new_event() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    return dis(gen) < 0.8;
}

void Simulation::run()
{
    EventGenerator generator(store, probabilities);
    std::unique_ptr<RandomEvent> event;
    std::unique_ptr<RandomEvent> previous_event;
    unsigned int daily_iterations = StoreTime(60*(ending_hour - starting_hour)).get_iterations();
    unsigned int closed_iterations = StoreTime(60*24).get_iterations() - daily_iterations;

    while(day_counter <= number_of_days)
    {
        //first employee shifts
        std::tuple<std::vector<int>,std::vector<int>> employees_tuple = store.check_employee_shift(int(day)+1, iteration_counter, starting_hour, ending_hour);
        simulation_interface.print("Day "+std::to_string(day_counter+1)+": " + day_to_string(int(day))+"\n");
        // DODAWANIE DOSTAWY

        while(iteration_counter <= daily_iterations)
        {
            std::string hour = get_hour(iteration_counter);
            simulation_interface.print(hour);
            simulation_interface.print("\n");
            Money store_money = store.get_money();
            simulation_interface.print("Store has "+std::to_string(store_money.get_whole_part())+"."+std::to_string(store_money.get_cents())+store_money.currency_name+"\n");
            std::this_thread::sleep_for(std::chrono::seconds(1));

            // displaying potential shift changes
            for(int index : std::get<0>(employees_tuple)) store.get_on_break_employees()[index]->start_message();
            for(int index : std::get<1>(employees_tuple)) store.get_on_shift_employees()[index]->end_message();
            store.update_employees_shift(employees_tuple);

            if(previous_event)
            {
                previous_event->perform_action();
                previous_event->end_message();
                previous_event->return_elements();
                if (ClientBuysEvent* clientBuysEvent = dynamic_cast<ClientBuysEvent*>(previous_event.get()))
                {
                    std::this_thread::sleep_for(std::chrono::seconds(4));
                }
            }
            // shift for the next iteration
            employees_tuple = store.check_employee_shift(int(day)+1, iteration_counter+1, starting_hour, ending_hour);
            std::vector<int> indexes = std::get<1>(employees_tuple);

            event = generator.draw_event(indexes);
            if(event)
            {
                event->start_message();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            previous_event = std::move(event);
            iteration_counter++;
            if(store.get_on_shift_employees().empty()) simulation_interface.print("No employees and avaible right now.\n");
            else if(store.get_products().empty()) simulation_interface.print("Out of products!\n");
        }

        for(int i=0; i<closed_iterations; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            simulation_interface.print(":"+get_hour(iteration_counter)+": The store is closed\n");
            iteration_counter++;
        }

        if(int(day) <= 7) ++day;
        else day = Day::monday;
        day_counter++;
        iteration_counter = 0;
    }
}
