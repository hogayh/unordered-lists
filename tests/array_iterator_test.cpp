#include "../libs/catch_amalgamated.hpp"
#include "../ArrayADTList.h"
#include <set>

// Tests for Iterator functionality of ArrayADTList

TEST_CASE("Should be able to iterate over all the list items using iterators") {
    ArrayADTList<int> list;
    std::set<int> seenItems;
    for (int i = 0; i < 10; ++i) {
        list.putItem(i);
    }

    for (ArrayADTList<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        seenItems.insert(*it);
    }

    REQUIRE(seenItems.size() == 10);
    for (int i = 0; i < 10; ++i) {
        REQUIRE(seenItems.count(i) == 1);
    }
}

TEST_CASE("Dereferencing an iterator at the end should throw an exception") {
    ArrayADTList<int> list;
    for (int i = 0; i < 5; ++i) {
        list.putItem(i);
    }

    ArrayADTList<int>::Iterator it = list.end();
    REQUIRE_THROWS_AS(*it, std::out_of_range);
}

TEST_CASE("begin() should return an iterator to the first element of the list") {
    ArrayADTList<int> list;
    list.putItem(10);
    list.putItem(20);
    list.putItem(30);
    ArrayADTList<int>::Iterator it = list.begin();
    REQUIRE(*it == 10);
}

TEST_CASE("end() should return an iterator beyond the last element of the list") {
    ArrayADTList<int> list;
    list.putItem(10);
    list.putItem(20);
    list.putItem(30);
    ArrayADTList<int>::Iterator it = list.end();
    REQUIRE_THROWS_AS(*it, std::out_of_range);
}

TEST_CASE("Iterator equality and inequality operators should work correctly") {
    ArrayADTList<int> list;
    list.putItem(10);
    list.putItem(20);
    list.putItem(30);

    ArrayADTList<int>::Iterator it1 = list.begin();
    ArrayADTList<int>::Iterator it2 = list.begin();
    ArrayADTList<int>::Iterator itEnd = list.end();

    REQUIRE(it1 == it2);  // Iterators to the same position should be equal
    ++it1;
    REQUIRE(it1 != it2);  // Iterators to different positions should not be equal
    REQUIRE(itEnd != it1);  // End iterator should not equal non-end iterators
}

TEST_CASE("Pre-increment operator should correctly traverse all elements") {
    ArrayADTList<int> list;
    list.putItem(10);
    list.putItem(20);
    list.putItem(30);

    std::set<int> seenValues;
    for (ArrayADTList<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        seenValues.insert(*it);
    }

    REQUIRE(seenValues.size() == 3);
    REQUIRE(seenValues.count(10) == 1);
    REQUIRE(seenValues.count(20) == 1);
    REQUIRE(seenValues.count(30) == 1);
}

TEST_CASE("Advancing iterator past the end should result in end iterator") {
    ArrayADTList<int> list;
    list.putItem(10);
    list.putItem(20);
    list.putItem(30);

    ArrayADTList<int>::Iterator it = list.begin();
    ++it;  // Now at second element
    ++it;  // Now at third element
    ++it;  // Now at end
    REQUIRE(it == list.end());
    REQUIRE_THROWS_AS(*it, std::out_of_range);  // Dereferencing should throw
}


TEST_CASE("Mixed operations: insertion, deletion, and iteration") {
    ArrayADTList<int> list;
    list.putItem(10);
    list.putItem(20);
    list.putItem(30);
    REQUIRE(list.getLength() == 3);

    list.deleteItem(20);
    REQUIRE(list.getLength() == 2);
    int found;
    REQUIRE_FALSE(list.getItem(20, found));

    std::set<int> seenValues;
    for (ArrayADTList<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        seenValues.insert(*it);
    }

    REQUIRE(seenValues.size() == 2);
    REQUIRE(seenValues.count(10) == 1);
    REQUIRE(seenValues.count(30) == 1);
}

TEST_CASE("Iterator should skip over a deleted item") {
    ArrayADTList<int> list;
    list.putItem(10);
    list.putItem(20);
    list.putItem(30);
    list.deleteItem(20);

    std::set<int> seenValues;
    for (ArrayADTList<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        seenValues.insert(*it);
    }

    REQUIRE(seenValues.size() == 2);
    REQUIRE(seenValues.count(10) == 1);
    REQUIRE(seenValues.count(30) == 1);
}
