#include "ClientBuysEvent.hpp"
#include "RandomEvent.hpp"
#include <algorithm>
#include <memory>
#include <numeric>
#include <type_traits>



ClientBuysEvent::ClientBuysEvent(Store& store, std::unique_ptr<Client> client,
                                std::unique_ptr<Employee> employee,
                                std::vector<std::unique_ptr<Product>> products): RandomEvent(store)
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
}

void ClientBuysEvent::end_message() const
{
    client->end_message();
}

void ClientBuysEvent::perform_action()
{
    client->buy_something(employee->get_name());
    int total_price = std::accumulate(products.begin(), products.end(),
                            [](int price, const auto& p) {return price + p->get_price();});
    client->take_money(total_price);
    store.add_money(total_price);
}

void ClientBuysEvent::restore()
{
    std::vector<std::unique_ptr<Client>> c = {std::move(client)};
    std::vector<std::unique_ptr<Employee>> e = {std::move(employee)};
    store.add_clients(c);
    store.add_employees(e);
    store.add_products(products);
}
