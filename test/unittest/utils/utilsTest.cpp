// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <ctime>
#include <math.h>
#include <sys/time.h>
#include <time.h>

#include <string>

#include "gtest/gtest.h"

#include <QString>

#include <fastdds-monitor/utils.h>

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
//  - miliseconds OFF: YYYY:MM:DD HH:MM:SS
//  - miliseconds ON : YYYY:MM:DD HH:MM:SS.mmm
TEST(utilsTest, now_format)
{
    // Without miliseconds
    {
        // Get the date 5 times
        for (int i=0; i<5; ++i)
        {
            std::string date = now(false);
            ASSERT_EQ(date.size(), 19);
            for (int j=0; j<19; ++j)
            {
                switch (j)
                {
                case 4:
                case 7:
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
        // Get the date 5 times
        for (int i=0; i<5; ++i)
        {
            std::string date = now();
            ASSERT_EQ(date.size(), 23);
            for (int j=0; j<19; ++j)
            {
                switch (j)
                {
                case 4:
                case 7:
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

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
