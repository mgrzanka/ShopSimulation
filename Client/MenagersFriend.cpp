#include "MenagersFriend.hpp"


MenagersFriend::MenagersFriend(std::string name, std::string vorname, Money money):
Client(name, vorname, money) {}

MenagersFriend::MenagersFriend(): Client("menagers_friend_name", "menagers_friend_vorname", Money(10000)) {}

void MenagersFriend::interaction_while_paying(std::string employee_name) const
{
    client_interface.print(this->get_name() + ": Hurry up, " + employee_name + ", I don't have a whole day. Do you want me to speak to our beloved Mr. Menager?\n");
}

void MenagersFriend::start_message() const
{
    client_interface.print("Menager's friend " + this->get_name() + " is going into the store\n");
}

void MenagersFriend::end_message() const
{
    client_interface.print("Menager's friend " + this->get_name() + " is going out of the store\n");
}

void MenagersFriend::add_money()
{
    money.full_price += 100000;
}