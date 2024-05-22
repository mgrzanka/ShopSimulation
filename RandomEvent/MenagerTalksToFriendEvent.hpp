#ifndef _MENAGER_TALKS_
#define _MENAGER_TALKS_


#include "RandomEvent.hpp"
#include "../Client/MenagersFriend.hpp"
#include "../Employee/Menager.hpp"


class MenagerTalksToFriendEvent: public RandomEvent
{
    std::unique_ptr<MenagersFriend> menagers_friend;
    std::unique_ptr<Menager> menager;
};


#endif