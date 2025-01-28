.. _ros_jazzy:

#################################
Monitor Tutorial with ROS 2 Jazzy
#################################

This section shows how to install and deploy some ROS 2 Jazzy nodes in order to monitor them with Fast DDS Monitor.

Installation
============

First of all, follow the :ref:`installation_manual_linux` or the :ref:`installation_manual_windows` on this
documentation to install Fast DDS Monitor. Additionally, make sure to also have a ROS 2 Jazzy installation available.

Execution
=========

We are going to recreate a simple DDS network with one :code:`talker` and one :code:`listener` from ROS 2 demo nodes.

Execute Fast DDS Monitor
------------------------

Initiate Fast DDS Monitor by running the executable file created in the installation process.
Once Fast DDS Monitor is launched, start a monitor in domain :code:`0` (default domain).

.. figure:: /rst/figures/screenshots/usage_example/Init_domain.png
    :align: center

Execute ROS 2 demo nodes with statistics
----------------------------------------

To execute ROS 2 nodes with statistics two aspects of the configuration must be taken into account:

- The middleware used must be Fast DDS, the default choice (can also be set through an environment variable).
- In order to activate the publication of statistical data, Fast DDS requires an environment variable specifying the
  specific kinds of statistical data to be reported.

To execute each of the nodes, run the following commands in different terminals:

.. code-block:: bash

    export FASTDDS_STATISTICS="HISTORY_LATENCY_TOPIC;NETWORK_LATENCY_TOPIC;\
    PUBLICATION_THROUGHPUT_TOPIC;SUBSCRIPTION_THROUGHPUT_TOPIC;RTPS_SENT_TOPIC;\
    RTPS_LOST_TOPIC;HEARTBEAT_COUNT_TOPIC;ACKNACK_COUNT_TOPIC;NACKFRAG_COUNT_TOPIC;\
    GAP_COUNT_TOPIC;DATA_COUNT_TOPIC;RESENT_DATAS_TOPIC;SAMPLE_DATAS_TOPIC;\
    PDP_PACKETS_TOPIC;EDP_PACKETS_TOPIC;DISCOVERY_TOPIC;PHYSICAL_DATA_TOPIC;\
    MONITOR_SERVICE_TOPIC"

    ros2 run demo_nodes_cpp listener

.. code-block:: bash

    export FASTDDS_STATISTICS="HISTORY_LATENCY_TOPIC;NETWORK_LATENCY_TOPIC;\
    PUBLICATION_THROUGHPUT_TOPIC;SUBSCRIPTION_THROUGHPUT_TOPIC;RTPS_SENT_TOPIC;\
    RTPS_LOST_TOPIC;HEARTBEAT_COUNT_TOPIC;ACKNACK_COUNT_TOPIC;NACKFRAG_COUNT_TOPIC;\
    GAP_COUNT_TOPIC;DATA_COUNT_TOPIC;RESENT_DATAS_TOPIC;SAMPLE_DATAS_TOPIC;\
    PDP_PACKETS_TOPIC;EDP_PACKETS_TOPIC;DISCOVERY_TOPIC;PHYSICAL_DATA_TOPIC;\
    MONITOR_SERVICE_TOPIC"

    ros2 run demo_nodes_cpp talker

Remember to source your `ROS 2 installation
<https://docs.ros.org/en/jazzy/Installation/Alternatives/Ubuntu-Development-Setup.html#setup-environment>`_
before every :code:`ros2` command.

Monitoring network
------------------

Now one should see in the :ref:`dds_panel_layout` two new Participants.

.. figure:: /rst/figures/screenshots/jazzy_tutorial/Participants.png
    :align: center

Domain View
^^^^^^^^^^^

To easily inspect the structure of the DDS network created, open the *Domain View* in the :ref:`chart_panel_index`.
In this tab, we can see a graph describing the structure of our network: our single Host contains our single User,
which in turn contains both our Processes, each containing a number of DataReaders and DataWriters. We can see a
number of Topics, presented as vertical gray lines, related to the code of the listener and talker. Only one of them,
:code:`rt/chatter`, relates two entities, a DataWriter and a DataReader: this is the Topic that is being
used to exchange information.

.. figure:: /rst/figures/screenshots/jazzy_tutorial/Domain_Graph.png
    :align: center

The *Domain View* allows us to access different possibilities. By pressing *right-click* on top of the Topic name, we
can find several options, such as filtering the graph by the Topic (selecting *Filter topic graph*). Clicking on the
:code:`rt/chatter` Topic, we can easily see the entities exchanging information.

.. figure:: /rst/figures/screenshots/jazzy_tutorial/Topic_filter.png
    :align: center

Additionally, we can access the we can access the IDL representation of any of the Topics, by pressing right-click over
the Topic name, and choosing *Data type IDL view*. This opens a new Tab with the required information, which can be
copied and pasted.

.. figure:: /rst/figures/screenshots/jazzy_tutorial/IDL_img_jazzy.png
    :align: center

Alias
^^^^^

Participants in ROS 2 are named :code:`/` by default.
In order to differentiate them one could change the alias of the Participant (see :ref:`change_alias`). This can be
done either from the :ref:`left_panel`, or from the Domain View panel, by pressing *righ click* on top of the entity.
The :code:`talker` would be the one with a :code:`chatter` writer, and the :code:`listener` the one with a
:code:`chatter` reader. Since we're not going to be using this Tab anymore, click on the *X* to return to the
:code:`New Tab` view.

.. figure:: /rst/figures/screenshots/jazzy_tutorial/Alias_new.png
    :align: center

Statistical data
^^^^^^^^^^^^^^^^

To show statistical data about the communication between the :code:`talker` and the :code:`listener`,
open the *Chart View* and follow the steps to :ref:`tutorial_create_dynamic_series` and plot this statistical data
in a real time chart.

.. figure:: /rst/figures/screenshots/jazzy_tutorial/Statistics.png
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

.. figure:: /rst/figures/screenshots/jazzy_tutorial/Metatraffic.png
    :align: center

Video Tutorial
==============

There is a `video tutorial <https://www.youtube.com/watch?v=OYibnUnMIlc>`_ going through the steps
described in this section.

