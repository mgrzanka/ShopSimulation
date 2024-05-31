#include "catch_amalgamated.hpp"
#include "../Product/Product.hpp"
#include "../Product/Breadstuff.hpp"
#include "../Product/Dairy_product.hpp"
#include "../Product/Fruit_vegetables.hpp"
#include "../Product/Cosmetics.hpp"
#include "../Product/Beverage.hpp"
#include "../Product/Industrial_article.hpp"
#include <sstream>

TEST_CASE("Industrial article tests") {
    IndustrialArticle prod("Product", Money(1050));
    REQUIRE(prod.get_name() == "Product");
    REQUIRE(prod.get_price_netto().full_price == 1050);
    prod.set_name("New Product");
    REQUIRE(prod.get_name() == "New Product");
    REQUIRE_THROWS_AS(prod.set_name(""), std::invalid_argument);
    prod.set_price_netto(Money(1575));
    REQUIRE(prod.get_price_netto().full_price == 1575);
    REQUIRE_THROWS_AS(prod.set_price_netto(0), std::invalid_argument);
    REQUIRE_THROWS_AS(prod.set_price_netto(-590), std::invalid_argument);
}


TEST_CASE("Cosmetics tests") {
    Cosmetics cosmetics("Lipstick", Money(1000), 'F');
    REQUIRE(cosmetics.get_name() == "Lipstick");
    REQUIRE(cosmetics.get_price_netto().full_price == 1000);
    REQUIRE(cosmetics.calculate_price().full_price == 1030);
    REQUIRE(cosmetics.find_shelf() == 578);
    cosmetics.set_name("Red lipstick");
    REQUIRE(cosmetics.get_name() == "Red lipstick");
    cosmetics.set_price_netto(Money(1200));
    REQUIRE(cosmetics.get_price_netto().full_price == 1200);
    Cosmetics male_cosmetics("Aftershave", Money(1500), 'M');
    REQUIRE(male_cosmetics.find_shelf() == 579);
    Cosmetics other_cosmetics("Nail polish", Money(800), 'O');
    REQUIRE(other_cosmetics.find_shelf() == 580);
    REQUIRE_THROWS_AS(cosmetics.set_name(""), std::invalid_argument);
    REQUIRE_THROWS_AS(cosmetics.set_price_netto(0), std::invalid_argument);
    REQUIRE_THROWS_AS(cosmetics.set_price_netto(-590), std::invalid_argument);
}

TEST_CASE("Breadstuff tests") {
    Breadstuff breadstuff("Whole wheat bread", Money(350), 50);
    REQUIRE(breadstuff.get_name() == "Whole wheat bread");
    REQUIRE(breadstuff.get_price_netto().full_price == 350);
    REQUIRE(breadstuff.calculate_price().full_price == 368);
    breadstuff.set_name("Bread roll");
    REQUIRE(breadstuff.get_name() == "Bread roll");
    breadstuff.set_price_netto(400);
    REQUIRE(breadstuff.get_price_netto().fyll_price == 400);
    REQUIRE(breadstuff.find_shelf() == 110);
    REQUIRE(breadstuff.calculate_price().full_price == 420);
    REQUIRE_THROWS_AS(breadstuff.set_name(""), std::invalid_argument);
    REQUIRE_THROWS_AS(breadstuff.set_price_netto(0), std::invalid_argument);
    REQUIRE_THROWS_AS(breadstuff.set_price_netto(-590), std::invalid_argument);
}

TEST_CASE("DairyProduct tests") {
    DairyProduct dairy_product("Low-fat milk", Money(220), 3.5);
    REQUIRE(dairy_product.get_name() == "Low-fat milk");
    REQUIRE(dairy_product.get_price_netto().full_price == 220);
    REQUIRE(dairy_product.find_shelf() == 235);
    REQUIRE(dairy_product.calculate_price().full_price == 231);
    REQUIRE_THROWS_AS(dairy_product.set_name(""), std::invalid_argument);
    REQUIRE_THROWS_AS(dairy_product.set_price_netto(0), std::invalid_argument);
    REQUIRE_THROWS_AS(dairy_product.set_price_netto(-590), std::invalid_argument);
    dairy_product.set_name("milk");
    REQUIRE(dairy_product.get_name() == "milk");
    dairy_product.set_price_netto(203);
    REQUIRE(dairy_product.get_price_netto().full_price == 203);
}

TEST_CASE("FruitVegetable tests") {
    FruitVegetable fruit_vegetable("Apple", Money(150), 6);
    REQUIRE(fruit_vegetable.get_name() == "Apple");
    REQUIRE(fruit_vegetable.get_price_netto().full_price == 150);
    REQUIRE(fruit_vegetable.find_shelf() == 450);
    REQUIRE(fruit_vegetable.calculate_price().full_price == 150);
    REQUIRE_THROWS_AS(fruit_vegetable.set_name(""), std::invalid_argument);
    REQUIRE_THROWS_AS(fruit_vegetable.set_price_netto(0), std::invalid_argument);
    REQUIRE_THROWS_AS(fruit_vegetable.set_price_netto(-590), std::invalid_argument);
    fruit_vegetable.set_name("pear");
    REQUIRE(fruit_vegetable.get_name() == "pear");
    fruit_vegetable.set_price_netto(203);
    REQUIRE(fruit_vegetable.get_price_netto().full_price == 203);
}

TEST_CASE("Beverage tests") {
    Beverage beverage("Cola", Money(250));
    REQUIRE(beverage.get_name() == "Cola");
    REQUIRE(beverage.get_price_netto().full_price == 250);
    Beverage beverage_long_name("Orange Juice", Money(250));
    REQUIRE(beverage.find_shelf() == 439);
    REQUIRE(beverage_long_name.find_shelf() == 440);
    REQUIRE(beverage.calculate_price().full_price == 308);
    REQUIRE_THROWS_AS(beverage.set_name(""), std::invalid_argument);
    REQUIRE_THROWS_AS(beverage.set_price_netto(0), std::invalid_argument);
    REQUIRE_THROWS_AS(beverage.set_price_netto(-590), std::invalid_argument);
    beverage.set_name("Water");
    REQUIRE(beverage.get_name() == "Water");
    beverage.set_price_netto(203);
    REQUIRE(beverage.get_price_netto().full_price == 203);
}
