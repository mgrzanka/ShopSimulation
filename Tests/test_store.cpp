#include "catch_amalgamated.hpp"
#include "../Store/Store.hpp"
#include <stdexcept>


TEST_CASE("inicial")
{
    Store store;
    auto clients = store.get_clients();
}