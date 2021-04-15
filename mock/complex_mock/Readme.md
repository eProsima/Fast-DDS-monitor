# Fast-DDS-Statistics-Backend Complex Mock

Mock that simulates the input data from an active FastDDS Statistics Backend.

## Entities

The entities that the mock simulates are dynamically created:

1. When `init_monitor` pressed, a new Domain entity is created, and one entity of each kind under this domain.
1. With periodicall time, new entities are created in three different ways:
    1. New DataWriter/DataReader in an already existing Participant and Topic
    1. New Topic in an already existing Domain, and a new DataWriter/DataReader in an already sexisting Participant
    1. New Process in an already User, new Participant in that Process and already existing Domain, and new Endpoints and locators
