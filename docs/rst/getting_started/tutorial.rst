.. include:: ../exports/alias.include

.. _start_tutorial:

################
Example of usage
################

This example will show how to monitoring a DDS network using *Fast DDS Monitor* and how to understand the different
application features and configurations.

*******************************
Fast DDS with Statistics module
*******************************

In order to show the *Fast DDS Monitor* running and monitoring a real DDS network, this tutorial uses a *Fast DDS*
example to create a simple and understandable DDS network.
The example proposed by this tutorial is using :code:`DDSHelloWorldExample` of *Fast DDS* repository.
Be aware that the statistics module is not compiled and used by default by *Fast DDS* but it has to be specifically
configured to send statistical data of an specific entity.

In order to execute this minimum DDS scenario where each entity publish its statistical data, follow these steps:

#. Compile *Fast DDS* library with CMake option :code:`FASTDDS_STATISTICS` to activate the statistics module.
#. Compile *Fast DDS* library with CMake option :code:`COMPILE_EXAMPLES` to build the examples.
#. Have a working environment with *Fast DDS*, *Fast DDS Statistics Backend* and *Fast DDS Monitor* built.
#. Use the environment variable :code:`FASTDDS_STATISTICS` to activate the statistics writers in the DDS execution.

For further information about the Statistics configuration, please refer to
`Fast DDS statistics module <https://fast-dds.docs.eprosima.com/en/v2.3.2/fastdds/statistics/statistics.html>`_.
For further information about installation of the Monitor and its dependencies, please refer to the documentation
section :ref:`installation_manual_linux` or :ref:`developer_manual_installation_sources_linux`.

.. _hello_world_example:

Hello World Example
===================

For this tutorial it has being used the *Fast DDS* :code:`DDSHelloWorldExample` to show a minimum DDS network being
monitoring.
Below are the commands executed in order to run this network.
Nevertheless, this tutorial does not start with this DDS network running but it is executed once the monitor has been
started.
This does not change the Monitor behavior, but would change the data and information shown by the application.

#.  Execute a *Fast DDS* :code:`DDSHelloWorldExample` **subscriber** with statistics data active.

    .. code-block:: bash

        FASTDDS_STATISTICS="HISTORY_LATENCY_TOPIC;DATA_COUNT_TOPIC;PHYSICAL_DATA_TOPIC" \
            ./build/fastrtps/examples/C++/DDS/HelloWorldExample/DDSHelloWorldExample \
            subscriber

    where :code:`subscriber` argument creates a *DomainParticipant* with a *DataReader* in the topic
    :code:`HelloWorldTopic` in *Domain* :code:`0`.

#.  Execute a *Fast DDS* :code:`DDSHelloWorldExample` **publisher** with statistics data active.

    .. code-block:: bash

        FASTDDS_STATISTICS="HISTORY_LATENCY_TOPIC;DATA_COUNT_TOPIC;PHYSICAL_DATA_TOPIC" \
            ./build/fastrtps/examples/C++/DDS/HelloWorldExample/DDSHelloWorldExample \
            publisher \
            0 \
            500

    where :code:`publisher` argument creates a *DomainParticipant* with a *DataWriter* in the topic
    :code:`HelloWorldTopic` in *Domain* :code:`0`.
    The following arguments indicate this process to run until the user press :code:`enter` (:code:`0` samples)
    and to write a message every half second (:code:`500` milliseconds period).

Statistics topics
-----------------

The environment variable :code:`FASTDDS_STATISTICS` activates the statistics writers for a *Fast DDS*
application execution.
This means that the *DomainParticipants* created within this variable will report the statistical data related
to them and their sub-entities.

For this example, only some of the available topics has been activated.
This means that each participant will only report this specific data and it will not store or send any other data.
This is very useful in order to limit the network traffic, as sending all the data highly increase the amount
of DDS data sent.

The topics that are going to be reported by this example are:

* **HISTORY_LATENCY_TOPIC**: Report the latency of the messages between the two entities.
* **DATA_COUNT_TOPIC**: Report the number of samples sent.
* **PHYSICAL_DATA_TOPIC**: Report the physical data of the participant.
  This will make possible to see in which hosts and context each entity is running.

For further information about these topics and other that could be use, please refer to
`Fast DDS documentation <https://fast-dds.docs.eprosima.com/en/v2.3.2/fastdds/statistics/dds_layer/topic_names.html>`_.

**************************
Fast DDS Monitor Execution
**************************

In the following section is presented a full *Fast DDS Monitor* execution monitoring a real DDS network.

Initial Window
==============

The Monitor starts with non DDS entities running.
First of all, the *Fast DDS Monitor* initial window is shown.
Press :code:`Start monitoring!` in order to enter the application and start the monitoring.

.. figure:: /rst/figures/screenshots/main.png
    :align: center

Initiate monitoring
===================

Once in the application, the first Dialog that appear ask the user to insert a domain in order to start monitoring
that domain.
Monitoring a domain means to listen in that domain for DDS entities that are running and reporting statistical data.
Please refer to section :ref:`monitor_domain` for further information.

First, the :code:`Cancel` button is pressed so the user can see around the monitor and check its configurations,
but no entities or data will be shown as there are not domains being monitored.
You can always return to the :ref:`initialize_monitoring` dialog from :ref:`edit_menu` or :ref:`shortcuts_bar_layout`.

Let's initialize monitoring in **domain 0** and pressing :code:`OK`.

.. figure:: /rst/figures/screenshots/usage_example/init_domain.png
    :align: center

At this point, you are going to see the whole window of the application.
You should be able to see how an unique entity is present in the application in the left sidebar.
This is the domain that you have just initiated.
Once a domain is initiated, it is set as :ref:`selected_entity` and so its information is shown in the
:ref:`info_panel_layout`.

For specific details on how the information is divided and where to find it, please refer to :ref:`index_user_manual`.

Execute subscriber
==================

Now, execute the first DDS entity in our DDS network: a *DomainParticipant* with one *DataReader* in
topic :code:`HelloWorldTopic` in domain :code:`0` following the steps given in :ref:`hello_world_example`.
Once the subscriber is running our window will update and you could see new information in the left sidebar.

.. figure:: /rst/figures/screenshots/usage_example/execute_subscriber.png
    :align: center

First of all, the number of entities discovered has increased.
Now, you have a *DomainParticipant* called :code:`Participant_sub`, that holds a *DataReader* called
:code:`DataReader_HelloWorldTopic_0.0.1.4`.
This *DataReader* has a locator, which will be the *Shared Memory Transport* locator.
That is because the Monitor and the *DomainParticipant* are running in the same host, and so they use *interprocess*
communication.

You should be able to see as well that now *Host* exists, with a *User* and a *Process* where :code:`Participant_sub`
is running.
This information is retrieved by the *DomainParticipant* thanks to activate the :code:`PHYSICAL_DATA_TOPIC`.
There is also a new *Topic* :code:`HelloWorldTopic` under *Domain* :code:`0`.

Making double click in any entity name we could see its specific information, such as name, backend id, QoS, etc.

.. figure:: /rst/figures/screenshots/usage_example/information_subscriber.png
    :align: center

Execute publisher
=================

The next step is to execute a publisher in topic :code:`HelloWorldTopic` in domain :code:`0`,
following the steps given in :ref:`hello_world_example`.
Once the publisher is running you will see that new entities has appeared.
Specifically, a new *DomainParticipant* :code:`Participant_pub` with a *DataWrtier*
:code:`DataWriter_HelloWorldTopic_0.0.1.3` and, in the case that this publisher has been executed from same
*Host* and *User*, there will be a new *Process* that represents the process where this new :code:`Participant_pub`
is running.

.. figure:: /rst/figures/screenshots/usage_example/information_publisher.png
    :align: center

Discovery Callbacks
===================

Whenever a new entity is discovered by the Monitor there is an event registered in :ref:`log_panel_layout`.
Checking this panel you could see the time when every entity that is being monitoring has been discovered.
This panel is refreshed automatically whenever a new entity is discovered.
Using the :ref:`refresh_button` this information is cleared until the current moment.

.. figure:: /rst/figures/screenshots/usage_example/callbacks.png
    :align: center

Summary of Statistical Data
===========================

In :ref:`statistics_panel_layout` you can see the main information retrieved by each entity.
This panel shows a summary of the data retrieved by the entity that is clicked.
In this case, you could only see those data that the entities are publishing, and so the rest of the *DataKinds* that
are related with the topics that we are not using will remain without data.

.. figure:: /rst/figures/screenshots/usage_example/summary.png
    :align: center

Change entity alias
===================

In order to make the user experience easier, there is a possibility to change the name of an specific entity.
We are going to change the name of the *DomainParticipant* that contains the publisher.
For that, just do right click over the entity name and a dialog will open.

.. todo::

    .. .. figure:: /rst/figures/screenshots/usage_example/alias_dialog.png
    ..     :align: center

Set the new alias that you want for this entity.
From now on this name will be used all along the monitor.

.. todo::

    .. .. figure:: /rst/figures/screenshots/usage_example/alias_dialog.png
    ..     :align: center

.. note::

    Be aware that this changes the alias of the entity inside the monitor, and does not affect to the real DDS network.


Create Series Chart
===================

This section describes how to graphically represent the data that is being monitored.

Data Count Plot
---------------

This section explains how to represent the data being monitored and retrieved by the DDS entities.
First of all, click in :ref:`display_historical_data_button`.
This will open a Dialog where you should choose one of the topics in which you want to see the data collected.
The :code:`DATA_COUNT` has been chosen for this tutorial.

.. figure:: /rst/figures/screenshots/usage_example/new_series_data_count.png
    :align: center

Once done this, a new Dialog will open asking you to configure the series that is going to be displayed.
In the case of :code:`DATA_COUNT`, the data belongs to the *DataWriter*, and so you should choose this entity in the
:code:`Source Entity Id:` checkbox.
The :code:`Number of bins` is the number of points in which our data is going to be stored.
In our case, we are going to use :code:`20` bins.
Selecting the :code:`Default initial timestamp` as the :code:`Start time`, the initial timestamp shall be the time at
which the monitor was executed.
Using :code:`Now` in option :code:`End time` will get all the data available until the moment the chart is created.
Now for the :code:`Statistics kind` option, we are going to use :code:`SUM` as we want to know the number of
data sent in each time interval.

.. figure:: /rst/figures/screenshots/usage_example/data_count_configuration.png
    :align: center

Clicking :code:`Apply` the series will be created in the main window, but the Dialog will no close.
This is very useful in order to create a new series similar to the one already created.
Here we are going to reuse all the information but we are going to change the :code:`Number of bins` to :code:`0`.
Using the value :code:`0` means that we want to see all the different *datapoints* that the writer has stored.
Be aware that option :code:`Statistics kind` do not have effect when :code:`Number of bins` is :code:`0`.
Then, click :code:`OK` and now you should be able to see both series represented in the :code:`DATA_COUNT` window.

.. figure:: /rst/figures/screenshots/usage_example/data_count_chart.png
    :align: center

In this new chart created, you could see in the blue series the total amount of data packages sent in each time
interval.
Each points means that from that timestamp until the timestamp of next point the publisher sent :code:`24/25` messages.
The green series reports that this data has been sent periodically by the publisher each time
it had updated the number of data sent.

Here you could appreciate that the beginning of the chart is empty.
This is because the monitor has started before the publisher, and so there are some data at the beginning of the
time displayed that does not exist.

Latency Plot
-------------

Next, you are going to see how to represent the latency between these *DomainParticipants*.
First, click in :ref:`display_historical_data_button`.
This will open a Dialog where you should choose one of the topics in which you want to see the data collected.
For this case, we will choose :code:`FASTDDS_LATENCY`.
This data is called like this because it represents the time elapsed between the user call :code:`write` function
and the reader in the other endpoint receives it in the user callback.
For the network latency there is other topic named :code:`NETWORK_LATENCY`. However our endpoints are not storing
neither publishing this type of data, and so it can not be monitored.

Once done this, a new Dialog will open asking to configure the series that is going to be displayed.
In the case of :code:`FASTDDS_LATENCY` the data to show is related with two entities.
In our example we are going choose both *DomainParticipants*, and this will give us all the latency between the
*DataWriters* of the first participant and the *DataReaders* of the second one.

For simplicity, we will use the same bins, start time, and end time configuration parameters as in the previous example.

.. figure:: /rst/figures/screenshots/usage_example/fastdds_latency_configuration.png
    :align: center

Now for the :code:`Statistics kind` option, we are going to use some of them in order to see more than one series of
statistical data.
Change the :code:`Statistics kind` and click :code:`Apply` for each of them in order to create a series for each one.
The statistic kinds that we are going to use for this example are:

* :code:`MEDIAN` (blue series)
* :code:`STANDARD_DEVIATION` (green series)
* :code:`MIN` (yellow series)
* :code:`MAX` (purple series)

.. figure:: /rst/figures/screenshots/usage_example/fastdds_latency_chart.png
    :align: center

It is worth mentioning that the series name, its color, the axis, and some features of the chart box could be changed
as mention in :ref:`chartbox`.
