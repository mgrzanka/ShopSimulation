#ifndef _USER_INTERFACE_HPP_
#define _USER_INTERFACE_HPP_
#include <iostream>


#include "../Structures.hpp"


class UserInterface
{
    virtual void print(std::string message_to_display) const = 0;
};


#endif