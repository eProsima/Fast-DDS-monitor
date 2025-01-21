.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _chart_panel_index:

##########
Main Panel
##########

In the central panel, there is a tab section that allows multiple views, including a collapsed menu that reports the
possible problems that have been detected on the DDS entities.

The main feature of the *Fast DDS Monitor* application is to graphically display the data that is being monitored in
the *Chart View*.
DDS entities have associated different types of data (so-called *DataKind*) that could be visualized by configuring
a *Chart*.
For example, the mean, median and standard deviation latency between two machines (*Hosts*) running
*Fast DDS* applications for the period of two hours in intervals of ten minutes could be displayed.

The *Fast DDS Monitor* can also show the detected entities in a graph.
The *Domain view* would filter all entities that belong to the same DDS Domain, and represent the inheritance of the
physical and DDS entities (the DataWriters or DataReaders that belong to a DomainParticipant, the
DomainParticipants that run on the same Process, the Processes that a User is running, and the Users that are on a
Host).
Those relations are represented in different boxes that contain the sub-category of entities.
Also, the connections between different endpoints that are publishing or subscribed to a Topic are represented with
arrows.
Those arrows would start from the DataWriter and point to the Topic, or start from the Topic and point to the
DataReader (showing publication and subscription cases, respectively).

.. figure:: /rst/figures/screenshots/shapes_domain.png
    :align: center

Filtering that graph by Topic, only the entities whose endpoints are publishing in, or subscribed to the selected
Topic would be represented in the view.

.. figure:: /rst/figures/screenshots/shapes_topic.png
    :align: center

If there are problems reported by a DDS entity, they are condensed by entity in the bottom layout Problem Summary
section. Inside the problem counter, the problem is described and, in some cases, followed by an applicable link to
the documentation.

.. figure:: /rst/figures/screenshots/problem_detail.png
    :align: center

.. toctree::
    :maxdepth: 2

    /rst/user_manual/chart_panel/chart_panel
    /rst/user_manual/chart_panel/historic_series
    /rst/user_manual/chart_panel/dynamic_series
    /rst/user_manual/chart_panel/chartbox
    /rst/user_manual/chart_panel/problem_summary
