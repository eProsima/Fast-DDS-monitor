.. include:: ../../exports/alias.include

.. _pro_layout:

######
Layout
######

This section describes the graphical user interface (GUI) of *Fast DDS Monitor Pro*.
It briefly covers the main menus and windows to help you find the controls and information you need.
Below is a screenshot of the application in operation.

.. thumbnail:: /rst/figures/screenshots/App_run.png
    :align: center

.. _pro_application_menu_layout:

Application Menu
================

This menu bar contains all available options, divided into four groups:

- **File**: General application actions.
- **Edit**: Application-specific functionality.
- **View**: Window layout configuration.
- **Help**: Links to documentation, support, and application information.

.. figure:: /rst/figures/screenshots/application_menu.png
    :align: center

For a full description of each menu item, see :ref:`pro_application_menu`.

.. _pro_shortcuts_bar_layout:

Shortcuts Bar
=============

This horizontal toolbar provides quick access to the most commonly used actions.
The bar can be configured from the **View** menu.

.. figure:: /rst/figures/screenshots/shortcuts_bar.png
    :align: center

For details on configuring this bar, see :ref:`pro_shortcuts_bar`.

.. _pro_left_sidebar_layout:

Explorer Panel
==============

The left sidebar shows all entities discovered by the monitor.
Entities are displayed in collapsible, interactive lists.
Clicking any entity displays its details in the same panel.

The panel contains a variable number of sub-panels: the :ref:`pro_dds_panel_layout`,
:ref:`pro_physical_panel_layout`, :ref:`pro_logical_panel_layout`, and :ref:`pro_info_panel_layout`.
Each sub-panel groups entities by category.
Use the ``...`` button in the upper bar of the panel to show or hide individual sub-panels.
Drag the panel border to resize it.
To hide the entire left sidebar, use **View → Hide Left Sidebar**.

For more information on entity types and their relationships, see :ref:`entities`.
For more information on entity selection, see :ref:`pro_selected_entity`.

.. figure:: /rst/figures/screenshots/explorer_panel.png
    :align: center
    :scale: 50 %

.. _pro_dds_panel_layout:

DDS Panel
---------

This sub-panel shows the :ref:`dds_entities` discovered by the monitor: DDS *DomainParticipant*,
*DataReader*, *DataWriter*, and the transport *Locators* used by each entity.
The list is filtered to show only entities related to the currently selected entity —
see :ref:`pro_selected_entity` for details.

.. figure:: /rst/figures/screenshots/dds_panel.png
    :align: center

For a full description, see :ref:`pro_dds_panel`.

.. _pro_physical_panel_layout:

Physical Panel
--------------

This sub-panel shows the physical entities discovered by the monitor: *Host*, *User*, and *Process*.
These represent the machine and execution context of each *Fast DDS* application.
For details, see :ref:`pro_physical_panel`.

.. figure:: /rst/figures/screenshots/physical_panel.png
    :align: center

.. _pro_logical_panel_layout:

Logical Panel
-------------

This sub-panel shows the logical entities discovered by the monitor: *Domain* and *Topic*.
These represent the abstract partitions of a DDS network.
Only entities sharing the same *Domain* can communicate with each other.
For details, see :ref:`pro_logical_panel`.

.. figure:: /rst/figures/screenshots/logical_panel.png
    :align: center

.. _pro_info_panel_layout:

Entity Info Panel
-----------------

This sub-panel displays information about the last clicked entity.
It has two tabs:

.. _pro_info_subpanel_layout:

Info Panel
^^^^^^^^^^

Shows the general information of the selected entity.
The fields shown depend on the entity type: for example, a *DDS Entity* shows *QoS* information,
while a *Process* shows its *process ID*.

.. figure:: /rst/figures/screenshots/Info_panel.png
    :align: center

For a full description, see :ref:`pro_info_panel`.

.. _pro_statistics_panel_layout:

Statistics Panel
^^^^^^^^^^^^^^^^

Shows a summary of the main statistical data for the selected entity.

.. figure:: /rst/figures/screenshots/statistics_panel.png
    :align: center

For a full description, see :ref:`pro_statistics_panel`.

.. _pro_alerts_panel_layout:

Alerts Panel
============

This panel shows the alerts created by the user to monitor specific events in the DDS network.

.. figure:: /rst/figures/screenshots/alert_panel.png
    :align: center

For a full description, see :ref:`pro_alerts_panel`.

.. _pro_alert_list_layout:

Alert List
----------

Lists the alerts created by the user.
Alerts are created using the |create_alert| button in the Shortcuts Bar or the **+** button in the
upper-right corner of the panel.
Right-click an alert to remove it.

.. _pro_alert_data_layout:

Alert Data
----------

Shows the configuration of the alert selected in the *Alert List*, including its name, domain,
host, user, topic, threshold, and duration.

.. _pro_monitor_status_panel_layout:

Monitor Status Panel
====================

This panel displays data about the monitored entities and the current state of the application.
It contains two sub-panels: :ref:`pro_status_panel_layout` and :ref:`pro_log_panel_layout`.
Click the sub-panel name to switch between them.

Drag the panel border to resize it.
To hide the panel, use **View → Hide Left Sidebar**.

.. _pro_status_panel_layout:

Status Panel
------------

Displays the current state of the application:

- **Entities**: the number of entities being monitored.
- **Domains**: the list of domains initialized in the monitor.

.. figure:: /rst/figures/screenshots/status_panel.png
    :align: center

For a full description, see :ref:`pro_status_panel`.

.. _pro_log_panel_layout:

Log Panel
---------

Displays the callbacks received by the application.
Callbacks are triggered by events such as discovery of a new entity or reception of new statistical data.
Use the :ref:`refresh_button` to clear the log.

.. figure:: /rst/figures/screenshots/log_panel.png
    :align: center

For a full description, see :ref:`pro_log_panel`.

.. _pro_issues_panel_layout:

Issues Panel
============

Lists error events reported by the application, such as attempting to start a monitor on an already
initialized domain.

.. figure:: /rst/figures/screenshots/issues_panel.png
    :align: center

For a full description, see :ref:`pro_issues_panel`.

.. _pro_alert_messages_panel_layout:

Alert Messages Panel
====================

Lists the alert events detected by the application based on the alerts created by the user.
Messages are shown in a tree structure with the most recent entries at the bottom.

.. figure:: /rst/figures/screenshots/alert_messages_panel.png
    :align: center

.. _pro_main_panel_layout:

Main Panel
==========

The central panel hosts multiple tabs with different views.
It displays a collapsible problem-summary section showing detected issues per entity.
It can show statistics *Chartboxes*, a *Domain Graph*, and — in *Fast DDS Monitor Pro* — any number of
:ref:`dockable panes <dockable_panes>` such as Topic Charts, Spy Panes, and Image Panes.

.. figure:: /rst/figures/screenshots/main_panel.png
    :align: center

For details on creating statistics charts, see :ref:`pro_chart_panel`.

.. _pro_chartbox_layout:

Chartbox
--------

A *Chartbox* stores one or more *series* to display a specific data type for one or several entities
over a specified time interval, with configurable accumulation operations.

To create a new *Chartbox*, go to the **Chart View** tab in the main panel and click **Create new chart**.
Chartboxes can be repositioned by dragging their title bar.
The remaining Chartboxes rearrange automatically.

.. thumbnail:: /rst/figures/screenshots/chartbox.png
    :align: center

For details on creating a chart, see :ref:`pro_chart_panel`.

.. _pro_create_new_series_layout:

Create Series Dialog
^^^^^^^^^^^^^^^^^^^^

This dialog appears when creating a new Chartbox or adding a series via **Series → Add Series**.

.. figure:: /rst/figures/screenshots/Create_series_historical.png
    :align: center

    Create historical series dialog

.. figure:: /rst/figures/screenshots/Create_series_dynamic.png
    :align: center

    Create real-time series dialog

For details, see :ref:`historic_series` for historical data or :ref:`dynamic_series` for real-time data.

.. _pro_domain_graph:

Domain View
-----------

This view shows the connections between DataWriters and DataReaders within a DDS Domain.
Entities are displayed encapsulated inside their physical entities (see :ref:`entities`),
with connections to the topics they publish on or subscribe to.

.. thumbnail:: /rst/figures/screenshots/domain_graph.png
    :align: center

Clicking any entity displays its details in the :ref:`pro_info_panel`.
Right-clicking allows you to rename the entity alias, filter problems to the selected entity, or —
for topics — filter the domain graph to show only the entities related to that topic.

The right-side configuration panel |Pro| provides per-entity visibility controls for the graph.
Individual topics, hosts, users, processes, participants, writers, and readers can be shown or hidden
by alias, with **Show All** and **Hide All** bulk actions.
See :ref:`domain-graph` for details.

.. _pro_problem_summary:

Problem Summary
---------------

This collapsible section at the bottom of the main panel lists all collected problems per entity.
Problems include samples lost, incompatible QoS between endpoints, and missed DataWriter deadlines.

Entities with reported problems display a warning or error icon next to their name, both here and in
the domain graph.

.. thumbnail:: /rst/figures/screenshots/problem.png
    :align: center
