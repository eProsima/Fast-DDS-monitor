.. _ros_glactic:

########
Galactic
########

This section shows how to install and deploy some ROS 2 galactic nodes in order to monitor them with Fast DDS Monitor.
It assumes that

Installation
============

First of all, follow the :ref:`installation_manual_linux` on this documentation to install the Fast DDS Monitor.

Fast DDS is not installed by default in the ROS 2 Galactic release.
Thus, first step is required is to download Fast DDS and compile it with statistics.

Installation from sources
-------------------------

Follow the `ROS 2 galactic installation from sources documentation
<https://docs.ros.org/en/galactic/Installation/Ubuntu-Development-Setup.html>`_
Fast DDS is downloaded within the rest of the packages.
The only consideration here is to compile fastrtps library with the Statistics Module activated.
When compiling with colcon, add this arguments as:

.. code-block:: bash

    colcon build --symlink-install --cmake-args -DFASTDDS_STATISTICS=ON

.. todo:

    Add Installation from binaries option

Execution
=========

We are going to recreate a simple DDS network with one :code:`talker` and one :code:`listener` from ROS 2 demo nodes.

Execute Fast DDS Monitor
------------------------

Intiate Fast DDS Monitor by the executable created by the installation process.
Once into the Fast DDS Monitor window, start a monitor in domain :code:`0` (default domain).

.. todo:

    Add screenshot

Execute ROS 2 demo nodes with statistics
----------------------------------------

To execute ROS 2 nodes with statistics two configurations must be taken into account:

- The middleware used must be Fast DDS, set by an environmental variable.
- To activate the report of statistic data, Fast DDS requires to use an environmental variable setting up those
    statistic kinds that are going to be reported.

To execute each of the nodes, run the following commands in different terminals:

.. code-block:: bash

    export RMW_IMPLEMENTATION=rmw_fastrtps_cpp
    export FASTDDS_STATISTICS="HISTORY_LATENCY_TOPIC;SUBSCRIPTION_THROUGHPUT_TOPIC;PHYSICAL_DATA_TOPIC" # add as many statistics topic as wanted
    ros2 run demo_nodes_cpp listener

.. code-block:: bash

    export RMW_IMPLEMENTATION=rmw_fastrtps_cpp
    export FASTDDS_STATISTICS="HISTORY_LATENCY_TOPIC;SUBSCRIPTION_THROUGHPUT_TOPIC;PHYSICAL_DATA_TOPIC" # add as many statistics topic as wanted
    ros2 run demo_nodes_cpp talker

Remember to source your `ROS 2 installation
<https://docs.ros.org/en/galactic/Installation/Ubuntu-Development-Setup.html?highlight=source#source-the-setup-script>`_
before every ros2 command.

Monitoring network
------------------

Now you must see in the Fast DDS Monitor two new Participants.

.. todo:

    Add screenshot

Alias
^^^^^

Participants in ROS 2 are called :code:`\ `.
In order to differentiate them you could :ref:`change_alias`.
The :code:`talker` would be the one with one writer, and the :code:`listener` with a reader.

.. todo:

    Add screenshot

Physical data
^^^^^^^^^^^^^

In order to see the information about the host and the physical context where every node is running, go to
the :ref:`left_panel` and activate the :ref:`physical_panel`.
There are shown the host, user and process of each node.

Statistical data
^^^^^^^^^^^^^^^^

To show statistical data about the communication between the :code:`talker` and the :code:`listener`.
Follow the steps to :ref:`tutorial_create_dynamic_series` and see this statistical data graphically in a real
time chart.

.. todo:

    Add screenshot

Introspect metatraffic topics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Fast DDS Monitor filters by default the metatraffic topics and the endpoints related to them so the user
can inspection its network easily.
These topics are the ones that ROS 2 uses for discovery and configuration, such as `ros_discovery_info`.
And those used by Fast DDS to report statistical data.

.. todo:

    Add link to metatraffic section and metatraffic show button

In order to see these topics in the monitor, click .
Now, these topics will be shown in the logical panel, and the Readers and Writers associated to them under their
respective Participants.

.. todo:

    Add screenshot

Video Tutorial
==============

There is a `video tutorial <https://www.youtube.com/watch?v=OYibnUnMIlc>`_ briefly showing the tutorial
that has been explained in this section.

