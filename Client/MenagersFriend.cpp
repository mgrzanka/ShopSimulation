#include "MenagersFriend.hpp"


MenagersFriend::MenagersFriend(std::string name, std::string vorname, Money money, StoreTime time_spent):
Client(name, vorname, money, time_spent) {}

MenagersFriend::MenagersFriend(): Client("menagers_friend_name", "menagers_friend_vorname", Money(10000), StoreTime(5)) {}

void MenagersFriend::interaction_while_paying(std::string employee_name) const
{
    client_interface->print(this->get_name() + ": Hurry up, " + employee_name + ", I don't have a whole day. Do you want me to speak to our beloved Mr. Menager?");
}

void MenagersFriend::start_message() const
{
    client_interface->print("Menager's friend " + this->get_name() + "is going into the store");
}

void MenagersFriend::end_message() const
{
    client_interface->print("Menager's friend " + this->get_name() + "is going out of the store");
}
