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

#include <string>

#include <gtest_aux.hpp>
#include <gtest/gtest.h>

#include <QString>

#include <fastdds_monitor/backend/SyncBackendConnection.h>

using namespace utils;

class SyncBackendConnectionTest : public ::testing::Test
{

public:

    void SetUp ()
    {
    }

    void TearDown()
    {
    }

};


//! Test that the listener is correctly set and unset to the database
TEST_F(SyncBackendConnectionTest, listener)
{
    // TODO
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
