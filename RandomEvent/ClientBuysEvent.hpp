#ifndef _CLIENT_BUYS_EVENT_HPP_
#define _CLIENT_BUYS_EVENT_HPP_

#include "RandomEvent.hpp"
#include "../Client/Client.hpp"
#include "../Product/Product.hpp"
#include "../Employee/cashier.hpp"
#include <memory>
#include <vector>


class ClientBuysEvent: public RandomEvent
{
    std::unique_ptr<Client> client;
    std::unique_ptr<Cashier> employee;
    std::vector<std::unique_ptr<Product>> products;
    public:
        ClientBuysEvent(Store& store, float probability, std::unique_ptr<Client>& client, std::unique_ptr<Cashier>& employee,
                        std::vector<std::unique_ptr<Product>>& products);

        virtual void start_message() const override;
        virtual void end_message() const override;
        virtual void perform_action() override;
        virtual void restore() override;
};


#endif