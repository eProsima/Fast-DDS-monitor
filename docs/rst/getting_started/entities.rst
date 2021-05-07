.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _entities:

########
Entities
########

The monitoring functions of this application relays on tracking the activity of certain *Entities* that the
*Fast DDS Monitor* will retireve, as well as it stores their data and the connections between them
for their presentation to the user.
These entities represents DDS communication entities, or different physical elements related with DDS entities.

In the following diagram could be seen the different kind of entities being tracked by the monitor.
The arrows in this schema represents a direct connection (not a 1:n in every case) between both kind of entities,
Those entities, or types of entities, that do not have a direct relationship are also related as
intermediate entities make it possible to relate any entity in the graph to another indirectly,
i.e. one *DomainParticipant* is related with its *User* by the relation with its *Process*.

.. _fig-entities-diagram:

.. figure:: /rst/figures/entities_diagram.svg

.. _dds_entities:

DDS Entities
============

This entities represent the DDS entities that manage the communication. That is, the *DomainParticipants*
and the DataWriters and DataReaders it manages. |br|
Each DataReader/DataWriter has one or more associated Locator entities.
Locators are the network addresses through which DataReaders/DataWriters communicate in a DDS network.

For further information about each entity, please refer to the |DDSSpecification| or visit the |FastDDSDocs|.

.. _participant_entity:

DomainParticipant
-----------------
The *DomainParticipant* is the main entity in the DDS protocol.
It represents a collection of DataReaders/DataWriters, and manage the whole DDS Discovery of others *DomainParticipants*
and *DataReaders/DataWriters* within the DDS Domain to which it belongs.
Refer to `Fast DDS Documentation
<https://fast-dds.docs.eprosima.com/en/latest/fastdds/dds_layer/domain/domainParticipant/domainParticipant.html>`_
for a more detailed explanation of the *DomainParticipant* entity in DDS.

Each *DomainParticipant* can only communicate under one *Domain* (see :ref:`logical_entities`)
and so it exist a direct connection between each *DomainParticipant* and the *Domain* in which it works. |br|
From image :ref:`fig-entities-diagram` it can be seen that a the DomainParticipant entities are contained in a Process,
this is because a system process (so-called *Process* entity) executes an application using Fast DDS
that instantiates *DomainParticipants*.
The same applies to *DataReaders/DataWriters* instantiated by a *DomainParticipant* belonging to a specific *Process*.
Therefore, a *Process* can contain as many DDS entities as the Fast DDS application running in that *Process*
has instantiated.

.. _datawriter_entity:

DataWriter
-----------
*DataWriter* is the DDS entity in charge of publishing the data.

Each *DataWriter* is directly contained in a single DomainParticipant.
In addition, since a *DataWriter* is associated to the *Topic* under which it publishes,
it is possible to define a direct containment relationship of a *DataWriter* in a *Topic*.
Thus, the *Topic* will contain all the *DataWriter*s that are publishing under it.

Therefore, each *DataWriter* is directly connected with the *DomainParticipant* it belongs,
and with the *Topic* under which it publish.
Also a *DataWriter* is associated with one or multiple *Locators*, that would represent the physical communication
channel this *DataWriter* is using to send data.

.. _datareader_entity:

DataReader
----------
*DataReader* holds the subscribe function of the communication.
As for the *DataWriter*, each *DataReader* is directly contained in a single *DomainParticipant*.
In addition, since a *DataReader* is associated to the *Topic* to which it is subscribed, it is possible to define
a direct containment relationship of a *DataReader* in a *Topic*.
Thus, the *Topic* will contain all the *DataReaders* that are publishing under it.
Therefore, each *DataReader* is directly connected with the *DomainParticipant* it belongs,
and with the *Topic* to which it is subscribed.

.. _locator_entity:

Locator
-------
This entity represents the physical address and port that a *DataReader/DataWriter* uses to send or/and receive data.
This entity is related with the physical division of the entities, as a *Locator* belongs to a unique *Host*
(see section :ref:`physical_entities`).
However, the monitor treats this entity as a *DDS Entity* in order to simplify the entities connection and make
the entities display more comprehensible.

A *Locator* is connected with one or multiple *DataReader/DataWriter*, and so it is related with a *Host*
by relating each of
these *DataReader/DataWriter* with a *DomainParticipant* and each *DomainParticipant* with its *Host*.

.. _logical_entities:

Logical Entities
================

.. _domain_entity:

Domain
------
*Domain* represents a logical abstraction in DDS protocol that divide the DDS network by partitions,
making each *Domain* completely independent and unaware of others.
This logical partition depends on the chosen discovery protocol.

In case of using the *Simple Discovery Protocol* (discovery protocol by default in Fast DDS) as the default discovery
mechanism, the *Domain* will be represented by a number, and every DDS entity in that *Domain* is going to discover
the rest entities deployed on the same *Domain*. |br|
In case of using *Discovery Server* as discovery protocol the partition will be made by the *Discovery Server*
or *Discovery Servers Net* to which the monitor connects. Please refer to
`Fast DDS documentation <https://fast-dds.docs.eprosima.com/en/v2.3.0/fastdds/discovery/discovery_server.html>`_ for
more information about this feature.
Each entity connected to a *Discovery Server* on the same network will know all other entities with which it needs to
communicate.

This entity inside the monitor is related with the *DomainParticipants* that communicate under this same *Domain*,
and the *Topics* created in this *Domain*.

.. _topic_entity:

Topic
-----
*Topic* is an abstract DDS entity that represents the channel of communications between publishers and subscribers.
Every *DataReader* subscribed to a *Topic* will receive the publications of every *DataWriter*
publishing under the same *Topic*.

This entity inside the monitor is directly connected with the *Domain* it belongs,
and with the *DataReaders*/*DataWriters* communicating under this *Topic*.

.. _physical_entities:

Physical Entities
=================

.. _host_entity:

Host
----
*Host* make reference to the physical (or logical i.e. Docker) machine where one or some DDS *Processes*
are running. |br|
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
*Process* represents each process running an application using *Fast DDS*. Be aware that it is possible to
run more than one *DomainParticipant* in the same *Process*, and they do not require to be related with
each other, not even under the same *Domain*.

This entity is connected directly with the *User* it belongs, and the *Participants* running within it.
