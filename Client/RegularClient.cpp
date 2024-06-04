#include "RegularClient.hpp"


RegularClient::RegularClient(std::string name, std::string vorname, Money money):
Client(name, vorname, money) {}

RegularClient::RegularClient(): Client("regular_client__name", "regular_client_vorname", Money(100000)) {}

void RegularClient::interaction_while_paying(std::string employee_name) const
{
    client_interface.print(this->get_name() + ": Thank you, " + employee_name + ",that's all I want for today. Have a nice day!\n");
}

void RegularClient::start_message() const
{
    client_interface.print("Regular client " + this->get_name() + " is going into the store\n");
}

void RegularClient::end_message() const
{
    client_interface.print("Regular client " + this->get_name() + " is going out of the store\n");
}

void RegularClient::add_money()
{
    money.full_price += 20000;
}