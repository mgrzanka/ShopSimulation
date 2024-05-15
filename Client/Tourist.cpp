#include "Tourist.hpp"
#include "Client.hpp"


Tourist::Tourist(std::string name, std::string vorname, Money money, StoreTime time_spent):
Client(name, vorname, money, time_spent) {}

Tourist::Tourist(): Client("tourist_name", "toursit_vorname", Money(1000000), StoreTime(30)) {}

void Tourist::interaction_while_paying(std::string employee_name) const
{
    client_interface->print(this->get_name() + ": Thank you!");
}

void Tourist::start_message() const
{
    client_interface->print("Tourist " + this->get_name() + "is going into the store");
}

void Tourist::end_message() const
{
    client_interface->print("Tourist " + this->get_name() + "is going out of the store");
}
