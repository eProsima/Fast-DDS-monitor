// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima Fast DDS Monitor.
//
// eProsima Fast DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima Fast DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima Fast DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

#include <chrono>
#include <cmath>
#include <ctime>
#include <string>
#include <thread>
#include <time.h>

#include <gtest_aux.hpp>
#include <gtest/gtest.h>

#include <QString>

#include <fastdds_monitor/utils.h>

using namespace utils;

//! Test that convert string to QString retrieves the same value as QString constructor
TEST(utilsTest, to_QString)
{
    ASSERT_EQ(to_QString(std::string("")), QString(""));
    ASSERT_EQ(to_QString(std::string("0")), QString("0"));
    ASSERT_EQ(to_QString(
                std::string("Hello World 1 Hello World 2 Hello World 3 Hello World 4 Hello World 5 Hello World")),
            QString(    "Hello World 1 Hello World 2 Hello World 3 Hello World 4 Hello World 5 Hello World"));
}

//! Test that convert QString to string retrieves the same value as QString constructor
TEST(utilsTest, to_string)
{
    ASSERT_EQ(to_string(QString("")), std::string(""));
    ASSERT_EQ(to_string(QString("0")), std::string("0"));
    ASSERT_EQ(to_string(
                QString(    "Hello World 1 Hello World 2 Hello World 3 Hello World 4 Hello World 5 Hello World")),
            std::string("Hello World 1 Hello World 2 Hello World 3 Hello World 4 Hello World 5 Hello World"));
}

//! Check that now function returns the correct format:
//  - miliseconds OFF: YYYY-MM-DD HH:MM:SS
//  - miliseconds ON : YYYY-MM-DD HH:MM:SS.mmm
TEST(utilsTest, now_format)
{
    int repeat = 20;
    uint32_t sleep = 113; // Use non round numbers so the microseconds change randomly
    // Without miliseconds
    {
        // Get the date <repeat> times
        for (int i = 0; i < repeat; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
            std::string date = now(false);
            ASSERT_EQ(date.size(), 19);
            for (int j = 0; j < 19; ++j)
            {
                switch (j)
                {
                    case 4:
                    case 7:
                        ASSERT_EQ(date[j], '-');
                        break;
                    case 13:
                    case 16:
                        ASSERT_EQ(date[j], ':');
                        break;

                    case 10:
                        ASSERT_EQ(date[j], ' ');
                        break;

                    default:
                        ASSERT_LE(date[j], '9');
                        ASSERT_GE(date[j], '0');
                        break;
                }
            }
        }
    }

    // With miliseconds
    {
        // Get the date <repeat> times
        for (int i = 0; i < repeat; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
            std::string date = now();
            ASSERT_EQ(date.size(), 23);
            for (int j = 0; j < 19; ++j)
            {
                switch (j)
                {
                    case 4:
                    case 7:
                        ASSERT_EQ(date[j], '-');
                        break;
                    case 13:
                    case 16:
                        ASSERT_EQ(date[j], ':');
                        break;

                    case 10:
                        ASSERT_EQ(date[j], ' ');
                        break;

                    case 19:
                        ASSERT_EQ(date[j], '.');
                        break;

                    default:
                        ASSERT_LE(date[j], '9');
                        ASSERT_GE(date[j], '0');
                        break;
                }
            }
        }
    }
}

//! Test that convert QString to string retrieves the same value as QString constructor
TEST(utilsTest, double_to_string)
{
    ASSERT_EQ(double_to_string(12345), std::string("12345"));
    ASSERT_EQ(double_to_string(1234500), std::string("1234500"));
    ASSERT_EQ(double_to_string(1234500.00), std::string("1234500"));
    ASSERT_EQ(double_to_string(1234500.0011), std::string("1234500.0011"));
    ASSERT_EQ(double_to_string(1234500.00110), std::string("1234500.0011"));
    ASSERT_EQ(double_to_string(nan("")), std::string(""));
    ASSERT_EQ(double_to_string(sqrt(-1.0)), std::string(""));
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
