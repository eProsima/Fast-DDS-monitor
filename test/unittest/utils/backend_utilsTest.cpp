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

#include <fastdds_monitor/backend/backend_utils.h>

using namespace backend;

//! Check that the conversion from EntityId to QString makes the same value as QString constructor
TEST(utilsBackendTest, backend_id_to_models_id)
{
    ASSERT_EQ(backend_id_to_models_id(EntityId(0)), QString("0"));
    ASSERT_EQ(backend_id_to_models_id(EntityId(111)), QString("111"));
    ASSERT_EQ(backend_id_to_models_id(EntityId(987654321)), QString("987654321"));
    ASSERT_EQ(backend_id_to_models_id(EntityId::invalid()), models::ID_ALL);
    ASSERT_EQ(backend_id_to_models_id(EntityId::all()), models::ID_INVALID);
}

//! Check that the conversion from models::EntityId to backend::EntityId produces a correct EntityId
TEST(utilsBackendTest, models_id_to_backend_id)
{
    ASSERT_EQ(models_id_to_backend_id(models::EntityId("0")), EntityId(0));
    ASSERT_EQ(models_id_to_backend_id(models::EntityId("111")), EntityId(111));
    ASSERT_EQ(models_id_to_backend_id(models::EntityId("987654321")), EntityId(987654321));
    ASSERT_EQ(models_id_to_backend_id(models::EntityId(
                models::ID_ALL)),
            EntityId::all());
    ASSERT_EQ(models_id_to_backend_id(models::EntityId(
                models::ID_INVALID)),
            EntityId::invalid());
}

/**
 * Check that the info retrieved from a EntityInfo structure is the correct in cases
 * - string
 * - int
 * - double
 * - bool
 * - json substructure
 * - key not exist
 */
TEST(utilsBackendTest, get_info_value)
{
    // Building dummy info from string
    std::string dummy_info_st = R"({"name":"some_name","id":1,"latency":1.1,"value":false})";
    EntityInfo dummy_info = EntityInfo::parse(dummy_info_st);

    std::cout << dummy_info_st << std::endl;
    std::cout << dummy_info << std::endl;

    ASSERT_EQ(get_info_value(dummy_info, "name"), "some_name");
    ASSERT_EQ(std::stoi(get_info_value(dummy_info, "id")), 1);
    ASSERT_EQ(std::stod(get_info_value(dummy_info, "latency")), 1.1);
    ASSERT_FALSE(std::stoi(get_info_value(dummy_info, "value")));

    // Case to retrieve non terminal values
    EntityInfo super_dummy_info;
    super_dummy_info["info"] = dummy_info;
    ASSERT_EQ(EntityInfo::parse(get_info_value(super_dummy_info, "info")), dummy_info);

    // Negative case
    ASSERT_NE(get_info_value(dummy_info, "Name"), "some_name");
}

//! Check the conversion from QString to EntityKind
TEST(utilsBackendTest, string_to_entity_kind)
{
    std::map<std::string, EntityKind> conversionTable = {
        {"Host", EntityKind::HOST},
        {"User", EntityKind::USER},
        {"Process", EntityKind::PROCESS},
        {"Domain", EntityKind::DOMAIN_ENTITY},
        {"Topic", EntityKind::TOPIC},
        {"DomainParticipant", EntityKind::PARTICIPANT},
        {"DataWriter", EntityKind::DATAWRITER},
        {"DataReader", EntityKind::DATAREADER},
        {"Locator", EntityKind::LOCATOR}
    };

    for (const auto& it : conversionTable)
    {
        ASSERT_EQ(string_to_entity_kind(QString::fromStdString(it.first)), it.second);
    }
}

//! Check the conversion from QString to DataKind
TEST(utilsBackendTest, string_to_data_kind)
{
    std::map<std::string, DataKind> conversionTable = {
        {"FASTDDS_LATENCY", DataKind::FASTDDS_LATENCY},
        {"NETWORK_LATENCY", DataKind::NETWORK_LATENCY},
        {"PUBLICATION_THROUGHPUT", DataKind::PUBLICATION_THROUGHPUT},
        {"SUBSCRIPTION_THROUGHPUT", DataKind::SUBSCRIPTION_THROUGHPUT},
        {"RTPS_PACKETS_SENT", DataKind::RTPS_PACKETS_SENT},
        {"RTPS_BYTES_SENT", DataKind::RTPS_BYTES_SENT},
        {"RTPS_PACKETS_LOST", DataKind::RTPS_PACKETS_LOST},
        {"RTPS_BYTES_LOST", DataKind::RTPS_BYTES_LOST},
        {"RESENT_DATA", DataKind::RESENT_DATA},
        {"HEARTBEAT_COUNT", DataKind::HEARTBEAT_COUNT},
        {"ACKNACK_COUNT", DataKind::ACKNACK_COUNT},
        {"NACKFRAG_COUNT", DataKind::NACKFRAG_COUNT},
        {"GAP_COUNT", DataKind::GAP_COUNT},
        {"DATA_COUNT", DataKind::DATA_COUNT},
        {"PDP_PACKETS", DataKind::PDP_PACKETS},
        {"EDP_PACKETS", DataKind::EDP_PACKETS},
        {"DISCOVERY_TIME", DataKind::DISCOVERY_TIME},
        {"SAMPLE_DATAS", DataKind::SAMPLE_DATAS}
    };

    for (const auto& it : conversionTable)
    {
        ASSERT_EQ(string_to_data_kind(QString::fromStdString(it.first)), it.second);
    }
}

//! Check the conversion from QString to StatisticKind
TEST(utilsBackendTest, string_to_statistic_kind)
{
    std::map<std::string, StatisticKind> conversionTable = {
        {"RAW DATA", StatisticKind::NONE},
        {"MEAN", StatisticKind::MEAN},
        {"STANDARD_DEVIATION", StatisticKind::STANDARD_DEVIATION},
        {"MAX", StatisticKind::MAX},
        {"MIN", StatisticKind::MIN},
        {"MEDIAN", StatisticKind::MEDIAN},
        {"COUNT", StatisticKind::COUNT},
        {"SUM", StatisticKind::SUM}
    };

    for (const auto& it : conversionTable)
    {
        ASSERT_EQ(string_to_statistic_kind(QString::fromStdString(it.first)), it.second);
    }
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
