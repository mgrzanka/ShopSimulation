#include "RandomEvent.hpp"


RandomEvent::RandomEvent(Store& store, float probability): store {store}, counter {1}, probability{probability} {} // domyślnie counter na 1 iteracja


unsigned int RandomEvent::get_counter()
{
    return counter;
}

void RandomEvent::decrease_counter()
{
    counter -= 1;
}

float RandomEvent::get_probability()
{
    return probability;
}

bool RandomEvent::check_action() const
{
    return counter == 0;
}

void RandomEvent::start_message() const {}

void RandomEvent::end_message() const {}
