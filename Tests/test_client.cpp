#include "catch_amalgamated.hpp"
#include "../Client/Client.hpp"
#include "../Client/MenagersFriend.hpp"
#include "../Client/RegularClient.hpp"
#include "../Client/Tourist.hpp"
#include <stdexcept>


TEST_CASE("test_basics")
{
    MenagersFriend menagers_friend("Marian", "Piernik", Money(11200));
    Tourist tourist("Andrew", "Stone", Money(1234));
    RegularClient regular("Pan", "Spod czworki", Money(123));

    REQUIRE(menagers_friend.get_name() == "Marian Piernik");
    REQUIRE(menagers_friend.get_money().full_price == 11200);

    REQUIRE(tourist.get_name() == "Andrew Stone");
    REQUIRE(tourist.get_money().full_price == 1234);

    REQUIRE(regular.get_name() == "Pan Spod czworki");
    REQUIRE(regular.get_money().full_price == 123);

    REQUIRE_THROWS_AS(MenagersFriend("", "djdhjwdh", Money(1)), std::invalid_argument);
    REQUIRE_THROWS_AS(MenagersFriend("dasdasd", "", Money(1)), std::invalid_argument);
}

TEST_CASE("wirtual methods")
{
    MenagersFriend menagers_friend("Marian", "Piernik", Money(11200));
    Tourist tourist("Andrew", "Stone", Money(1234));
    RegularClient regular("Pan", "Spod czworki", Money(123));

    menagers_friend.add_money();
    tourist.add_money();
    regular.add_money();

    REQUIRE(menagers_friend.get_money().full_price == 111200);
    REQUIRE(tourist.get_money().full_price == 501234);
    REQUIRE(regular.get_money().full_price == 20123);

    menagers_friend.take_money(100);
    tourist.take_money(100);
    regular.take_money(100);

    REQUIRE(menagers_friend.get_money().full_price == 111100);
    REQUIRE(tourist.get_money().full_price == 501134);
    REQUIRE(regular.get_money().full_price == 20023);

    REQUIRE_THROWS_AS(regular.take_money(1000000), std::invalid_argument);

    REQUIRE_NOTHROW(regular.start_message());
    REQUIRE_NOTHROW(regular.end_message());
    Money money(13);
    REQUIRE_NOTHROW(regular.buy_somethig("Amadeusz", {"Woda"}, money));

}
