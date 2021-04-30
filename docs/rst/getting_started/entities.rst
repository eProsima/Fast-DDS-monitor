.. include:: ../exports/alias.include

.. _entities:

########
Entities
########

The monitoring functions of this application relays on the tracking the activity of certain *Entities* that the monitor
will store, as their data and connections.
These entities represents DDS communication entities, or different physical elements related with DDS entities.

In the following diagram could be seen the different kind of entities that are tracking by the monitor,
and the connection between them.
The arrows in this schema represents a direct connection (not a 1 to n in every case) between both kind of entities,
but the entity kinds that are not connected directly are related to each other by the connections of the entities
directly connected, creating a connected graph where every kind of entity has a relation with each other.

.. figure:: /rst/figures/entities_diagram.svg

.. _dds_entities:

DDS Entities
============

This entities represents the DDS entities that manage the communication. That is, the *DomainParticipants*
(*Participants* from now on) and the writers and readers it manages.
The word *Endpoint* will be use to refer to *DataWriters* and *DataReaders* indifferently.

For further information about each entity, please refer to the |DDSSpecification| or visit the |FastDDSDocs|.

.. _participant_entity:

Participant
-----------
*Participant* (*DomainParticipant* in DDS) is the main entity in the DDS protocol.
It represents a collection of writers and readers, and manage the whole DDS Discovery between external *Participants*,
their writers and readers, and the that belongs to itself.

Each *Participant* can only communicate under one *Domain* (visit :ref:logical_entities) and so it exist a direct
connection between each *participant* and the *Domain* it works in. \
It also exist a direct connection between a *Pocess* and where the *Participant* is being executed.
Be aware that one *Participant* and its *DataReaders* and *DataWriters* are always under one and the same *Process*,
but in one *Process* more than one *Participant* could be running. \
Each *Participant* is a collection of *DataWriters* and *DataReaders*, and so it has a direct connection with each of
them.

.. _datawriter_entity:

DataWriter
-----------
*DataWriter* holds the write function of the communication.
Each *DataWriter* is associated with one *Topic*, and it publish data under this topic, so each *DataReader* under
the same topic will receive this data.

Each *DataWriter* is connected directly with the *Participant* it belongs, and with the *Topic* it publish under. \
Also a *DataWriter* is associated with one or multiple *Locators*, that would represent the physical communication
channel this *DataWriter* is using to send data.

.. _datareader_entity:

DataReader
-----------
*DataReader* holds the read function of the communication.
Each *DataReader* is associated with one *Topic* where it is subscribed, and it reads every data that any *DataWriter*
publish under this *Topic*.

Each *DataReader* is connected directly with the *Participant* it belongs, and with the *Topic* it subscribes under. \
Also a *DataReader* is associated with one or multiple *Locators*, that would represent the physical communication
channel this *DataReader* is using to receive data.

.. _locator_entity:

Locator
-----------
This entity represents the physical address and port that an *Endpoint* uses to send or/and receive data.
This entity is related with the physical division of the entities, as a *Locator* belongs to a unique *Host*.
However, the monitor treats this entity as a *DDS Entity* in order to simplify the entities connection and make
the entities display more comprehensible.

*Locator* is connected with one or multiple *Endpoints*, and so it is related with a *Host* by relating each of
these *Endpoints* with a *Participant* and each *Participant* with its *Host*.

.. _logical_entities:

Logical Entities
================

.. _domain_entity:

Domain
------
*Domain* represents a logical abstraction in DDS protocol that divide the DDS network by partitions, making
each *domain* completely independent and unaware of others.
This logical partition could depends on the discovery protocol chosen. \
In case *Simple Discovery* (discovery protocol by default) is in use, the *Domain* is represented by a number,
and every entity in that *Domain* is going to be aware of the rest. \
In case of using *Discovery Server* as discovery protocol (please, refer to
`Fast DDS documentation <https://fast-dds.docs.eprosima.com/en/v2.3.0/fastdds/discovery/discovery_server.html>` for
more information about this feature) the partition will be made by the Discovery Server or Discovery Servers Net that
the monitor connects. Every entity connected to one of this Discovery Servers in the same network, will know and
communicate with each other.

This entity inside the monitor is related with the *Participants* that communicate under this same *Domain*,
and the *Topics* created in this *Domain*.

.. _topic_entity:

Topic
-----
*Topic* is an abstract DDS entity that represents the channel of communications between publishers and subscribers.
Every *DataReader* will receive the publications of every *DataWriter* in the same *Topic*.

This entity inside the monitor is directly connected with the *Domain* it belongs, and with the *Endpoints*,
that is: *DataWriters* and *DataReaders*, that communicate under this *Topic*.

.. _physical_entities:

Physical Entities
=================

.. _host_entity:

Host
----
*Host* make reference to the physical (or logical i.e. Docker) machine where one or some DDS *Processes* are running.

This entity is connected directly with the *Users* running in this *Host*.

.. _user_entity:

User
----
*User* make reference to the different users that could run in a *Host*.

This entity is connected directly with the *Host* it belongs, and the running *Processes* that are being executed
within this *User*.

.. _process_entity:

Process
-------
*Process* represents each process where one or several *Participants* are running. Be aware that it is possible to
run more than one *Participant* in the same *Process*, and those *Participants* do not require to be related with
each other, not even under the same *Domain*.

This entity is connected directly with the *User* it belongs, and the *Participants* running under it.
