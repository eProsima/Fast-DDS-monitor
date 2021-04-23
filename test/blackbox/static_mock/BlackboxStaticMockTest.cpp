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

#include "gtest/gtest.h"

#include <QApplication>

#include <fastdds-monitor/Engine.h>

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
TEST_F(BlackboxStaticMockTest, enable_engine)
{
    int argc = 1;
    char* argv[1] = {static_cast<char*>("test")};
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
