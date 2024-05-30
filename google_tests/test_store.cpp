#include "gtest/gtest.h"
#include <algorithm>
#include <memory>
#include <vector>
#include "../Store/Store.hpp"
#include "../Client/Client.hpp"
#include "../Client/RegularClient.hpp"
#include "../RandomEvent/CleanerCleansEvent.hpp"



TEST(Store, Store)
{
    Store store;
    std::unique_ptr<Client> client1 = std::make_unique<RegularClient>("M", "G", Money(100000000), StoreTime(5));
    std::unique_ptr<Client> client2 = std::make_unique<RegularClient>("I", "G", Money(1000), StoreTime(35));
    std::vector<std::unique_ptr<Client>> vec; vec.push_back(std::move(client1)); vec.push_back(std::move(client2));

    store.add_clients(vec);
    auto& products = store.get_products();
}
