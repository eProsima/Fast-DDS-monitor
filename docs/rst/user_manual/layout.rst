.. include:: ../exports/alias.include

.. _layout:

######
Layout
######
This section explains the Graphical User Interface (GUI) of the *Fast DDS Monitor* application.
It will briefly explain the main menus and windows that could be seen, in order to familiarize the user
with where to find the buttons and information.
Below is a screenshot of the *Fast DDS Monitor* application in operation.

.. figure:: /rst/figures/screenshots/App_run.png
    :align: center

.. _application_menu_layout:

Application Menu
================
This general menu contains all the options available for this application divided in four groups depending on
their area of operation:

- **File**: General propose buttons.
- **Edit**: Specific buttons with application functionality
- **View**: Window layout configuration.
- **Help**: Useful links for getting application information or support.

.. figure:: /rst/figures/screenshots/application_menu.png
    :align: center

For the explanation of the functionality of this buttons refer to the section :ref:`application_menu`.

.. _shortcuts_bar_layout:

Shortcuts Bar
=============
This horizontal bar contains shortcuts to the main operations supported by the application,
so the user has a faster access to the main functionalities.
This bar could be configured in the *View* tab of the application menu.

.. figure:: /rst/figures/screenshots/shortcuts_bar.png
    :align: center

For the explanation of how to configure this bar refer to the section :ref:`shortcuts_bar`.

.. _left_sidebar_layout:

Explorer Panel
==============
This panel shows the different entities that have been discovered by the monitor.
They will be displayed in interactive lists that the user could expand or collapse.
These entities are clickable as well, in order to inspect their information shown in this same panel.

This panel contains a mutable number of subpanels.
The different panels that could be shown are the :ref:`dds_panel_layout`, the :ref:`physical_panel_layout`,
the :ref:`logical_panel_layout` and the :ref:`info_panel_layout`.
In these subpanels, the entities discovered are going to be displayed depending on their kind.
In order to know which kind of entities the application has and how are they divided in categories, please refer to
:ref:`entities`.

To add a new panel to display other relevant information, use the ``...`` button in the upper bar of the panel and
select those subpanels that want to be show or hide.
To increase or decrease this sidebar size, grab the border of it and move it to the desired size.
In order to hide the whole left sidebar, click *Hide Left sidebar* in the *View* menu.

For more information about what is an entity and how they are organized refer to :ref:`entities`.
For more information about what it means to select an entity refer to :ref:`selected_entity`.

.. figure:: /rst/figures/screenshots/explorer_panel.png
    :align: center
    :scale: 50 %

.. _dds_panel_layout:

DDS Panel
---------
This subpanel shows the :ref:`dds_entities` of the monitor.
These entities are the DDS *DomainParticipant*, the DDS *DataReader* and *DataWriter*, and the transport *Locators* that
each entity is using.
This subpanel will be filled with the DDS entities that are related with the entity currently selected,
so it could happen that not all DDS entities discovered by the monitor appear in this subpanel at a certain point
(see :ref:`selected_entity` for further details).

.. todo::

    use a figure with not alive entities

.. figure:: /rst/figures/screenshots/dds_panel.png
    :align: center

For the explanation of this entities and the interaction with them refer to the section :ref:`dds_panel`.

.. _physical_panel_layout:

Physical Panel
--------------
This subpanel shows the Entities discovered by the monitor that refer to physical entities.
There are three different kind of physical entities, *Host*, *User* and *Process*.
These entities refer to the main information of the machine and the context where an application using
*Fast DDS* is running.
For further explanation of these entities and the interaction with them refer to the section :ref:`physical_panel`.

.. figure:: /rst/figures/screenshots/physical_panel.png
    :align: center

.. _logical_panel_layout:

Logical Panel
-------------
This subpanel shows the Entities discovered by the monitor that refer to abstract entities in a
DDS communication network.
These entities are *Domain* and *Topic*.
These entities refer to abstract partitions in a DDS network. Only entities in the same *Domain* could communicate
to each other by publishing or subscribing in the same *Topic*.
For further explanation of this entities and the interaction with them refer to the section :ref:`logical_panel`.

.. figure:: /rst/figures/screenshots/logical_panel.png
    :align: center

.. _info_panel_layout:

Entity Info Panel
-----------------
This subpanel displays information regarding the last entity clicked.
This information is divided in two categories, which are shown in the different subpanel tabs.
First, the ``info`` tab contains the general information of the last entity clicked.
Secondly, the ``Statistics`` tab contains a summary of the main statistical data regarding the last entity clicked.

.. _info_subpanel_layout:

Info Panel
^^^^^^^^^^
This panel shows the main information of the last entity clicked.
This information differs depending on the kind of the entity, i.e. for a *DDS Entity*,
the *QoS* information would be shown, while for a *Process*, its *process id* will be displayed.

.. figure:: /rst/figures/screenshots/Info_panel.png
    :align: center

For the explanation of this information refer to the section :ref:`info_panel`.

.. _statistics_panel_layout:

Statistics Panel
^^^^^^^^^^^^^^^^
This panel shows a summary of the main statistical data related with the last entity clicked.

.. figure:: /rst/figures/screenshots/statistics_panel.png
    :align: center

For the explanation of this information refer to the section :ref:`statistics_panel`.

.. _monitor_status_panel_layout:

Monitor Status Panel
====================

In this panel, different data related to the entities being monitored or the current state of the application
will be displayed. This panel contains two different subpanels, the :ref:`status_panel_layout` and the
:ref:`log_panel_layout`. To change from one another, press on the name of the subpanel to be displayed.

To increase or decrease this sidebar size, grab the border of it and move it to the desired size.
In order to hide the whole left sidebar, click *Hide Left sidebar* in the *View* menu.

.. _status_panel_layout:

Status Panel
------------

This panel shows a collection of data related with the current state of the application:

- Entities refer to the number of entities being monitored in the user application.

- Domains is a collection of the *Domains* that have been initialized in the Monitor.

.. figure:: /rst/figures/screenshots/status_panel.png
    :align: center

For a thorough explanation of this information refer to the section :ref:`status_panel`.

.. _log_panel_layout:

Log Panel
---------

This panel shows the callbacks that the application has obtained.
These callbacks refer to different events in the DDS network that is being monitored.
These callbacks could be cleared by using the :ref:`refresh_button`.
A callback may refer to:

- The discovery of a new Entity in the DDS network.

- The reception of new data related to any of the entities that are being monitored.

.. figure:: /rst/figures/screenshots/log_panel.png
    :align: center

For a thorough explanation of this information refer to the section :ref:`log_panel`.

.. _issues_panel_layout:

Issues Panel
============

This panel lists the error events of the application.
The events that the application reacts to in the current version are:

- Attempt to start monitoring a DDS Domain or a Discovery Server network that has been previously initialized.

.. figure:: /rst/figures/screenshots/issues_panel.png
    :align: center

For a thorough explanation of this information refer to the section :ref:`issues_panel`.

.. _main_panel_layout:

Main Panel
==========
The central window allows multiple tabs for different views.
It also displays a collapsed menu with the possible problems that have been detected on the DDS entities.
It can display the data charts, so-called *Chartbox*, that the user has configured.
It can also display a domain graph where the physical, logical and DDS entities from a domain are represented,
focusing on the connection between endpoints through the topics, and the entities physical inheritance.

.. figure:: /rst/figures/screenshots/main_panel.png
    :align: center

For further information about how to create a chart refer to the section :ref:`chart_panel`.

.. _chartbox_layout:

Chartbox
--------
These windows in the main panel store some *series* or *data configurations* to show a specific data type for
one or several entities in a specified time interval and with different accumulative operations on the data.

To create a new *Chartbox* go to *Chart View* in the Main Panel default tab, and click on *Create new chart* button.
This button will create a new *Chartbox* where new series could be added, removed or modified.

These *Chartboxes* can be moved along the *Chart View* tab.
In order to move one of these charts, click on the *Chartbox* title and grab the object to its new desired location
inside the main panel.
The rest of the *Chartboxes* will automatically rearrange when one of them is moved to a different position.

.. figure:: /rst/figures/screenshots/chartbox.png
    :align: center

For further information about how to create a chart refer to the section :ref:`chart_panel`.

.. _create_new_series_layout:

Create Series Dialog
^^^^^^^^^^^^^^^^^^^^
This Dialog will appear every time a new Chartbox is created, or adding a new series by the button in the Chartbox
*Series->AddSeries*.

.. figure:: /rst/figures/screenshots/Create_series_historical.png
    :align: center

    Create historical series dialog

.. figure:: /rst/figures/screenshots/Create_series_dynamic.png
    :align: center

    Create real-time series dialog

For further details on how to configure a new series refer to :ref:`historic_series` for historic data or
:ref:`dynamic_series` for dynamic data.

.. _domain_graph:

Domain View
-----------
This view in the main panel shows the connections between DataWriters and DataReaders that belong to the same
DDS Domain.
They are represented encapsulated inside their physical entities (see :ref:`entities` relationship), and with a
connection to the topic they publish on or are subscribed to, respectively.

.. figure:: /rst/figures/screenshots/domain_graph.png
    :align: center

By clicking on any entity, its detailed information is displayed in the :ref:`info_panel`.
Right click allows changing the alias of the entity, filter the problems to display only the selected entity's problems
and, in the case of topics, filtering the domain graph by topic so that only the entities related to the selected topic
are displayed.

.. _problem_summary:

Problem summary
---------------

This section that can be expanded and collapsed displays all the collected problems per entity.
Those problems are related to DataReader samples lost, incompatible QoS between endpoints, or DataWriter deadline missed
counter, for instance.

The entities that have reported a problem would display a warning or an error icon close to the entity name, based on
the severity of the problem.
The entity representation in the domain graph may also display that icon.

.. figure:: /rst/figures/screenshots/problem.png
    :align: center
