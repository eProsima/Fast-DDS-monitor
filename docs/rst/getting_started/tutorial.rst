.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _start_tutorial:

################
Example of usage
################

This example will show how to monitor a DDS network using *Fast DDS Monitor* and how to understand the different
application features and configurations.

.. _fastdds-with-statistics:

*******************************
Fast DDS with Statistics module
*******************************

In order to show the *Fast DDS Monitor* application running and monitoring a real DDS network, this tutorial uses a
*Fast DDS* example to create a simple and understandable DDS network.
The example proposed by this tutorial uses the :code:`hello_world` example of *Fast DDS* repository.

In order to execute this minimum DDS scenario where each entity publishes its statistical data, follow these steps:

#. Compile *Fast DDS* library with CMake option :code:`COMPILE_EXAMPLES` to build the examples
   (:code:`-DCOMPILE_EXAMPLES=ON`).
#. Have *Fast DDS Monitor* installed or a working environment with *Fast DDS*, *Fast DDS Statistics Backend* and
   *Fast DDS Monitor* built.
#. Use the environment variable :code:`FASTDDS_STATISTICS` to activate the statistics writers in the DDS execution (see
   following section).

For further information about the Statistics configuration, please refer to
`Fast DDS statistics module <https://fast-dds.docs.eprosima.com/en/latest/fastdds/statistics/statistics.html>`_.
For further information about installation of the Monitor and its dependencies, please refer to the documentation
section :ref:`installation_manual_linux` or :ref:`developer_manual_installation_sources_linux`.

.. _hello_world_example:

Hello World Example
===================

For this tutorial, the *Fast DDS* :code:`hello_world` example is used to create a simple DDS network to be monitored.
Below are the commands executed in order to run this network.
Note that this tutorial does not start with this DDS network running, and it is instead executed once the monitor
has been started.
This does not change the Monitor behavior, but would change the data and information shown by the application.

#.  Execute a *Fast DDS* :code:`hello_world` **subscriber** with statistics data active.

    .. code-block:: bash

        export FASTDDS_STATISTICS="HISTORY_LATENCY_TOPIC;NETWORK_LATENCY_TOPIC;\
        PUBLICATION_THROUGHPUT_TOPIC;SUBSCRIPTION_THROUGHPUT_TOPIC;RTPS_SENT_TOPIC;\
        RTPS_LOST_TOPIC;HEARTBEAT_COUNT_TOPIC;ACKNACK_COUNT_TOPIC;NACKFRAG_COUNT_TOPIC;\
        GAP_COUNT_TOPIC;DATA_COUNT_TOPIC;RESENT_DATAS_TOPIC;SAMPLE_DATAS_TOPIC;\
        PDP_PACKETS_TOPIC;EDP_PACKETS_TOPIC;DISCOVERY_TOPIC;PHYSICAL_DATA_TOPIC;\
        MONITOR_SERVICE_TOPIC"

        ./build/fastdds/examples/cpp/hello_world/hello_world subscriber

    where :code:`subscriber` argument creates a *DomainParticipant* with a *DataReader* in the topic
    :code:`hello_world_topic` in *Domain* :code:`0`.

#.  Execute a *Fast DDS* :code:`hello_world` **publisher** with statistics data active.

    .. code-block:: bash

        export FASTDDS_STATISTICS="HISTORY_LATENCY_TOPIC;NETWORK_LATENCY_TOPIC;\
        PUBLICATION_THROUGHPUT_TOPIC;SUBSCRIPTION_THROUGHPUT_TOPIC;RTPS_SENT_TOPIC;\
        RTPS_LOST_TOPIC;HEARTBEAT_COUNT_TOPIC;ACKNACK_COUNT_TOPIC;NACKFRAG_COUNT_TOPIC;\
        GAP_COUNT_TOPIC;DATA_COUNT_TOPIC;RESENT_DATAS_TOPIC;SAMPLE_DATAS_TOPIC;\
        PDP_PACKETS_TOPIC;EDP_PACKETS_TOPIC;DISCOVERY_TOPIC;PHYSICAL_DATA_TOPIC;\
        MONITOR_SERVICE_TOPIC"

        ./build/fastdds/examples/cpp/hello_world/hello_world publisher --samples 0

    where :code:`publisher` argument creates a *DomainParticipant* with a *DataWriter* in the topic
    :code:`hello_world_topic` in *Domain* :code:`0`.
    The following arguments indicate this process to run until the user press :code:`enter` (:code:`0` samples)
    and to write a message every tenth of a second (:code:`100` milliseconds period).

The environment variable :code:`FASTDDS_STATISTICS` activates the statistics writers for a *Fast DDS*
application execution.
This means that the *DomainParticipants* created within this variable will report the statistical data related
to them and their sub-entities.

Please refer to
`Fast DDS documentation <https://fast-dds.docs.eprosima.com/en/latest/fastdds/statistics/dds_layer/topic_names.html>`_
for further information about the available statistical topics.

**************************
Fast DDS Monitor Execution
**************************

The following section presents a complete *Fast DDS Monitor* execution, monitoring a real DDS network.

Initial Window
==============

The Monitor starts with no DDS entities running.
First of all, the *Fast DDS Monitor* initial window is shown.
Press :code:`Start monitoring!` in order to enter the application and start the monitoring.

.. thumbnail:: /rst/figures/screenshots/main.png
    :align: center

Initiate monitoring
===================

Once in the application, the first dialog that appears asks the user to enter a domain to begin monitoring it.
Monitoring a domain means to listen in that domain for DDS entities that are running and reporting statistical data.
Please refer to section :ref:`monitor_domain` for further information.

First, the :code:`Cancel` button is pressed so the user can see around the monitor and check its configurations,
but no entities or data will be shown as there are no domains being monitored.
You can always return to the :ref:`initialize_monitoring` dialog from :ref:`application_menu_file`.

Let's initialize monitoring in **domain 0** and pressing :code:`OK`.

.. thumbnail:: /rst/figures/screenshots/usage_example/Init_domain.png
    :align: center

Add physical and logical panels
===============================

By default, the Monitor only displays the DDS panel which lists the DDS entities together with their configuration
and available statistics information.
In order to open the logical and the physical panels, click on the top right corner of the
:ref:`left_panel`, in button :code:`···` and add all the panels to visualize the whole information.

.. thumbnail:: /rst/figures/screenshots/usage_example/Add_panels.png
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
topic :code:`hello_world_topic` in domain :code:`0` following the steps given in :ref:`hello_world_example`.
Once the subscriber is running our window will update and you could see new information in the left sidebar.

.. thumbnail:: /rst/figures/screenshots/usage_example/Execute_subscriber.png
    :align: center

First of all, the number of entities discovered has increased.
Now, you have a *DomainParticipant* called :code:`RTPSParticipant`, holding a *DataReader* called
:code:`hello_world_topic_0.0.1.4`.
This *DataReader* has a locator, which will be the *Shared Memory Transport* locator.
That is because the Monitor and the *DomainParticipant* are running in the same host, and so they communicate using
the `Shared Memory Transport (SHM) protocol
<https://fast-dds.docs.eprosima.com/en/latest/fastdds/transport/shared_memory/shared_memory.html>`_.

You should be able to see as well that now *Host* exists, with a *User* and a *Process* where :code:`RTPSParticipant`
is running.
This information is retrieved by the *DomainParticipant* thanks to activating the :code:`PHYSICAL_DATA_TOPIC`.
There is also a new *Topic* :code:`hello_world_topic` under *Domain* :code:`0`.

Double-clicking any entity name shows its specific information, such as name, backend id, QoS, etc.

.. thumbnail:: /rst/figures/screenshots/usage_example/Information_subscriber.png
    :align: center

Execute publisher
=================

The next step is to execute a publisher in topic :code:`hello_world_topic` in domain :code:`0`,
following the steps given in :ref:`hello_world_example`.
Once the publisher is running you will see that new entities have appeared.
Specifically, a new *DomainParticipant* also called :code:`RTPSParticipant` with a *DataWriter*
:code:`hello_world_topic_0.0.1.3` and, in the case that this publisher has been executed from same
*Host* and *User*, there will be a new *Process* that represents the process where this new :code:`RTPSParticipant`
is running.

.. thumbnail:: /rst/figures/screenshots/usage_example/Information_publisher.png
    :align: center

Domain View
===========

Now that we have both our publisher and subscriber in execution, we can check the configuration of the DDS network
that has just been created. Click on *Domain View* in the :ref:`chart_panel_index` to open the Domain display. In
this tab, we can see a graph describing the structure of our network: our single Host contains our single User,
which in turn contains both our Processes. Each Process is related to one of our Participants, either the publisher
or the subscriber. It's easy to distinguish them in this view: with the vertical line representing our Topic, the
publisher contains the DataWriter, represented with an arrow that feeds into the Topic, while the subscriber contains
the DataReader, represented with an arrow coming from the Topic.

.. thumbnail:: /rst/figures/screenshots/usage_example/Domain_view.png
    :align: center

In this view, we have access to different functionalities, including filtering by Topic (right-click over the Topic
name, and choose *Filter topic graph*, opening the filtered graph in a new Tab). Additionally, we can access the IDL
representation of any of the Topics, by pressing right-click over the Topic name, and choosing *Data type IDL view*.
This opens a new Tab with the required information, which can be copied and pasted.

.. thumbnail:: /rst/figures/screenshots/usage_example/IDL_img_tutorial.png
    :align: center

Since we're not going to be using these Tabs anymore, click on the *X* to close all Tabs and return to the
:code:`New Tab` view.

Summary of Statistical Data
===========================

In :ref:`statistics_panel_layout` you can see the main information retrieved by each entity.
This panel shows a summary of the data retrieved by the entity that is clicked.
In this case, you could only see the data that the entities are publishing, and the rest of *DataKinds* that
are related to the topics that we are not using will remain without data.

.. thumbnail:: /rst/figures/screenshots/usage_example/Summary.png
    :align: center

.. _change_alias:

Change entity alias
===================

In order to make the user experience easier, it is allowed to change the name of any specific entity.
Change the name of our *Publisher* and *Subscriber* *DomainParticipants*, as well as our *DataReader*
and *DataWriter*, to make them easier to identify. For that, right-click the entity name and select **Change alias**.

.. thumbnail:: /rst/figures/screenshots/usage_example/Alias_dialog.png
    :align: center

Set the new alias that you want for these entities.
From now on this name will be used all along the monitor.

.. note::

    Be aware that this changes the alias of the entity inside the monitor, and does not affect to the real DDS network.

Create Historic Series Chart
============================

This section describes how to graphically represent the data reported by a DDS network.

Data Count Plot
---------------

This section explains how to represent the data being monitored and retrieved by the DDS entities.
First of all, click *Chart View* in the :ref:`chart_panel_index` to open the graph display. Then, go to
*Edit->Display Historical Data*. This will open a Dialog where you should choose one of the topics
in which you want to see the data collected. The :code:`DATA_COUNT` has been chosen for this tutorial.

.. thumbnail:: /rst/figures/screenshots/usage_example/New_series_data_count.png
    :align: center

Once done, a new Dialog will open asking you to configure the series that is going to be displayed.
In the case of :code:`DATA_COUNT`, the data belongs to the *DataWriter*, and so you should choose this entity in the
:code:`Source Entity Id:` checkbox.
The :code:`Number of bins` is the number of points in which our data is going to be stored.
In our case, we are going to use :code:`20` bins.
Selecting the :code:`Default initial timestamp` as the :code:`Start time`, the initial timestamp shall be the time at
which the monitor was executed.
Using :code:`Now` in option :code:`End time` will get all the data available until the moment the chart is created.
Now for the :code:`Statistics kind` option, we are going to use :code:`SUM` as we want to know the amount of
data sent in each time interval.

.. thumbnail:: /rst/figures/screenshots/usage_example/Data_count_configuration.png
    :align: center

Clicking :code:`Add` the series will be created in the main window, but the dialog will not close.
This is very useful in order to create a new series similar to the one already created.
Here we are going to reuse all the information but we are going to change the :code:`Number of bins` to :code:`0`.
Using the value :code:`0` means that we want to see all the different *datapoints* that the writer has stored.
Be aware that option :code:`Statistics kind` do not have effect when :code:`Number of bins` is :code:`0`.
Then, click :code:`Add & Close` and now you should be able to see both series represented in the :code:`DATA_COUNT`
window.

.. thumbnail:: /rst/figures/screenshots/usage_example/Data_count_chart.png
    :align: center

In this new chart created, you could see in the blue series the total amount of data packages sent in each time
interval.
The green series reports that this data has been sent periodically by the publisher.

Latency Plot
-------------

Next, you are going to see how to represent the latency between these *DomainParticipants*.
First, go to *Edit->Display Historical Data*.
This will open a Dialog where you should choose one of the topics in which you want to see the data collected.
For this case, we will choose :code:`FASTDDS_LATENCY`.
This data is called like this because it represents the time elapsed between the user calls the  :code:`write` function
and the reader in the other endpoint receives it in the user callback.
For the network latency there is another topic named :code:`NETWORK_LATENCY`. However our endpoints are neither storing
nor publishing this type of data, and so it cannot be monitored.

Once done, a new Dialog will open asking to configure the series that is going to be displayed.
In the case of :code:`FASTDDS_LATENCY` the data to show is related to two entities.
In our example we are going to choose both *DomainParticipants*, and this will give us all the latency between the
*DataWriters* of the first participant and the *DataReaders* of the second one.

For simplicity, we will use the same bins, start time, and end time configuration parameters as in the previous example.

.. thumbnail:: /rst/figures/screenshots/usage_example/Latency_configuration.png
    :align: center

Now for the :code:`Statistics kind` option, we are going to use some of them in order to see more than one series of
statistical data.
Change the :code:`Statistics kind` and click :code:`Apply` for each of them in order to create a series for each one.
The statistic kinds that we are going to use for this example are:

* :code:`MEDIAN` (blue series)
* :code:`MAX`  (green series)
* :code:`MIN` (yellow series)
* :code:`STANDARD_DEVIATION` (purple series)

.. thumbnail:: /rst/figures/screenshots/usage_example/Latency_chart.png
    :align: center

The series name, color, axes, and other chart properties can be changed as mentioned in :ref:`chartbox`.

.. _tutorial_create_dynamic_series:

Create Dynamic Series Chart
===========================

This section describes how to graphically represent data of a running DDS network in real-time.

Periodic Latency Plot
---------------------

This section explains how to represent the FastDDS latency in real-time between the publisher and
the subscriber.
First of all, click in |dynamic_chart|.
This will open a Dialog where you should choose one of the topics in which you want to see the data collected.
For this case, choose :code:`FASTDDS_LATENCY`.
Set a :code:`Time window` of 1 minute.
This means you will be able to see the data of the last minute of the network.
Finally, set an :code:`Update period` of 5 seconds.
This will query for new data every 5 seconds and retrieve and display it in the chart.

.. thumbnail:: /rst/figures/screenshots/usage_example/New_dynamic_series_latency.png
    :align: center

After this, a new Dialog will open asking to configure the series that is going to be displayed.
In the case of :code:`FASTDDS_LATENCY` the data to show is related with two entities.
In our example we are going choose our *Host*.
This will retrieve the latency measured in the communication between the entities of this host to itself.
For this case, it is going to be the latency between the two participants, but this trick is very useful when
you want to filter latency between two specific hosts or even to collect all the latency in the same domain.

Now for the :code:`Statistics kind` option, we are going to use some of them in order to see more than one series of
statistical data.
Change the :code:`Statistics kind` and click :code:`Apply` for each of them in order to create a series for each one.
The statistic kinds that we are going to use for this example are:

* :code:`MEAN` (blue series)
* :code:`MAX` (green series)
* :code:`MIN` (yellow series)

.. thumbnail:: /rst/figures/screenshots/usage_example/Dynamic_latency_configuration.png
    :align: center

This chart will be updated each 5 seconds, displaying the data collected by the monitor within the last 5 seconds.
The axis are updated periodically, and so the zoom and chart move is not available in this kind of charts while
running.
For this purpose, the *play/pause* button stops the axis's update, allowing to zoom and move along the chart.
Be aware that pausing the chart does not stop new points from appearing, as every 5 seconds the update of the data will
still happen.

.. thumbnail:: /rst/figures/screenshots/usage_example/Dynamic_latency_chart.png
    :align: center

Latency DataPoints
------------------

There is a special feature for real-time data display that allows to see every *DataPoint* received from the DDS
entities monitored (similar to :code:`bins 0` in historic series).
In order to see this data in real-time, add a new series in this same chartbox in *Series->Add series*.
Choose again the *Host* as source and target and choose :code:`RAW_DATA` as :code:`Statistics kind`.

Now you should be able to see a new series in purple that represents each of the
*DataPoints* sent by the DDS entities and collected by the monitor in the last 5 seconds.
This is very helpful to understand the :code:`Statistics kind`.
As you can see, the :code:`MEAN`, :code:`MAX` and :code:`MIN` in each interval are calculated with these *DataPoints*.

.. thumbnail:: /rst/figures/screenshots/usage_example/Dynamic_all_latency_chart.png
    :align: center

It is worth mentioning that dynamic series can be configurable, just like historic series.
The label and color of each series are mutable, and the chart could zoom in and out and move along the axis
while paused.

Set alert to watch events
============================

This section describes how to create alerts to watch specific events in the monitored DDS network. First, click on
the *Alerts* tab (marked with a bell icon) in the left panel to open the Alerts view. In this tab, you can see a list
of all the defined alerts.

.. thumbnail:: /rst/figures/screenshots/usage_example/alert_panel_pre.png
    :align: center

Click on the *+* button to create a new alert. This will open a dialog where you can configure the alert.

.. thumbnail:: /rst/figures/screenshots/usage_example/alert_dialog.png
    :align: center

In this dialog, you can set the name of the alert, its type, the domain to monitor and the conditions for triggering the alert.

In general, all alerts filter the triggering entities using the fields `host`, `user` and `topic`. If any of these fields are left empty
or the `ALL` option is selected, all entities will be compliant with that part of the filter. Note that the filter does not act like a regular expression,
but like a simple equality check between strings. Note also that all 3 conditions must be met for an entity to be compliant with the alert filter.

If the alert type is *NEW_DATA*, the alert will be triggered when a positive `DATA_COUNT` is received from any entity that matches the fields
`host`, `user` and `topic`.

If the alert type is *NO_DATA*, the alert will be triggered when a `PUBLICATION_THROUGHPUT` message is received from any entity that matches
the fields `host`, `user` and `topic` and its value is lower than `threshold`.

If a timeout period is defined, the alert will trigger a timeout message with this periodicity. `NEW_DATA` alerts don't support timeout due to
their event-driven nature. However, the user can define a more relaxed polling time to collect timeout messages in the `Edit->Alerts Configuration` option
from the upper menu.

Finally, if a script is provided, it will be executed every time the alert is triggered. Note that the script must have executable permissions in the
host OS.

Once the alert is set up, it will appear in the list of alerts and its metadata will be shown below when clicked.

.. thumbnail:: /rst/figures/screenshots/usage_example/alert_panel_post.png
    :align: center

To remove an alert, just right-click on it and choose the `Remove` option.

.. _pro_features_tutorial:

**************************
Fast DDS Monitor |Pro|
**************************

*Fast DDS Monitor Pro* includes all the features of the open-source edition - everything
demonstrated in the previous sections of this tutorial works in Pro exactly the same way.
The sections below walk through the features that are exclusive to *Fast DDS Monitor Pro*.

To showcase these capabilities a richer DDS network is needed than the minimal ``hello_world``
example.
The main scenario in this tutorial uses the *eProsima Shapes Demo*, a graphical application that
publishes and subscribes to colored geometric shapes on named DDS topics (``Square``, ``Circle``,
``Triangle``).
Each shape sample carries four fields: ``color`` (a string), ``x``, ``y``, and ``shapesize``
(integers), which are ideal for live charts, spy views, and scatter plots.
A separate scenario at the end of this section demonstrates the :ref:`image_pane`.

.. _shapes_demo_scenario:

Shapes Demo Scenario
====================

*eProsima Shapes Demo* is available at `https://github.com/eProsima/ShapesDemo
<https://github.com/eProsima/ShapesDemo>`_.
Follow the build and installation instructions in that repository before continuing.
Once installed, two instances are needed to create the network used in this tutorial.

#. Open a terminal, source the *eProsima Shapes Demo* installation, and launch the first
   instance:

   .. code-block:: bash

       source ~/shapes_demo_ws/install/setup.bash
       ShapesDemo

   In the Shapes Demo GUI, go to **Options → Participant Configuration** and make sure the
   **Active statistics** toggle is enabled (it is on by default) so the participant reports
   statistical data to the monitor.
   Then click **Publish** and create a **Square** publisher.
   Click **Publish** again and create a **Circle** publisher.

#. Open a second terminal and launch a second instance:

   .. code-block:: bash

       source ~/shapes_demo_ws/install/setup.bash
       ShapesDemo

   In this second GUI, make sure **Active statistics** is enabled the same way under
   **Options → Participant Configuration**.
   Then click **Subscribe** and create a **Square** subscriber.

The DDS network now has three active endpoints on domain :code:`0`: a Square publisher and a
Circle publisher in the first instance, and a Square subscriber in the second.
Keep both Shapes Demo windows open throughout the tutorial.

.. thumbnail:: /rst/figures/screenshots/shapes_demo_pro.png
    :align: center

.. _pro_monitor_launch:

Fast DDS Monitor Pro Execution
================================

Start *Fast DDS Monitor Pro*.
The start screen appears; press **Start monitoring!** to enter the main interface.

.. figure:: /rst/figures/screenshots/main_pro.png
    :align: center

Initiate Monitoring
===================

Once in the application, the initialization dialog asks you to select a monitoring mode.
The Shapes Demo processes are running on domain :code:`0`.
Select **DDS Domain**, enter :code:`0`, and click **OK**.

.. figure:: /rst/figures/screenshots/init-monitor_pro.png
    :align: center

The monitor starts discovering entities.
After a few seconds the **Explorer Panel** on the left shows the participants, writers, and reader
created by the two Shapes Demo instances.
Open all sub-panels by clicking the :code:`···` button in the top-right corner of the Explorer
Panel.
The topics ``Square`` and ``Circle`` appear in the Logical panel under domain :code:`0`, and the
host, users, and two processes appear in the Physical panel.

.. figure:: /rst/figures/screenshots/explorer_pro.png
    :align: center

Explore the Domain View
=======================

Click **Domain View** in the main panel selector, or go to **Add → Add Domain View**, to see
the DDS network as an interactive graph.

.. figure:: /rst/figures/screenshots/domain_pro.png
    :align: center

The graph shows both Shapes Demo processes as boxes inside the host.
Each process contains its participant.
The ``Square`` topic line runs vertically with a DataWriter arrow from the first process feeding
into it and a DataReader arrow from the second process coming out - the full publish-subscribe
connection is visible at a glance.
The ``Circle`` topic line shows only a DataWriter arrow from the first process; it has no
subscriber yet, so no reader arrow appears.

Right-click the ``Square`` topic line and choose **Data type IDL view** to open an IDL pane
showing the ``ShapeType`` definition - the ``color``, ``x``, ``y``, and ``shapesize`` fields are
all visible.
Close the IDL pane once you have inspected it.

.. figure:: /rst/figures/screenshots/domain_idl_pro.png
    :align: center
    :width: 300px

Right-click the ``Square`` topic line and choose **Filter topic graph** to open a filtered view
showing only the entities connected to that topic.
A new tab opens with the Square publisher and subscriber - the Circle publisher is not shown
since it is not related to the Square topic.
Close the filtered tab and return to the full domain view.

.. figure:: /rst/figures/screenshots/filter_topic_pro.png
    :align: center
    :width: 400px

Now let's explore the visibility controls.
Click the |gear| button in the Domain View pane header.
The configuration panel opens on the right and shows **DOMAIN GRAPH** at the top.
The panel lists all entities grouped into seven collapsible sections: **TOPICS**, **HOSTS**,
**USERS**, **PROCESSES**, **PARTICIPANTS**, **DATAWRITERS**, and **DATAREADERS**.
Each section header shows a visible/total count.

**Hiding a process and its descendants**

Expand the **PROCESSES** section.
You will see the two Shapes Demo processes listed by their process ID or alias.
Clear the checkbox next to one of them.
That process disappears from the graph immediately - and so does everything it contained:
its participant, the participant's DataWriter or DataReader, and the locators associated with
them.
This is the container behavior: hiding a parent entity hides all its descendants automatically.
Re-check the process to bring all its entities back at once.

**Hiding and showing individual topics**

Expand the **TOPICS** section.
Both ``Square`` and ``Circle`` are listed.
Clear the checkbox next to ``Circle``.
The Circle topic line vanishes from the graph along with its DataWriter arrow; the ``Square``
part of the graph is unaffected.
Re-check ``Circle`` to restore it.

Use the **Filter entities...** search box at the top of the panel to find any entity by name
quickly when the list is long.

**Showing metatraffic**

By default metatraffic is hidden.
Go to **View → Hide/Show Metatraffic** to make it visible.
A large number of new topic lines and endpoints appear in the graph - these are the internal
statistics topics produced by the statistics module.
Toggle the same menu item again to hide metatraffic and return to the clean graph.

.. figure:: /rst/figures/screenshots/statistics_filter_pro.png
    :align: center

To restore all manually hidden entities at once, use the **ACTIONS** button in the configuration
panel and choose **Show All Entities**.

Topics Panel
============

Click the |topic_icon| icon in the vertical icon bar on the far left of the window to open the
**Topics Panel**.
All discovered topics are listed here - ``Square`` and ``Circle`` are visible, together with the
statistics metatraffic topics produced by the *Fast DDS* statistics module.

Click the small arrow next to ``Square`` to expand it.
The fields of ``ShapeType`` are listed: ``color``, ``x``, ``y``, and ``shapesize``.
The numeric fields ``x``, ``y``, and ``shapesize`` are interactive leaf nodes - they can be dragged
onto an open chart to add a new series, or right-clicked to plot immediately.

.. figure:: /rst/figures/screenshots/topics_square_pro.png
    :align: center
    :width: 400px

Spy a Topic
===========

Right-click ``Square`` in the **Topics Panel** and select **Spy topic data**.
A Spy Topic View pane opens and immediately starts receiving live samples from the Square
publisher.

.. figure:: /rst/figures/screenshots/spy_square_pro.png
    :align: center
    :width: 400px

Use the |play| / |pause| button in the pane header to pause or resume the live feed without
closing the pane.
While paused, the last received sample stays visible for inspection.

Split Panes
===========

*Fast DDS Monitor Pro* can hold several views side by side within the same monitor tab.
With the Spy pane already open, let's split it to place a chart alongside it.

Click the **...** (three-dots) button in the Spy pane header and hover over **Split right**.
A submenu appears listing all available pane types — select **Topic Charts** to open a
Time Series Topic Chart to the right of the Spy pane.

.. figure:: /rst/figures/screenshots/resize_pro.png
    :align: center
    :width: 470px

Drag the vertical divider between the panes to resize them as needed.
The configuration panel opens automatically for the newly opened chart.

Up to six panes can be open in a single tab at the same time.

Plot a Topic Live Chart
=======================

With the Time Series Topic Chart pane open alongside the Spy pane, let's configure it to track
the Square's position.
The configuration panel already shows **TIME SERIES CHART** at the top.

Notice the **PLOT MODE** row: it has two buttons, **Time Series** and **XY Chart**, that switch
this pane between the two chart types.
Make sure **Time Series** is selected.

Under **PANE SETTINGS**:

* **Domain** -- :code:`Domain 0`.
* **Time window** -- :code:`60` seconds, so the last minute of data is visible.
* **Max points** -- leave at :code:`500`.
* Click **Apply & Reset Chart**.

Under **CHART NAME**, type ``Square Position`` to label this chart.

Click **Add Series** in the **SERIES** section.
The inline form expands: type ``Square`` in the **Filter topics** box.
Select ``Square`` and wait a moment for the first sample to arrive - the field list populates with
``color``, ``x``, ``y``, and ``shapesize``.
Click ``x`` and then click **Add Series** (or double-click ``x``) to add it.
Repeat and add ``y`` as a second series.

.. figure:: /rst/figures/screenshots/topic_time_series_pro.png
    :align: center

The chart now shows both the horizontal and vertical position of the square updating live as the
shape bounces around the canvas.
Under **DISPLAY**, enable **Show legend** to see the series names alongside their line colors.

You can also add series without using the configuration panel:

* **From the Topics Panel** - expand ``Square`` in the **Topics Panel** and drag the ``shapesize``
  leaf directly onto the chart; a third series appears immediately.
* **From the Spy pane** - right-click the ``x`` field in the Spy pane and select **Plot field**
  to open a new chart for that field, or drag any numeric leaf from the sample tree onto an
  already-open chart to add it as a new series.

Click |resize| **Reset View** in the chart header at any time to return both axes to their
default range after zooming or panning.

Plot an XY Chart
================

A Time Series chart shows each value changing over time.
To see the shape's trajectory - plotting ``x`` against ``y`` - switch to XY Chart mode.

Click |gear| in the ``Square Position`` chart header to open the configuration panel.
Click the **XY Chart** button in the **PLOT MODE** row.
The chart clears and the settings update for XY mode.

Under **PANE SETTINGS**:

* **Domain** -- :code:`Domain 0`.
* **Max points** -- :code:`150` to keep the scatter plot readable.
* Click **Apply & Reset Chart**.

Click **Add XY Series** in the **SERIES** section:

* **X Axis Topic** -- select ``Square``; **X Field** -- select ``x``.
* **Y Axis Topic** -- select ``Square``; **Y Field** -- select ``y``.
* Click **Add XY Series**.

.. figure:: /rst/figures/screenshots/xy_pro.png
    :align: center

The scatter plot shows every position where the shape has been during the last :code:`200` samples.
As the Shapes Demo keeps running, new points appear and old ones drop off once the buffer is full.
Because the shape bounces between the edges of the canvas, the point cloud outlines the boundaries
of the Shapes Demo window as a rectangle.

When X and Y values come from different topics, each new X sample is paired with the most recent
Y value, making it possible to plot correlations between any two numeric fields in the same domain.

Statistics Charts
=================

Beyond raw topic values, *Fast DDS Monitor Pro* can also visualize pre-computed DDS statistics.
Let's add a live publication throughput chart for the Square publisher.

Click |dynamic_chart| in the shortcuts toolbar, or go to **Add → Add Statistics Chart**.
A new chart pane opens and the configuration panel shows **STATISTICS CHART** at the top.

Under **PANE SETTINGS**:

* **Chart type** -- select *Live (real-time)*.
* **Data kind** -- choose :code:`PUBLICATION_THROUGHPUT`.
* **Time window** -- :code:`120` seconds.
* **Update period** -- :code:`5` seconds.
* Click **Apply & Restart**.

Click **Add Series** in the **SERIES** section.
The inline form expands with a **Source entity** selector.
Choose the Square publisher participant as the source entity.
Select :code:`MEAN` for **Statistics kind** and click **Add Series**.

.. figure:: /rst/figures/screenshots/statistics_charts_pro.png
    :align: center

The series appears in the chart and updates every five seconds, showing the mean publication
throughput of the Square publisher over time.
Under **CHART NAME**, rename this chart to ``Throughput`` to make it easy to identify later.

Under **AXES**, enable **Lock Y axis** to keep the vertical scale stable.
Under **ACTIONS**, click **Export to CSV** at any time to save the chart data to a file for
offline analysis.

Publish Topic Data
==================

The *Publisher Pane* lets you inject custom DDS samples directly from the monitor - without
writing any code.
Let's publish a new ``Square`` shape and watch it appear in the Shapes Demo subscriber window.

Right-click ``Square`` in the **Topics Panel** and select **Publish topic data**.
A Publisher Pane opens and the configuration panel shows **PUBLISHER** at the top.

The **CURRENT TOPIC** section shows the topic name (``Square``), the domain (:code:`Domain 0`),
the resolved type name (``ShapeType``), the publisher status, and a samples-sent counter.

Click **Apply & Restart** to attach the publisher to the ``Square`` topic.
The pane body fills with an auto-generated form with one row per field in ``ShapeType``.
Click **Randomize** in the **ACTIONS** section of the configuration panel to fill all fields
with random valid values automatically.

.. figure:: /rst/figures/screenshots/publish_pro.png
    :align: center

Click **Publish once** (the blue button at the bottom of the pane body, or **Publish once** in
the **ACTIONS** section of the configuration panel) to send a single sample.
The samples-sent counter in **CURRENT TOPIC** increments to :code:`1`.
A shape with the randomized color, size, and position appears in the Shapes Demo instance that
has the Square subscriber for the duration of one message lifetime.

To publish a continuous stream, enable **Publish continuously** in the **CONTINUOUS** section of
the configuration panel and set **Interval** to :code:`100` milliseconds.
The shape stays refreshed at the same position for as long as continuous mode is active.
Click the toggle again to stop publishing.

Add a Second Monitor
====================

A notable feature of *Fast DDS Monitor Pro* is the ability to run several
independent monitors in the same window, each watching a different DDS environment.
The image publisher used in the next section runs on domain :code:`1`, so let's start it now
and add a second monitor tab for that domain.

#. Open a third terminal and start the image publisher on domain :code:`1`.

   The publisher starts sending image frames on the image topic in domain :code:`1`.

#. In *Fast DDS Monitor Pro*, open the **FIle** menu and select **Initialize DDS Monitor**.
   The initialization dialog appears.
   Enter :code:`1`, and click **OK**.

A second tab labeled with domain :code:`1` appears in the main panel area alongside the first.

.. figure:: /rst/figures/screenshots/2_monitors_pro.png
    :align: center

Click the domain :code:`1` tab to make it active.
The Explorer Panel, entity lists, and the **Topics Panel** switch to show the entities from the
second domain.
The image topic appears in the **Topics Panel** and the image publisher's
participant is listed in the Explorer Panel.
Click back to the domain :code:`0` tab in the logical panel and everything returns to the Shapes Demo network instantly.

Each monitor operates entirely independently: entity discovery and data collection continue in the
background regardless of which tab is currently visible.

View Live Image Data
====================

The *Image Pane* renders live image frames from a DDS topic directly inside the monitor.
The image publisher started in the previous section is already running on domain :code:`1`
and sending frames on the topic.

In the **Topics Panel**, right-click on the image topic and select **Open image view**.
Alternatively, click the **Image View** button shown in the empty pane placeholder.
A new Image Pane opens and the configuration panel shows **IMAGE VIEW** at the top.

Under **CHANGE TOPIC**, select **Domain 1** and pick your image topic from the list (the list shows only the image topics).
Click **Apply & Reload**.

.. figure:: /rst/figures/screenshots/image_pro.png
    :align: center

The pane starts displaying frames as soon as the first one arrives.
A metadata strip at the bottom of the pane shows the frame resolution, encoding, and a running
total frame count.

Use the |play| / |pause| button in the pane header to pause the stream.
When paused, the last received frame stays visible so you can inspect it.

Under **ACTIONS** in the configuration panel, click **Save Screenshot** to save the current frame
as a PNG file, or **Copy Screenshot** to copy it to the clipboard.

Save and Restore a Workspace
==============================

After spending time setting up monitors, pane layouts, charts, and alert rules, it would be a
waste to lose all that configuration when the application is closed.
*Fast DDS Monitor Pro* saves the complete session state to a workspace file and restores it
exactly on the next launch.

Click the |save| button in the toolbar at the top right of the window, or go to
**File → Save Workspace**.
A file dialog opens.
Navigate to a suitable folder, type a name such as ``shapes_tutorial``, and click **Save**.
The file is written with the ``.fdmw`` extension.

To verify that the restore works, go to **File → Load Workspace** and select the
``shapes_tutorial.fdmw`` file.
All monitor tabs, pane layouts, chart series, chart settings, alert rules, sidebar state, theme,
and toolbar visibility are restored exactly as they were.
Each monitor reopens in a waiting state and populates as the Shapes Demo processes are rediscovered.

.. note::

    The statistics database is not stored in the workspace file.
    Entity discovery and data collection restart fresh on load; panes populate as DDS traffic is
    received after the workspace is applied.

Switch Theme
============

*Fast DDS Monitor Pro* ships with **Light** and **Dark** themes.
Every part of the interface (panels, charts, icons, dialogs, the title bar, and the menu bar)
switches instantly when the theme is changed, with no restart required.

Go to **View → Theme** and select **Dark**, or use the |moon| / |sun| toggle in the shortcuts toolbar on the top right.

.. figure:: /rst/figures/screenshots/dark_image_pro.png
    :align: center

The entire application switches to the dark palette immediately.
Charts use the same ten-color series palette in both themes so existing series remain easily
distinguishable.
Node and edge colors in the Domain View adapt automatically; entity status colors (green for alive,
yellow for degraded, red for error) remain fixed so their meaning is always clear.

To revert, go to **View → Theme** and select **Light**.

The active theme is included in the workspace file and is restored the next time the
``shapes_tutorial.fdmw`` workspace is loaded.
