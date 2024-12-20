#ifndef _MENAGERS_FRIEND_HPP_
#define _MENAGERS_FRIEND_HPP_


#include "Client.hpp"


class MenagersFriend: public Client
{
    void interaction_while_paying(std::string employee_name) const override;
    public:
        MenagersFriend(std::string name, std::string vorname, Money money);
        MenagersFriend();
        void start_message() const override;
        void end_message() const override;
        void add_money() override;
};

#endif
