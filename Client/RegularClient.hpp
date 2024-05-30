#ifndef _REGULAR_CLIENT_HPP_
#define _REGULAR_CLIENT_HPP_


#include "Client.hpp"


class RegularClient: public Client
{
    void interaction_while_paying(std::string employee_name) const override;
    public:
        RegularClient(std::string name, std::string vorname, Money money, StoreTime time_spent);
        RegularClient();
        void start_message() const override;
        void end_message() const override;
};

#endif