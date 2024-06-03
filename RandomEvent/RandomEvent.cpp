#include "RandomEvent.hpp"
#include <memory>


RandomEvent::RandomEvent(Store& store): store {store} {} // domyślnie counter na 1 iteracja

void RandomEvent::start_message() const {}

void RandomEvent::end_message() const {}
