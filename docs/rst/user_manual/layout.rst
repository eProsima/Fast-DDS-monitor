.. include:: ../exports/alias.include

.. _layout:

######
Layout
######

This section explains the Graphical User Interface (GUI) of the *Fast DDS Monitor* application.
It will briefly explain the main menus and windows that could be seen, in order to familiarize the user
with where to find the buttons and information.

.. _application_menu_layout:

Application Menu
================

This general menu contains all the options available for this application divided in four groups depending on
their area of operation:

- **File**: General propose buttons.
- **Edit**: Specific buttons with application functionality
- **View**: Window layout configuration.
- **Help**: Useful links for getting application information or support.

.. todo::
    Include a screenshot.

For the explanation of the functionality of this buttons refer to the section :ref:`application_menu`.

.. _shortcuts_bar_layout:

Shortcuts Bar
=============

This horizontal bar contains shortcuts to the main operations supported by the application,
so the user has a faster access to the main functionalities.
This bar could be configured in the *View* tab of the application menu.

.. todo::
    Include a screenshot.

For the explanation of how to configure this bar refer to the section :ref:`shortcuts_bar`.

.. _left_sidebar_layout:

Left Sidebar
============

In this side bar it will be shown the different entities that has been discovered by the monitor.
They will be displayed in interactive lists that the user could expand or collapse.
These entities are clickable as well, in order to inspect them.

This sidebar contains a mutable number of panels where one of the possible entity panels will be displayed.
The different panels that could be shown are the :ref:`dds_panel_layout`, the :ref:`physical_panel_layout` and
the :ref:`logical_panel_layout`.
In this panels, the entities discovered are going to be displayed depending on their kind.
In order to know which kind of entities the application has and how are they divided in categories, please refer to
:ref:`entities`.

To add a new panel to display other relevant information, use the ``+`` button in the upper bar of any panel.
To delete any panel click in the ``x`` button.
Once one new panel is created could be changed to the desired kind by clicking in the name of the panel and choosing
one of them.
To increase or decrease this sidebar size, grab the border of it and move it to the desired size.
In order to hide the whole left sidebar, click in the ``<`` button in the upper panel or click
*Hide Left sidebar* in the *View* menu..

For more information about what is an entity and how they are organized refer to :ref:`entities`.
For more information about what means to select an entity refer to :ref:`selected_entity`.

.. _dds_panel_layout:

DDS Panel
---------

This panel shows the :ref:`dds_entities` of the monitor.
This entities are the DDS *DomainParticipant*, the DDS *DataReader* and *DataWriter*, and the transport *Locators* that
each entity is using.
This panel will be filled with the DDS entities that are related with the entity currently selected,
so it could happen that not all the DDS entities discovered by the monitor appears in this panel at a certain point
(see :ref:`selected_entity` for further details).

.. todo::
    Include a screenshot.

For the explanation of this entities and the interaction with them refer to the section :ref:`dds_panel`.

.. _physical_panel_layout:

Physical Panel
--------------

In this panel it will appear the Entities discovered by the monitor that refers to physical entities.
There are three different kind of physical entities, *Host*, *User* and *Process*.
These entities refer to the main information of the machine and the context where an application using
*Fast DDS* is running.
For further explanation of this entities and the interaction with them refer to the section :ref:`physical_panel`.

.. todo::
    Include a screenshot.

.. _logical_panel_layout:

Logical Panel
-------------

In this panel it will appear the Entities discovered by the monitor that refers to abstract entities in a
DDS communication network.
These entities are *Domain* and *Topic*.
These entities refer to abstract partitions in a DDS network. Only entities in the same *Domain* could communicate
to each other by publishing or subscribing in the same *Topic*.
For further explanation of this entities and the interaction with them refer to the section :ref:`logical_panel`.

.. todo::
    Include a screenshot.

.. _right_sidebar_layout:

Right Sidebar
=============

In this side bar it will be shown different data related with the entities that are being monitored or related
with the actual state of the application.
This side bar is divided in two different side bars.
The upper one contains :ref:`info_panel_layout` and :ref:`statistics_panel_layout`.
To change from one another press on the name of the tab an choose the panel desired to be displayed.
The lower side bar contains :ref:`status_panel_layout`, :ref:`log_panel_layout` and
:ref:`issues_panel_layout`.
To change from one to another press on the name of the tab an choose the panel desired to be displayed.

To increase or decrease this sidebar size, grab the border of it and move it to the desired size.
In order to hide the whole left sidebar, click in the ``<`` button in the upper panel or click
*Hide Left sidebar* in the *View* menu.

.. _info_panel_layout:

Info Panel
----------

This panel shows the main information of the last entity clicked.
This information differs depending on the kind of the entity, i.e. for a *DDS Entity*,
the *QoS* information would be shown, while for a *Process*, its *process id* will be displayed.

.. todo::
    Include a screenshot.

For the explanation of this information refer to the section :ref:`info_panel`.

.. _statistics_panel_layout:

Statistics Panel
----------------

This panel shows a summary of the main statistic data related with the last entity clicked.

.. todo::
    Include a screenshot.

For the explanation of this information refer to the section :ref:`statistics_panel`.

.. _status_panel_layout:

Status Panel
------------

This panel shows a collection of data related with the actual state of the application:

- Entities refer to the number of entities being monitored in the user application.

- Domains is a collection of the *Domains* that has been initialized in the Monitor.

.. todo::
    Include a screenshot.

For the explanation of this information refer to the section :ref:`status_panel`.

.. _log_panel_layout:

Log Panel
---------

This panel shows the callbacks that the application has obtained.
These callbacks refer to different events in the DDS network that is being monitored.
These callbacks could be cleared by using the :ref:`refresh_button`.
A callback may refer to:

- The discovery of a new Entity in the DDS network.

- The reception of new data related to any of the entities that are being monitored.

.. todo::
    Include a screenshot.

For the explanation of this information refer to the section :ref:`log_panel`.

.. _issues_panel_layout:

Issues Panel
------------

This panel is not available in this version of the Fast DDS Monitor.

.. _main_panel_layout:

Main Panel
==========

The central window it will display the data charts, so-called *Chartbox*, that the user has configured.
To create a new *Chartbox* go to *Edit->DisplayNewData* in the application menu.
This button will create a new *Chartbox* where new series could be added, removed or modified.

.. todo::
    Include a screenshot.

For further information about how to create a chart refer to the section :ref:`chart_panel`.

.. _chartbox_layout:

Chartbox
--------
These windows in the central panel store some *series* or *data configurations* to show a specific data type for
one or several entities in a specified time interval and with different accumulative operations on the data.

These Chartbox could be moved along the main window.
In order to move one of this charts, press in the *Chartbox* title and grab the object to its new location inside the
main panel.
The rest of the *Chartboxes* will automatically rearrange when one of them is moved to a different position.

.. todo::
    Include a screenshot.

.. _create_new_series_layout:

Create new Series Dialog
------------------------
This Dialog will appear every time a new Chartbox is created, or adding a new series by the button in the Chartbox
*Series->AddSeries*.

.. todo::
    Include a screenshot.

For further details on how to configure a new series refer to :ref:`create_serie`.
