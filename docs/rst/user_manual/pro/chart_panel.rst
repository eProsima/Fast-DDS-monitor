.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_chart_panel:

##########
Main Panel
##########

The central panel hosts multiple tabs and views for inspecting and visualizing monitored data.

.. _pro_chart_view:

Chart View
==========

The primary feature of *Fast DDS Monitor Pro* is the graphical display of monitored DDS statistics
in the *Chart View*.
DDS entities expose different types of statistical data (called *DataKind*) that can be visualized
by configuring a *Chartbox*.
For example, you can display the median, mean, and standard deviation of application latency between
two hosts running *Fast DDS* applications over a two-hour window, sampled at ten-minute intervals.

See :ref:`chart_panel` for a full description of Chartbox configuration.
See :ref:`historic_series` for historical data charts and :ref:`dynamic_series` for real-time charts.

In addition to statistics charts, *Fast DDS Monitor Pro* provides the following pane types for
visualizing live topic data:

* :ref:`Topic Charts <topic_charts>` |Pro| for plotting live numeric values from any DDS topic as a
  time-series chart, including :ref:`XY Charts <xy_charts>` for scatter plots of one numeric field
  against another.
* :ref:`Dockable Spy Pane <dockable_spy_pane>` |Pro| for inspecting raw live message data from any
  DDS topic as a structured tree.
* :ref:`Image Pane <image_pane>` |Pro| for rendering live image or video data from DDS topics directly
  in the workspace.

.. _pro_domain_view:

Domain View
===========

The *Domain View* shows all entities belonging to the same DDS domain in a graph.
Entities are displayed encapsulated inside their physical context, with arrows indicating the
publisher–subscriber relationships through their shared topics.
Arrows run from a DataWriter to its topic, and from a topic to its DataReaders.

.. thumbnail:: /rst/figures/screenshots/shapes_domain.png
    :align: center

Filtering the graph by topic shows only the entities whose endpoints publish to or subscribe from
the selected topic, opened in a new tab.

.. thumbnail:: /rst/figures/screenshots/shapes_topic.png
    :align: center

Each topic's IDL type definition is also accessible from the *Domain View*.

.. thumbnail:: /rst/figures/screenshots/IDL_img.png
    :align: center

Right-clicking the IDL view opens a context menu with options to copy selected text, select all, or
copy the title to the clipboard.
When the type is a ROS 2 type, the IDL and type name are shown demangled by default, indicated by a
badge in the upper-right corner.
Use **View → Revert ROS 2 Demangling** to display the raw type, or **View → Perform ROS 2 Demangling**
to restore demangling.

.. thumbnail:: /rst/figures/screenshots/IDL_demangled_context_menu.png
    :align: center

.. _pro_problem_panel:

Problem Summary
===============

The collapsible *Problem Summary* section at the bottom of the main panel lists all detected problems
per entity.
Problems include data samples lost, incompatible QoS between endpoints, and missed DataWriter deadlines.
Where applicable, the problem description includes a link to the relevant documentation.

.. thumbnail:: /rst/figures/screenshots/problem_detail.png
    :align: center
