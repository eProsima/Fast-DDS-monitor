.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _chart_panel_index:

##########
Main Panel
##########

In the central panel, there is a tan section that allows multiple views, including a collapsed menu that reports the
possible problems that have been detected on the DDS entities.

The main feature of the *Fast DDS Monitor* application is to graphically display the data that is being monitored in
the *Chartbox* or *Chart view*.
DDS entities have associated different types of data (so-called *DataKind*) that could be visualize by configuring
a chart.
For example, it can be displayed the mean, median and standard deviation latency between two machines (*Hosts*) running
*Fast DDS* applications for the period of two hours in intervals of ten minutes.

There are other features to represent the detected entities graphically in a graph.
The *Domain view* would filter all entities that belong to the same DDS Domain, and represent the inheritance of the
physical entities and DDS entities (the DataWriters or DataReaders that belong to a DomainParticipant, the
DomainParticipants that runs on the same process, the processes that a user is running, and the users that are on a
host).
Those relations are represented in different boxes that contain the sub-category of entities.
Also, the connections between different endpoints that are publishing or subscribed to a Topic are represented with
arrows.
Those arrows would start from the DataWriter and point to the Topic, or start from the Topic and point to the
DataReader (in publication and subscription cases, respectively).

.. figure:: /rst/figures/screenshots/shapes_domain.png
    :align: center

If filtering that graph by Topic, only the entities whose endpoints are publishing in, or subscribed to the selected
Topic would be represented in the view.

.. figure:: /rst/figures/screenshots/shapes_topic.png
    :align: center

If there are problems reported by a DDS entity, they are condensed by entity in the bottom layout problem section.
Among the problem counter, the problem is described and, in some cases, followed by a link to the documentation.

.. figure:: /rst/figures/screenshots/problem_detail.png
    :align: center

.. toctree::
    :maxdepth: 2

    /rst/user_manual/chart_panel/chart_panel
    /rst/user_manual/chart_panel/historic_series
    /rst/user_manual/chart_panel/dynamic_series
    /rst/user_manual/chart_panel/chartbox
