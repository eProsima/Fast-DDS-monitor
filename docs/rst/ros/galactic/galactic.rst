.. _ros_glactic:

########
Galactic
########

This section shows how to install and deploy some ROS 2 Galactic nodes in order to monitor them with Fast DDS Monitor.

Installation
============

First of all, follow the :ref:`installation_manual_linux` on this documentation to install Fast DDS Monitor.

Fast DDS is not installed by default in the ROS 2 Galactic release.
Thus, first required step is to download Fast DDS and compile it with statistics.

Installation from sources
-------------------------

Follow the `ROS 2 galactic installation from sources documentation
<https://docs.ros.org/en/galactic/Installation/Ubuntu-Development-Setup.html>`_
Fast DDS is downloaded within the rest of the packages.
The only consideration here is to compile :code:`fastdds` library with the Statistics Module activated.
When compiling with colcon, the following arguments must be provided:

.. code-block:: bash

    colcon build --symlink-install --cmake-args -DFASTDDS_STATISTICS=ON

.. todo:

    Add Installation from binaries option

Execution
=========

We are going to recreate a simple DDS network with one :code:`talker` and one :code:`listener` from ROS 2 demo nodes.

Execute Fast DDS Monitor
------------------------

Initiate Fast DDS Monitor by running the executable file created in the installation process.
Once Fast DDS Monitor is launched, start a monitor in domain :code:`0` (default domain).

.. figure:: /rst/figures/screenshots/usage_example/init_domain.png
    :align: center

Execute ROS 2 demo nodes with statistics
----------------------------------------

To execute ROS 2 nodes with statistics two aspects of the configuration must be taken into account:

- The middleware used must be Fast DDS, set through an environment variable.
- In order to activate the publication of statistical data, Fast DDS requires an environment variable specifying those
  kinds of statistical data to be reported.

To execute each of the nodes, run the following commands in different terminals:

.. code-block:: bash

    export RMW_IMPLEMENTATION=rmw_fastdds_cpp

    export FASTDDS_STATISTICS="HISTORY_LATENCY_TOPIC;NETWORK_LATENCY_TOPIC;\
    PUBLICATION_THROUGHPUT_TOPIC;SUBSCRIPTION_THROUGHPUT_TOPIC;RTPS_SENT_TOPIC;\
    RTPS_LOST_TOPIC;HEARTBEAT_COUNT_TOPIC;ACKNACK_COUNT_TOPIC;NACKFRAG_COUNT_TOPIC;\
    GAP_COUNT_TOPIC;DATA_COUNT_TOPIC;RESENT_DATAS_TOPIC;SAMPLE_DATAS_TOPIC;\
    PDP_PACKETS_TOPIC;EDP_PACKETS_TOPIC;DISCOVERY_TOPIC;PHYSICAL_DATA_TOPIC;\
    MONITOR_SERVICE_TOPIC"

    ros2 run demo_nodes_cpp listener

.. code-block:: bash

    export RMW_IMPLEMENTATION=rmw_fastdds_cpp

    export FASTDDS_STATISTICS="HISTORY_LATENCY_TOPIC;NETWORK_LATENCY_TOPIC;\
    PUBLICATION_THROUGHPUT_TOPIC;SUBSCRIPTION_THROUGHPUT_TOPIC;RTPS_SENT_TOPIC;\
    RTPS_LOST_TOPIC;HEARTBEAT_COUNT_TOPIC;ACKNACK_COUNT_TOPIC;NACKFRAG_COUNT_TOPIC;\
    GAP_COUNT_TOPIC;DATA_COUNT_TOPIC;RESENT_DATAS_TOPIC;SAMPLE_DATAS_TOPIC;\
    PDP_PACKETS_TOPIC;EDP_PACKETS_TOPIC;DISCOVERY_TOPIC;PHYSICAL_DATA_TOPIC;\
    MONITOR_SERVICE_TOPIC"

    ros2 run demo_nodes_cpp talker

Remember to source your `ROS 2 installation
<https://docs.ros.org/en/galactic/Installation/Ubuntu-Development-Setup.html?highlight=source#source-the-setup-script>`_
before every ros2 command.

Monitoring network
------------------

Now one should see in the :ref:`dds_panel_layout` two new Participants.

.. figure:: /rst/figures/screenshots/galactic_tutorial/participants.png
    :align: center

Alias
^^^^^

Participants in ROS 2 are named :code:`/` by default.
In order to differentiate them one could change the alias of the Participant (see :ref:`change_alias`).
The :code:`talker` would be the one with one writer, and the :code:`listener` the one with a reader.

.. figure:: /rst/figures/screenshots/galactic_tutorial/alias.png
    :align: center

Physical data
^^^^^^^^^^^^^

In order to see the information of the host and the physical context where every node is running, go to
the :ref:`left_panel` and activate the :ref:`physical_panel`.
There, the host, user and process of each node are displayed.

.. figure:: /rst/figures/screenshots/galactic_tutorial/physical.png
    :align: center

Statistical data
^^^^^^^^^^^^^^^^

To show statistical data about the communication between the :code:`talker` and the :code:`listener`,
follow the steps to :ref:`tutorial_create_dynamic_series` and plot this statistical data in a real time chart.

.. figure:: /rst/figures/screenshots/galactic_tutorial/statistics.png
    :align: center

Introspect metatraffic topics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Fast DDS Monitor filters by default the topics used for sharing metatraffic and the endpoints related to them
so the user can inspect their network easily.
These topics are the ones that ROS 2 uses for discovery and configuration purposes, such as :code:`ros_discovery_info`,
as well as those used by Fast DDS to report statistical data.

In order to see these topics in the monitor, click *View->Show Metatraffic* menu button
(see :ref:`hide_show_metatraffic`).
Now, these topics are shown in the logical panel, and also the Readers and Writers associated to them under their
respective Participants.

.. figure:: /rst/figures/screenshots/galactic_tutorial/metatraffic.png
    :align: center

Video Tutorial
==============

There is a `video tutorial <https://www.youtube.com/watch?v=OYibnUnMIlc>`_ going through the steps
described in this section.

