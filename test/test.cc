#include <gtest/gtest.h>
#include <sstream>
#include "utility.h"

TEST(TestReadPositiveInteger, TestPositive)
{
    std::istringstream in("17");
    std::ostringstream out;
    size_t dest;
    EXPECT_TRUE(Utility::readPositiveInteger(in, out, dest, "", ""));
    EXPECT_EQ(dest, 17);
}

TEST(TestReadPositiveInteger, TestNegative)
{
    std::istringstream in("-1");
    std::ostringstream out;
    size_t dest;
    EXPECT_FALSE(Utility::readPositiveInteger(in, out, dest, "", ""));
}

TEST(TestInitializeArray, TestSize1)
{
    constexpr size_t size = 1;
    int *array = Utility::initializeArray(size);
    EXPECT_EQ(array[0], Utility::valueToInitialize);
    delete[] array;
}

TEST(TestInitializeArray, TestSize7)
{
    constexpr size_t size = 7;
    int *array = Utility::initializeArray(size);
    for(size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(array[i], Utility::valueToInitialize);
    }
    delete[] array;
}

TEST(TestOutputArray, TestSize1)
{
    constexpr size_t size = 1;
    int array[size] = {7};
    std::ostringstream out;
    std::string expectedAnswer = "7 \n";
    Utility::outputArray(out, array, size);
    EXPECT_EQ(out.str(), expectedAnswer);
}

TEST(TestOutputArray, TestSize4)
{
    constexpr size_t size = 4;
    int array[size] = {5, 2, 7, 1};
    std::ostringstream out;
    std::string expectedAnswer = "5 2 7 1 \n";
    Utility::outputArray(out, array, size);
    EXPECT_EQ(out.str(), expectedAnswer);
}

TEST(TestOutputMarkers, TestMarkerCount0)
{
    constexpr size_t markerCount = 0;
    int *finish = nullptr;
    std::ostringstream out;
    std::string expectedAnswer = "\n";
    Utility::outputMarkers(out, finish, markerCount);
    EXPECT_EQ(out.str(), expectedAnswer);
}

TEST(TestOutputMarkers, TestMarkerCount1Enabled)
{
    constexpr size_t markerCount = 1;
    int finish[markerCount] = {1};
    std::ostringstream out;
    std::string expectedAnswer = "\n";
    Utility::outputMarkers(out, finish, markerCount);
    EXPECT_EQ(out.str(), expectedAnswer);
}

TEST(TestOutputMarkers, TestMarkerCount7Enabled3)
{
    constexpr size_t markerCount = 7;
    int finish[markerCount] = {1, 0, 0, 0, 1, 1, 1};
    std::ostringstream out;
    std::string expectedAnswer = "2 3 4 \n";
    Utility::outputMarkers(out, finish, markerCount);
    EXPECT_EQ(out.str(), expectedAnswer);
}

TEST(TestInputWorkingMarkerId, TestFirstInput)
{
    std::istringstream in("1");
    std::ostringstream out;
    constexpr size_t markerCount = 5;
    int finish[markerCount] = {0, 1, 1, 0, 0};
    size_t id = Utility::inputWorkingMarkerId(in, out, finish, markerCount, "");
    EXPECT_EQ(id, 0);
}

TEST(TestInputWorkingMarkerId, TestSecondInputThirdMarker)
{
    std::istringstream in("0 4\n");
    std::ostringstream out;
    constexpr size_t markerCount = 5;
    int finish[markerCount] = {1, 1, 1, 0, 0};
    size_t id = Utility::inputWorkingMarkerId(in, out, finish, markerCount, "");
    EXPECT_EQ(id, 3);
}