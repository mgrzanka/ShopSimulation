#include "catch_amalgamated.hpp"
#include "../Client/Client.hpp"
#include "../Client/MenagersFriend.hpp"
#include "../Client/RegularClient.hpp"
#include "../Client/Tourist.hpp"
#include <stdexcept>


TEST_CASE("test_basics")
{
    MenagersFriend menagers_friend("Marian", "Piernik", Money(11200), StoreTime(5));
    Tourist tourist("Andrew", "Stone", Money(1234), StoreTime(30));
    RegularClient regular("Pan", "Spod czworki", Money(123), StoreTime(10));

    REQUIRE(menagers_friend.get_name() == "Marian Piernik");
    REQUIRE(menagers_friend.get_money().full_price == 11200);
    REQUIRE(menagers_friend.get_storetime().minutes == 5);

    REQUIRE(tourist.get_name() == "Andrew Stone");
    REQUIRE(tourist.get_money().full_price == 1234);
    REQUIRE(tourist.get_storetime().minutes == 30);

    REQUIRE(regular.get_name() == "Pan Spod czworki");
    REQUIRE(regular.get_money().full_price == 123);
    REQUIRE(regular.get_storetime().minutes == 10);

    REQUIRE_THROWS_AS(MenagersFriend("", "", Money(1), StoreTime(2)), std::invalid_argument);
    REQUIRE_THROWS_AS(MenagersFriend("dasdasd", "asdad", Money(1), StoreTime(0)), std::invalid_argument);
}

TEST_CASE("wirtual methods")
{
    MenagersFriend menagers_friend("Marian", "Piernik", Money(11200), StoreTime(5));
    Tourist tourist("Andrew", "Stone", Money(1234), StoreTime(30));
    RegularClient regular("Pan", "Spod czworki", Money(123), StoreTime(10));

    menagers_friend.add_money(100);
    tourist.add_money(100);
    regular.add_money(100);

    REQUIRE(menagers_friend.get_money().full_price == 11300);
    REQUIRE(tourist.get_money().full_price == 1334);
    REQUIRE(regular.get_money().full_price == 223);

    menagers_friend.take_money(100);
    tourist.take_money(100);
    regular.take_money(100);

    REQUIRE(menagers_friend.get_money().full_price == 11200);
    REQUIRE(tourist.get_money().full_price == 1234);
    REQUIRE(regular.get_money().full_price == 123);

    REQUIRE_THROWS_AS(regular.take_money(1000), std::invalid_argument);

    regular.start_message();
    regular.end_message();
    Money money(13);
    regular.buy_somethig("Amadeusz", "Woda", money);

}
