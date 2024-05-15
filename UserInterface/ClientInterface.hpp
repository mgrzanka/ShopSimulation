#ifndef _CLIENT_INTERFACE_HPP_
#define _CLIENT_INTERFACE_HPP_
#include <iostream>


#include "../Structures.hpp"
#include "UserInterface.hpp"


class ClientInterface: public UserInterface
{
    virtual void print(std::string message_to_display) const override;
};


#endif