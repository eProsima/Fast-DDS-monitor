.. include:: ../exports/alias.include

.. _start_tutorial:

################
Example of usage
################

This example will show how to monitoring a DDS network using Fast DDS Monitor and how to understand the different
application features and configurations.

*******************************
Fast DDS with Statistics module
*******************************

In order to show the Fast DDS Monitor running and monitoring a real DDS network, we are going to use a Fast DDS
example to create a simple and understandable DDS network.
The example proposed by this tutorial is using :code:`DDSHelloWorldExample` of Fast DDS repository.
Be aware that the statistics module is not compiled and used by default by Fast DDS but it has to be specifically
configured to run and send statistical data of an specific entity.

In order to execute this minimum DDS scenario where each entity publish its statistical data, follow these steps:

#. Compile Fast DDS library with CMake option :code:`FASTDDS_STATISTICS` to activate the statistics module.
#. Compile Fast DDS library with CMake option :code:`COMPILE_EXAMPLES` to build the examples.
#. Has an scenario with Fast DDS, Fast DDS Statistics Backend and Fast DDS Monitor built.
#. Use Environmental Variable :code:`FASTDDS_STATISTICS` to activate the statistics writers in the DDS execution.

For further information about the Statistics configuration, refer to
`Fast DDS statistics module <https://fast-dds.docs.eprosima.com/en/v2.3.2/fastdds/statistics/statistics.html>`_.
For further information about installation of the Monitor and its dependencies, refer to this documentation section
:ref:`installation_manual_linux`.

.. todo::

    add the source installation.

.. _hello_world_example:

Hello World Example
===================

For this tutorial the has being used the Fast DDS :code:`DDSHelloWorldExample` to show a minimum DDS network being
monitoring.
Following there are the command executions in order to run this network.
Nevertheless, this tutorial does not start whit this DDS network running but it is executed once the monitor has been
started.
This does not change the Monitor behavior, but would change the data and information shown by the application.

#. Execute a Fast DDS :code:`DDSHelloWorldExample` **subscriber** with statistics data active.

.. code-block:: bash

    FASTDDS_STATISTICS="HISTORY_LATENCY_TOPIC;DATA_COUNT_TOPIC;PHYSICAL_DATA_TOPIC" \
        ./build/fastrtps/examples/C++/DDS/HelloWorldExample/DDSHelloWorldExample \
        subscriber  # Creates a subscriber in topic: "HellowWorldTopic" domain: 0

#. Execute a Fast DDS :code:`DDSHelloWorldExample` **publisher** with statistics data active.

.. code-block:: bash

    FASTDDS_STATISTICS="HISTORY_LATENCY_TOPIC;DATA_COUNT_TOPIC;PHYSICAL_DATA_TOPIC" \
        ./build/fastrtps/examples/C++/DDS/HelloWorldExample/DDSHelloWorldExample \
        publisher \ # Creates a publisher in topic: "HellowWorldTopic" domain: 0
        0 \         # Run indefinitly until enter pressed
        1000        # Send one message per second

Statistics topics
-----------------

Environmental Variable :code:`FASTDDS_STATISTICS` activates the statistics writers for a Fast DDS execution.
This means that the *Participants* created within this variable, will report the statistical data related
to them and their sub-entities.

For this example, only some of the available topics has been activated.
This means that each participant will only report this specific data and it will not store or send any other data.
This is very useful in order to limit the network traffic, as sending all the data highly increase the amount
of DDS data sent.

The topics that are going to be reported by this example are:

* **HISTORY_LATENCY_TOPIC** Report the latency of the messages between the two entities.
* **DATA_COUNT_TOPIC** Report the number of samples sent.
* **PHYSICAL_DATA_TOPIC** Report the physical data of the participant.
  This will make possible to see in which hosts and context each entity is running.

For further information about these topics and other that could be use, refer to
`Fast DDS documentation <https://fast-dds.docs.eprosima.com/en/v2.3.2/fastdds/statistics/dds_layer/topic_names.html>`_.

**************************
Fast DDS Monitor Execution
**************************

In the following section is presented a full Fast DDS Monitor execution monitoring a real DDS network.

Initial Window
==============

To start this example, we start with non DDS entities running.
First of all we would see the Fast DDS Monitor initial window.
We press :code:`Start monitoring!` in order to enter the application and start the monitoring.

.. todo::

    main screenshot

Initiate monitoring
===================

Once in the application, first Dialog that appear ask us to insert a domain in order to start monitoring that domain.
Monitoring a domain means to listen in that domain for DDS entities that are running and reporting statistical data.
For further information refer to section :ref:`monitor_domain`.

We could pressing :code:`Cancel` and we could see around the monitor and check its configurations, but no entities or
data will be shown as there are not domains being monitoring.
We could always return to the :ref:`initialize_monitoring` dialog from :ref:`edit_menu` or :ref:`shortcuts_bar_layout`.

We are going to initialize monitoring in **domain 0** and pressing :code:`OK`.

.. todo::

    init monitor 0

At this point, we are going to see the whole window of the application.
We could see how a unique entity is present in the application in left panels.
This is the domain we just have initiated.
Once a domain is initiated, it is set as :ref:`selected_entity` and so its information is shown in the
:ref:`right_sidebar_layout`.

For specific details on how the information is divided and where to find it, please refer to :ref:`index_user_manual`.


Execute subscriber
==================

Now we are going to execute the first DDS entity in our DDS network: a *DomainParticipant* with one *DataReader* in
topic :code:`HelloWorldTopic` in domain :code:`0` following the steps given in :ref:`hello_world_example`.
Once the subscriber is running our window will update and we could see new information.

.. todo::

    subscriber initialized

First of all, we could see that the number of entities discovered has incresed.
Now we have a *DomainParticipant* called :code:`Participant_sub`, that holds a *DataReader* called
:code:`DataReader_HelloWorldTopic_0.0.1.4`.
This *DataReader* has a locator, that with default configurtion will be the *Shared Memory* related locator.
That is because the Monitor and the *DomainParticipant* are running in the same host, and so they use *interprocess*
communication.

We could see as well that now *Host* exists, with a *User* and a *Process* where :code:`Participant_sub` is running.
This information is retrieved by the *DomainParticipant* thanks to activate the :code:`PHYSICAL_DATA_TOPIC`.
There is also a new *Topic* :code:`HelloWorldTopic` under *Domain* :code:`0`.

Making double click in any entity name we could see its specific information, such as name, backend id, QoS, etc.

.. todo::

    information of Datareader
