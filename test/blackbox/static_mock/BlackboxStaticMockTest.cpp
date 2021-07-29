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

#include <gtest_aux.hpp>
#include <gtest/gtest.h>

#include <QApplication>

#include <fastdds_monitor/Engine.h>

/**
 * This test checks the functions of Engine works by checking the model updates
 */

class BlackboxStaticMockTest;

//! Mock to use getter methods of protected variables of Engine
class MockEngine : public Engine
{
public:

    // using Engine::Engine;
    MockEngine ()
        : Engine()
    {
    }

    bool enabled()
    {
        return enabled_;
    }

};

//! Check that enables function works and the Engine set enable variable to True
TEST(BlackboxStaticMockTest, enable_engine)
{
    int argc = 1;
    char argv1[5] = "test";
    char* argv[1] = {argv1};
    QApplication app(argc, argv);
    MockEngine engine;

    EXPECT_FALSE(engine.enabled());
    engine.enable();
    EXPECT_TRUE(engine.enabled());
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
