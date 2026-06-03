.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _start_tutorial:

######################
Example of usage |Pro|
######################

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

The following sections walk through the main *Fast DDS Monitor Pro* features using the same
``hello_world`` DDS network from the previous tutorial.

Add a Second Monitor
====================

*Fast DDS Monitor Pro* can run several monitors at the same time.
Each active monitor appears as a tab along the top edge of the main panel area.
Click any tab to make that monitor active; the left sidebar, entity lists, and panes all update to
show data for that monitor.

To add a second monitor, open the **Add** menu and select **Add Monitor**.
The initialization dialog appears — select **DDS Domain**, enter a different domain number such as
:code:`1`, and click **OK**.
A second tab labeled with the new domain appears alongside the first.

.. figure:: /rst/figures/screenshots/2_monitors_pro.png
    :align: center

.. .. thumbnail:: /rst/figures/screenshots/pro/add_monitor.png
    :align: center

Split Panes
===========

The main panel can show several views side by side within a single monitor tab.

Click the **...** (three-dots) button in the header of any existing pane and select
**Split right** or **Split down**.

.. figure:: /rst/figures/screenshots/split_pro.png
    :align: center
    :width: 400px

The new pane starts empty; click the |gear| button to open the configuration panel and choose what
type of view to display there.
Drag the divider line between panes to resize them.
Up to six panes can be open in a single tab at once.

.. figure:: /rst/figures/screenshots/tab_reordering_pro.png
    :align: center

.. .. thumbnail:: /rst/figures/screenshots/pro/dockable_panes.png
    :align: center

Statistics Charts
=================

Statistics charts in *Fast DDS Monitor Pro* are configured entirely through the right-side panel.

Click |historical_chart| or |dynamic_chart| in the shortcuts toolbar, or go to
**Add -> Add Statistics Chart**.
A new pane opens and the configuration panel slides in from the right showing
**STATISTICS CHART LIVE** (or HISTORICAL) at the top.

Under **PANE SETTINGS**:

* **Chart type** -- choose *Live (real-time)* or *Historical*.
* **Data kind** -- select the statistic to plot, for example :code:`FASTDDS_LATENCY`.
* **Time window** -- visible time range in seconds (for example :code:`120`).
* **Update period** (live) -- how often data is fetched, in seconds (for example :code:`5`).
* **Max points** -- maximum data points kept across all series. :code:`0` keeps everything.
* Click **Apply & Restart** to apply the settings.

Click **Add Series** in the **SERIES** section.
The inline form expands with entity and statistics kind selectors.
Pick the source entity, target entity, and statistics kind (:code:`MEDIAN`, :code:`MEAN`,
:code:`MAX`, :code:`MIN`, :code:`STANDARD_DEVIATION`, or :code:`SUM`), then click **Add Series**.
The panel stays open so you can add further series by changing parameters and clicking **Add Series**
again.

Under **CHART NAME**, edit the label shown in the pane header.

.. figure:: /rst/figures/screenshots/statistics_charts_pro.png
    :align: center

**Useful options:**

* **DISPLAY** -- toggle *Show legend*, *Show points*, or *Running* to pause/resume ingestion.
* **AXES** -- enable *Lock Y axis* or *Lock X axis* and set *min* / *max* to fix the range;
  click *Reset Zoom* to return to auto-fit.
* **ACTIONS** -- *Show All Series* / *Hide All Series*; *Export to CSV* saves chart data;
  *Save Screenshot* / *Copy Screenshot* captures the chart as an image.

.. .. thumbnail:: /rst/figures/screenshots/pro/statistics_chart.png
    :align: center

.. .. thumbnail:: /rst/figures/screenshots/pro/statistics_chart_config.png
    :align: center

Spy a Topic
===========

The *Spy Topic View* displays the live content of every message published on a topic.

Right-click :code:`hello_world_topic` in the **Topics** panel and select **Spy topic data**, or go
to **Add -> Add Spy Topic View**.
A new pane opens and the configuration panel shows **SPY VIEW** at the top.

Under **PANE SETTINGS**:

* Select a **Domain** from the dropdown and pick the topic from the filtered list.
* Click **Apply & Restart** to start the subscription.

Under **PLAYBACK**, toggle *Active (receiving messages)* to pause or resume the feed without
closing the pane.

Under **ACTIONS**: *Expand All* / *Collapse All* unfold or fold the entire sample tree; *Clear*
discards all received samples; *Copy JSON to Clipboard* copies the last sample.

Under **PANEL ACTIONS**: *Split right* / *Split down* open another pane alongside this one.

.. figure:: /rst/figures/screenshots/spy_pro.png
    :align: center

Each incoming sample appears in the pane as an expandable tree.
Click the arrow next to any struct field to expand it and see its sub-fields.
Numeric leaf fields (integers, floats, doubles) can be used further:

* **Right-click a numeric leaf field** and select **Plot field** to open a new Topic Live Chart
  for that field immediately.
* **Drag a numeric leaf field** onto an existing Topic Live Chart to add it as a new series,
  or drop it onto an empty area to create a new chart.

.. .. thumbnail:: /rst/figures/screenshots/pro/spy_pane.png
    :align: center

Plot a Topic Live Chart
=======================

The *Topic Live Chart* plots raw numeric values from any topic against time, updated live.

Right-click :code:`hello_world_topic` in the **Topics** panel and choose **Chart topic data**, or
go to **Add -> Add Topic Live Chart**.
A new chart pane opens and the configuration panel shows **TIME SERIES CHART** at the top.

A **PLOT MODE** row appears with two buttons -- **Time Series** and **XY Chart** -- that switch the
chart between the two modes without opening a new pane.

Under **PANE SETTINGS**:

* **Domain** -- select the domain (for example :code:`Domain 0`).
* **Time window** -- visible time range in seconds (for example :code:`120`).
* **Max points** -- maximum data points retained (default :code:`500`).
* Click **Apply & Reset Chart**.

Under **CHART NAME**, rename the chart if desired.

Click **Add Series** in the **SERIES** section:

* Use **Filter topics** to narrow the list and select :code:`hello_world_topic`.
* Wait for the first sample to arrive so fields populate, then select a numeric leaf field.
* Click **Add Series**, or double-click the field to add immediately.

You can also add series by dragging:

* **From the Spy Topic View** -- drag a numeric leaf field from the sample tree onto the chart.
* **From the Topics panel** -- drag a numeric leaf field from the topic tree in the left sidebar
  onto the chart.

.. figure:: /rst/figures/screenshots/topic_time_series_pro.png
    :align: center

**Useful options:**

* **DISPLAY** -- *Show legend*, *Show points*, *Running* (pause/resume ingestion).
* **AXES** -- *Lock Y axis* / *Lock X axis* with *min* / *max* fields; *Reset Zoom*.
* **ACTIONS** -- *Show All Series* / *Hide All Series*; *Clear Chart* removes all series;
  *Save screenshot* / *Copy screenshot to clipboard*.

.. .. thumbnail:: /rst/figures/screenshots/pro/topic_live_chart.png
    :align: center

Plot an XY Chart
================

An *XY Chart* plots two numeric fields against each other as a real-time scatter chart.
It shares the same pane type as the Topic Live Chart -- switch mode using the **PLOT MODE** buttons
in the configuration panel, or open a dedicated pane via **Add -> Add XY Chart**.

When **XY Chart** is selected in **PLOT MODE**, **PANE SETTINGS** shows:

* **Domain** -- select the domain.
* **Max points** -- maximum scatter points (default :code:`500`). No time window for XY.
* Click **Apply & Reset Chart**.

Click **Add XY Series** in the **SERIES** section:

* **X Axis Topic** + **X Field** -- select the topic and numeric field for the X axis.
* **Y Axis Topic** + **Y Field** -- select the topic and numeric field for the Y axis
  (can be the same topic as X).
* Click **Add XY Series**.

.. figure:: /rst/figures/screenshots/xy_pro.png
    :align: center

When X and Y come from different topics, each new X sample is paired with the most recent Y value.

**Useful options:**

* **DISPLAY** -- *Show legend*; *Show lines* draws lines between scatter points; *Running*.
* **AXES** -- *Lock Y axis* / *Lock X axis* with numeric *min* / *max*; *Reset Zoom*.
* **ACTIONS** -- *Show All Series* / *Hide All Series*; *Clear Chart*; *Save Screenshot*.

.. .. thumbnail:: /rst/figures/screenshots/pro/xy_chart.png
    :align: center

Filter the Domain View
======================

The Domain View graph can be filtered to show or hide specific entities without removing them from
the monitor.

With a Domain View tab active, click the |gear| button in the tab header to open the configuration
panel, which shows **DOMAIN GRAPH** at the top.

A **Filter entities...** search box at the top filters all sections simultaneously.
Entities are grouped into seven collapsible sections -- **TOPICS**, **HOSTS**, **USERS**,
**PROCESSES**, **PARTICIPANTS**, **DATAWRITERS**, **DATAREADERS** -- each showing a visible/total
count.

Clear the checkbox next to any entity alias to remove it from the graph.
The entity remains listed so it can be restored at any time.

.. figure:: /rst/figures/screenshots/domain_filter_pro.png
    :align: center

Under **ACTIONS**: **Show All Entities** makes every entity visible; **Hide All Entities** hides
all of them at once.

.. .. thumbnail:: /rst/figures/screenshots/pro/domain_graph_filter.png
    :align: center

View Live Image Data
====================

The *Image View* renders live image or video frames from a DDS topic inside the monitor.

Right-click an image-compatible topic in the **Topics** panel and select **Open image view**, or
go to **Add -> Add Image View**.
A new pane opens and the configuration panel shows **IMAGE VIEW** at the top.

* **TOPIC** shows the current topic and domain as read-only labels.
* Under **CHANGE TOPIC**: select a **Domain**, use **Filter topics...** to narrow the list, then
  pick a topic -- only topics with a recognized image schema appear (ROS 2
  ``sensor_msgs/Image`` or compatible OMG IDL image types).
* Click **Apply & Reload** to start the subscription.
* Under **PLAYBACK**, toggle *Active (receiving frames)* to pause or resume the stream.
* **STATUS** shows *Streaming*, *Waiting for frames*, *Paused*, or *Error*.
* **FRAME INFO** (once frames arrive) shows image size, encoding, and total frame count.
* Under **ACTIONS**: *Save Screenshot* saves the current frame; *Copy Screenshot* copies it.

.. figure:: /rst/figures/screenshots/image_pro.png
    :align: center

.. .. thumbnail:: /rst/figures/screenshots/pro/image_pane.png
    :align: center

Publish Topic Data
==================

The *Publisher View* lets you compose and send DDS samples on any discovered topic.

Right-click :code:`hello_world_topic` in the **Topics** panel and select **Publish topic data**, or
go to **Add -> Add Publisher View**.
A new pane opens and the configuration panel shows **PUBLISHER** at the top.

* **CURRENT TOPIC** shows the current topic, domain, type, status, and samples sent (read-only).
* Under **CHANGE TOPIC**: select a **Domain**, use **Filter data types...** to narrow the type
  list, pick a type, and type the topic name in **Topic name to publish on...** if needed.
* Click **Apply & Restart** to attach the publisher.
  The pane body fills with an auto-generated form -- one editable row per field in the message type.
* Under **CONTINUOUS**: toggle *Publish continuously* and set **Interval (ms)** (minimum :code:`50`)
  to publish at a fixed rate.
* Under **ACTIONS**: **Publish once** (blue button) sends a single sample immediately;
  **Reset** restores all fields to defaults; **Randomize** fills them with random valid values.

.. figure:: /rst/figures/screenshots/publish_pro.png
    :align: center

Fill in the form fields in the pane body (numeric spin boxes, text inputs, expandable structs),
then publish.

.. .. thumbnail:: /rst/figures/screenshots/pro/publisher_pane.png
    :align: center

Save and Restore a Workspace
==============================

After setting up monitors, panes, charts, and alerts, save the session so it can be restored
exactly as it is now.

Click the |save| button in the shortcuts toolbar, or go to **File -> Save Workspace**.
A file dialog opens; navigate to a folder, type a file name, and click **Save**.
The file is written with the :code:`.fdmw` extension.

To restore it, go to **File -> Load Workspace** and select the :code:`.fdmw` file.
All monitors, pane layouts, chart series, alert rules, and display settings are restored.

.. note::

   The statistics database is not stored in the workspace.
   Entity discovery restarts fresh on load; panes populate as DDS traffic is received.

.. .. thumbnail:: /rst/figures/screenshots/pro/save_workspace.png
    :align: center

Switch Theme
============

Go to **View -> Theme** and select **Dark** to activate the dark palette.
Every panel, chart, dialog, icon, and toolbar updates instantly without a restart.
To revert, select **View -> Theme -> Light**.

.. figure:: /rst/figures/screenshots/dark_theme_pro.png
    :align: center

The selected theme is saved in the workspace file and restored on the next load.
If no workspace has been saved yet, the application follows the operating system color scheme.

.. .. thumbnail:: /rst/figures/screenshots/pro/dark_mode.png
    :align: center
