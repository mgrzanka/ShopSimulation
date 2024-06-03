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
    std::unique_ptr<Cashier> cashier;
    std::unique_ptr<Client> client;
    std::vector<std::unique_ptr<Product>> products;
    public:
        ClientBuysEvent(Store& store, unsigned int client_index, unsigned int employee_index,
                        std::vector<std::unique_ptr<Product>>& products);

        virtual void start_message() const override;
        virtual void end_message() const override;
        virtual void perform_action() override;
        virtual void return_elements() override;
};


#endif