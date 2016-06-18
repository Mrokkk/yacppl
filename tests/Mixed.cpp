//
// Created by maciek on 15.06.16.
//

#include <gtest/gtest.h>
#include <List.h>
#include <Pointer.h>
#include <Algorithm.h>
#include <String.h>


TEST(MixedTests, canCreateSharedPointerList)
{
    List<SharedPointer<int>> list;
    auto ptr1 = makeShared<int>(5);
    list.push_front(ptr1);
    list.push_front(SharedPointer<int>(new int(6)));
    auto it = list.begin();
    EXPECT_EQ(**it, 6);
    it++;
    EXPECT_EQ(**it, 5);
}

TEST(MixedTests, canCreateStringList)
{
    List<String> list{ "String 1", "String 2", "Third String", "4th String" };
    EXPECT_EQ(list.size(), 4);
    EXPECT_TRUE(list.front() == "String 1");
    EXPECT_TRUE(list.back() == "4th String");
    for (auto &s : list)
        s = "Example";
    EXPECT_TRUE(list.front() == "Example");
    EXPECT_TRUE(list.back() == "Example");
}

TEST(MixedTests, canUseForEachOnList)
{
    List<int> list;
    int result[3];
    list.push_front(3);
    list.push_front(5);
    list.push_front(78);
    int i = 0;
    for_each(list, [ & ](int &e) { result[i++] = e; });
    EXPECT_EQ(result[0], 78);
    EXPECT_EQ(result[1], 5);
    EXPECT_EQ(result[2], 3);
    EXPECT_EQ(count(list, 78), 1);
    for_each(list.begin(), list.end(), [ ](int &e) { e = 22; });
    i = 0;
    for_each(list, [ & ](int &e) { result[i++] = e; });
    EXPECT_EQ(result[0], 22);
    EXPECT_EQ(result[1], 22);
    EXPECT_EQ(result[2], 22);
}

TEST(MixedTests, canUseCountOnList)
{
    List<int> list{ 3, 7, 8, 6, 5, 3, 7, 9, 60, 55, 8, 6 };
    EXPECT_EQ(count(list, 3), 2);
    EXPECT_EQ(count(list, 9), 1);
    EXPECT_EQ(count(list, 20), 0);
    auto result1 = count_if(list, [ ](const int &e) { return e > 3; });
    EXPECT_EQ(result1, 10);
    auto result2 = count_if(list, [ ](const int &e) { return e < 3; });
    EXPECT_EQ(result2, 0);
    auto result3 = count_if(list, [ ](const int &e) { return 1; });
    EXPECT_EQ(result3, 12);
    auto result4 = count_if(list, [ ](const int &e) { return 0; });
    EXPECT_EQ(result4, 0);
}

TEST(MixedTests, canSwapSameSizeLists)
{
    List<int> list1{ 3, 7, 8, 6 };
    List<int> list2{ 9, 15, -3, 21 };
    swap(list1, list2);
    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list1.front(), 9);
    EXPECT_EQ(list1.back(), 21);
    EXPECT_EQ(list2.size(), 4);
    EXPECT_EQ(list2.front(), 3);
    EXPECT_EQ(list2.back(), 6);
    swap(list1, list2);
    EXPECT_EQ(list2.size(), 4);
    EXPECT_EQ(list2.front(), 9);
    EXPECT_EQ(list2.back(), 21);
    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list1.front(), 3);
    EXPECT_EQ(list1.back(), 6);
}

TEST(MixedTests, canSwapDifferentSizeLists)
{
    List<int> list1{ 3, 7, 8, 6, 8, 4 };
    List<int> list2{ 9, 15, -3, 21 };
    swap(list1, list2);
    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list1.front(), 9);
    EXPECT_EQ(list1.back(), 21);
    EXPECT_EQ(list2.size(), 6);
    EXPECT_EQ(list2.front(), 3);
    EXPECT_EQ(list2.back(), 4);
    swap(list1, list2);
    EXPECT_EQ(list2.size(), 4);
    EXPECT_EQ(list2.front(), 9);
    EXPECT_EQ(list2.back(), 21);
    EXPECT_EQ(list1.size(), 6);
    EXPECT_EQ(list1.front(), 3);
    EXPECT_EQ(list1.back(), 4);
}

TEST(MixedTests, canFillList)
{
    List<int> list;
    list.resize(30);
    fill(list, 945);
    EXPECT_EQ(list.size(), 30);
    EXPECT_EQ(list.front(), 945);
    EXPECT_EQ(list.back(), 945);
    list.resize(10);
    fill(list, 3);
    EXPECT_EQ(list.size(), 10);
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 3);
}
