#include "FileHandler.hpp"
#include "../Product/Breadstuff.hpp"
#include "../Product/Beverage.hpp"
#include "../Product/Cosmetics.hpp"
#include "../Product/Dairy_product.hpp"
#include "../Product/Fruit_vegetable.hpp"
#include "../Product/Industrial_article.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

FileHandler::FileHandler(std::string path):
path(path)
{}

std::vector<std::tuple<std::string, std::string>> FileHandler::load_names()
{
    {
    file.open(path);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
    }
    std::vector<std::tuple<std::string, std::string>> names;

    std::string line;
    while (std::getline(file, line)) {
        line.erase(line.find_last_not_of(" \n\r\t")+1);
        std::stringstream lineStream(line);
        std::string name;
        std::string surname;

        if (std::getline(lineStream, name, ' ') && std::getline(lineStream, surname)) {
            names.emplace_back(name, surname);
        }
    }

    file.close();
    return names;
}
}


std::vector<std::unique_ptr<Product>> FileHandler::load_products()
{
   std::vector<std::unique_ptr<Product>> products;
    std::string line;

    file.open(path);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
    }


    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string product_type, name, str_price, additional_attribute;

        iss >> product_type >> name >> str_price >> additional_attribute;
        int int_price = std::stoi(str_price);
        Money price = Money(int_price);

        if (product_type == "fruit_vegetable") {
            int amount_in_pack = std::stoi(additional_attribute);
            products.push_back(std::make_unique<FruitVegetable>(name, price, amount_in_pack));

        } else if (product_type == "beverage") {
            products.push_back(std::make_unique<Beverage>(name, price));

        } else if (product_type == "breadstuff") {
            int glycemic_index = std::stoi(additional_attribute);
            products.push_back(std::make_unique<Breadstuff>(name, price, glycemic_index));

        } else if (product_type == "cosmetics") {
            char type = additional_attribute[0];
            products.push_back(std::make_unique<Cosmetics>(name, price, type));
        }
        else if (product_type == "dairy_product") {
            double protein_content = std::stoi(additional_attribute);
            products.push_back(std::make_unique<DairyProduct>(name, price, protein_content));

        } else if (product_type == "industrial_article") {
            products.push_back(std::make_unique<IndustrialArticle>(name, price));
        }
        else {
            std::cerr << "Unknown product type: " << product_type << "\n";
        }
    }

    return products;

}