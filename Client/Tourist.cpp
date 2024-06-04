#include "Tourist.hpp"
#include "Client.hpp"


Tourist::Tourist(std::string name, std::string vorname, Money money):
Client(name, vorname, money) {}

Tourist::Tourist(): Client("tourist_name", "toursit_vorname", Money(1000000)) {}

void Tourist::interaction_while_paying(std::string employee_name) const
{
    client_interface.print(this->get_name() + ": Thank you!\n");
}

void Tourist::start_message() const
{
    client_interface.print("Tourist " + this->get_name() + " is going into the store\n");
}

void Tourist::end_message() const
{
    client_interface.print("Tourist " + this->get_name() + " is going out of the store\n");
}

void Tourist::add_money()
{
    money.full_price += 500000;
}
