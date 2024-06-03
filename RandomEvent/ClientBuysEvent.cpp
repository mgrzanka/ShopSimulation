#include "ClientBuysEvent.hpp"
#include "RandomEvent.hpp"
#include "../Receipt/Receipt.hpp"
#include <algorithm>
#include <memory>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>



ClientBuysEvent::ClientBuysEvent(Store& store, unsigned int client_index, unsigned int employee_index,
std::vector<std::unique_ptr<Product>>& products): RandomEvent(store)
{
    Cashier* cashier = dynamic_cast<Cashier*>(store.on_shift_employees[employee_index].get());
    if(cashier)
    {
        this->cashier = std::make_unique<Cashier>(*cashier);
    }
    else throw std::invalid_argument("Something went wrong in event generator - this employee is not a cashier!");

    this->client = std::move(store.taken_clients[client_index]);
    store.taken_clients.erase(std::remove(store.taken_clients.begin(), store.taken_clients.end(),
    nullptr), store.taken_clients.end());

    for(auto& product : products) this->products.push_back(std::move(product));
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
    Money total_price, price_without_tax;
    std::vector<std::string> names;
    std::vector<Money> prices;
    for(const auto& product : products)
    {
        price_without_tax += product->get_price_netto();
        total_price += product->calculate_price();
        names.push_back(product->get_name());
        prices.push_back(product->calculate_price());
    }
    cashier->serve_the_client();
    client->buy_somethig(cashier->get_name(), names, Money(total_price));
    store.add_money(total_price);
    // get recepit
    Receipt receipt(total_price, price_without_tax, names, prices);
    receipt.print_receipt();
}

void ClientBuysEvent::return_elements()
{
    store.available_clients.push_back(std::move(client));
}
