#ifndef _TOURIST_HPP_
#define _TOURIST_HPP_


#include "Client.hpp"


class Tourist: public Client
{
    void interaction_while_paying(std::string employee_name) const override;
    public:
        Tourist(std::string name, std::string vorname, Money money);
        Tourist();
        void start_message() const override;
        void end_message() const override;
};

#endif