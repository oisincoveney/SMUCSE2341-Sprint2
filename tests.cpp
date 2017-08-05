#include "catch.hpp"

#include <cstring>
#include "dsstring.h"
#include "Vector.h"


TEST_CASE("String class", "[string]"){

    String s[10];
    s[0] = String("testString");
    s[1] = String("a test string");
    s[2] = String("");
    s[3] = String("THIS IS AN UPPERCASE STRING");
    s[4] = String("this is an uppercase string");
    s[5] = String("\n");
    s[6] = String("");
    s[7] = String("  split  split  split  ");
    s[8] = String("                          ");
    s[9] = String("testString");

    SECTION("Equality operators"){
        REQUIRE(s[0] == String("testString"));
        REQUIRE(s[0] == s[9]);
        REQUIRE(s[2] == "");
        REQUIRE(s[1] == "a test string");
        REQUIRE(!(s[3] == s[4]));
    }

    SECTION("Assignment operators"){
        String str;
        str = "a test string";
        REQUIRE(str == s[1]);
        str = String("testString");
        REQUIRE(str == s[0]);
        str = "";
        REQUIRE(str == s[6]);
        str = String("\n");
        REQUIRE(str == s[5]);
    }

    SECTION("Addition operator"){
        REQUIRE(String("testStringtestString") == s[0]+s[9]);
        REQUIRE(s[6] + s[6] == "");
        REQUIRE(s[5] + s[6] == String("\n"));
        REQUIRE(s[0] + s[1] + s[2] == "testStringa test string");
    }

    SECTION("Greater than operator"){
        REQUIRE(s[0] > s[1]);
        REQUIRE(s[4] > s[3]);
        REQUIRE(s[9] > s[6]);
        REQUIRE(s[7] > s[6]);
    }

    SECTION("[] Operator"){
        REQUIRE(s[0][1] == 'e');
        REQUIRE(s[9][-1] == 'g');
        REQUIRE(s[3][-3] == 'I');
        REQUIRE(s[4][4] == ' ');
        REQUIRE(s[6][0] == 0);
    }

    SECTION("Size function"){
        REQUIRE(s[9].size() == 10);
        REQUIRE(s[2].size() == 0);
        REQUIRE(s[8].size() == 26);
        REQUIRE(s[3].size() == 27);
    }

    SECTION("Substring function"){
        REQUIRE(s[0].substring(0, 5) == "testS");
        REQUIRE(s[1].substring(-6, -1) == "tring");
        REQUIRE(s[9].substring(0, -3) == "testStri");
        REQUIRE(s[9].substring(0, -1) == s[9]);
        REQUIRE(s[4].substring(0, 4) == "this");
    }

    SECTION("c_str function"){
        REQUIRE(strcmp(s[0].c_str(), "testString") == 0);
        REQUIRE(strcmp(s[9].c_str(), s[0].c_str()) == 0);
        REQUIRE(strcmp(s[2].c_str(), "") == 0);
    }

}

TEST_CASE("Vector class", "[Vector]")
{
    Vector<int> list{};
    for(int i{}; i < 30; i++)
        list.pushBack(i);

    SECTION("Accessor Functions")
    {
        REQUIRE(list[0] == 0);
        REQUIRE(list.at(3) == 3);
        REQUIRE(list.front() == list[0]);
        REQUIRE(list.back() == list[29]);
    }

    SECTION("Adding functions")
    {
        for(int i{30}; i < 60; i++)
            list.pushBack(i);
        for(int i{}; i < 60; i++)
        {
            list.insert(0, 1);
        }
        for(int i{}; i < 60; i++)
        {
            REQUIRE(list[i] == 1);
        }
        for(int i{}; i < list.size(); i++)
        {
            list.assign(i, i+200);
        }
        for(int i{}; i < list.size(); i++)
        {
            REQUIRE(list[i] == 200 + i);
        }

    }

    SECTION("Removal Functions")
    {
        int n = list.size();
        for(int i = 0; i < n; i++)
        {
            list.popBack();
        }
        REQUIRE(list.empty() == true);

        for(int i{}; i < 100; i++)
            list.pushBack(i);

        for(int i{}; i < 100; i++)
        {
            list.remove(rand() % list.size());
        }
        REQUIRE(list.empty() == true);
    }

    SECTION("Size Functions")
    {
        REQUIRE(list.empty() == false);
        REQUIRE(list.size() == 30);
        list.clear();
        REQUIRE(list.size() == 0);
        REQUIRE(list.empty() == true);
    }

    SECTION("Constructor test")
    {
        Vector<int> test(list);
        for(int i{}; i < test.size(); i++)
        {
            REQUIRE(list.at(i) == test[i]);
        }
    }

    SECTION("Assignment Operator Test")
    {
        Vector<int> test{};
        for(int i{30}; i < 60; i++)
            test.pushBack(i);
        list = test;
        REQUIRE(list[0] == 30);
        REQUIRE(list[15] == 45);
        REQUIRE(list[list.size()-1] == 59);
    }

    SECTION("insertion sort functions")
    {
        list.insertionSortHigh();
        for(int i{29}; i >= 0; i--)
        {
            REQUIRE(list[i] == 29 - i);
        }

        list.insertionSortLow();
        for(int i{0}; i < 30; i++)
            REQUIRE(list[i] == i);

    }

}
