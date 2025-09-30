#define CATCH_CONFIG_MAIN
#include "../libs/catch_amalgamated.hpp"
#include <string.h>
#include "../ArrayADTList.h"

// Tests for base methods of ArrayADTList

TEST_CASE("Should create an ArrayADTList") {
    ArrayADTList<int> list;
}

TEST_CASE("Copy Constructor should make an independent list") {
    ArrayADTList<int> list;
    list.putItem(1);
    list.putItem(2);
    list.putItem(3);
    list.putItem(4);
    ArrayADTList<int> list2 = list;
    int found;
    REQUIRE(list2.getItem(3, found));
    list.deleteItem(3);
    REQUIRE_FALSE(list.getItem(3, found));
    REQUIRE(list2.getItem(3, found));
}

TEST_CASE("Assignment operator should make an independent list") {
    ArrayADTList<int> list;
    list.putItem(1);
    list.putItem(2);
    list.putItem(3);
    list.putItem(4);
    ArrayADTList<int> list2;
    list2 = list;
    int found;
    REQUIRE(list2.getItem(3, found));
    list.deleteItem(3);
    REQUIRE_FALSE(list.getItem(3, found));
    REQUIRE(list2.getItem(3, found));
}

TEST_CASE("Assignment operator should overwrite values in the lhs list") {
    ArrayADTList<int> list;
    list.putItem(1);
    list.putItem(2);
    list.putItem(3);
    list.putItem(4);
    ArrayADTList<int> list2;
    list2.putItem(7);
    list2 = list;
    int found;
    REQUIRE_FALSE(list2.getItem(7, found));
}

TEST_CASE("New List should be empty") {
    ArrayADTList<int> list;
    REQUIRE(list.getLength() == 0);
}

TEST_CASE("Length should be 1 after adding an item") {
    ArrayADTList<int> list;
    list.putItem(4);
    REQUIRE(list.getLength() == 1);
}

TEST_CASE("Length should be 3 after adding 3 items") {
    ArrayADTList<int> list;
    list.putItem(4);
    list.putItem(5);
    list.putItem(6);
    REQUIRE(list.getLength() == 3);
}

TEST_CASE("Should not be full to start") {
    ArrayADTList<int> list;
    REQUIRE_FALSE(list.isFull());
}

TEST_CASE("MakeEmpty should make the list empty") {
    ArrayADTList<int> list;
    list.putItem(4);
    list.putItem(5);
    list.putItem(6);
    list.makeEmpty();
    REQUIRE(list.getLength() == 0);
}

TEST_CASE("Should throw an error with a message of 'List is Full.'") {
    ArrayADTList<int> list;
    for (int i = 0; i < 100; ++i) {
        list.putItem(i);
    }

    try {
        list.putItem(101);
        REQUIRE_FALSE(false);
    } catch (std::out_of_range& error) {
        REQUIRE(strcmp(error.what(), "List is full.") == 0);
    }
}

TEST_CASE("Should be able to get an item after adding it") {
    ArrayADTList<int> list;
    list.putItem(7);
    int item;
    REQUIRE(list.getItem(7, item));
    REQUIRE(item == 7);
}

TEST_CASE("Delete should return false when the item is not in the list") {
    ArrayADTList<int> list;
    list.putItem(4);
    list.putItem(5);
    list.putItem(6);
    REQUIRE_FALSE(list.deleteItem(1));
}

TEST_CASE("Should not be able to get an item after deleting it") {
    ArrayADTList<int> list;
    list.putItem(4);
    list.putItem(5);
    list.putItem(6);
    REQUIRE(list.deleteItem(5));
    REQUIRE(list.getLength() == 2);
    int item;
    REQUIRE_FALSE(list.getItem(5, item));
}

TEST_CASE("Should receive false when getting an item from an empty list") {
    ArrayADTList<int> list;
    int item;
    REQUIRE_FALSE(list.getItem(9, item));
}

TEST_CASE("Should be able to get other items after an item has been deleted") {
    ArrayADTList<int> list;
    list.putItem(4);
    list.putItem(5);
    list.putItem(6);
    REQUIRE(list.deleteItem(5));
    REQUIRE(list.getLength() == 2);
    int item;
    REQUIRE(list.getItem(4, item));
    REQUIRE(list.getItem(6, item));
}


TEST_CASE("getItem should retrieve the first matching item if duplicates exist") {
    ArrayADTList<int> list;
    list.putItem(10);
    list.putItem(20);
    list.putItem(10); // Duplicate item
    int foundItem;
    REQUIRE(list.getItem(10, foundItem));
    REQUIRE(foundItem == 10);
}

TEST_CASE("makeEmpty should clear a non-empty list") {
    ArrayADTList<int> list;
    list.putItem(10);
    list.putItem(20);
    list.putItem(30);
    REQUIRE(list.getLength() == 3);
    list.makeEmpty();
    REQUIRE(list.getLength() == 0);
}

TEST_CASE("getItem should return false on an empty list") {
    ArrayADTList<int> list;
    int foundItem;
    REQUIRE_FALSE(list.getItem(10, foundItem)); // No items in the list
}
