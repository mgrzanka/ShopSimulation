#include "ClientBuysEvent.hpp"
#include "RandomEvent.hpp"
#include <algorithm>
#include <memory>
#include <numeric>
#include <type_traits>
#include <vector>



ClientBuysEvent::ClientBuysEvent(Store& store, float probability, std::unique_ptr<Client> client,
                                std::unique_ptr<Cashier> employee,
                                std::vector<std::unique_ptr<Product>> products): RandomEvent(store, probability)
{
    this->client = std::move(client);
    this->employee = std::move(employee);
    std::for_each(products.begin(), products.end(),
                    [&](const auto& p){this->products.push_back(std::move(p));});
    this->counter = client->get_storetime().get_iterations();
}

void ClientBuysEvent::start_message() const
{
    client->start_message();
    employee->start_message();
}

void ClientBuysEvent::end_message() const
{
    client->end_message();
    employee->start_message();
}

void ClientBuysEvent::perform_action()
{

    int total_price = std::accumulate(products.begin(), products.end(), 0,
                            [](int price, const auto& p) {return price + p->get_price().full_price;});
    std::vector<std::string> names;
    std::for_each(products.begin(), products.end(), [&](const auto& p){names.push_back(p->get_name());});
    client->buy_somethig(employee->get_name(), names, Money(total_price));
    employee->serve_the_client();
    store.add_money(total_price);
}

void ClientBuysEvent::restore()
{
    std::vector<std::unique_ptr<Client>> c = {std::move(client)};
    std::vector<std::unique_ptr<Cashier>> e = {std::move(employee)};
    store.add_clients(c);
    store.add_employees(e);
    store.add_products(products);
}
