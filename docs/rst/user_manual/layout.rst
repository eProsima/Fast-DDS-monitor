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

For more information about what is an entity and how they are organized refer to :ref:`entities`.
For more information about what means to select an entity refer to :ref:`selected_entity`.

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

Physical/Logical Panel
----------------------

In this panel it will appear the Entities discovered by the monitor that are not DDS Entities.
These entities are divided in two groups, the *Logical* entities and the *Physical* entities.

.. todo::
    Include a screenshot.

**Logical** entities refer to the DDS *Domain* and *Topic* entities.
For the explanation of this entities and the interaction with them refer to the section :ref:`logical_panel`.

**Physical** entities refer to the main information of the machine and the context where an application using
*Fast DDS* is running.
These *Fast DDS Monitor* entities are *Host*, *User* and *Process*.
For the explanation of this entities and the interaction with them refer to the section :ref:`physical_panel`.

.. _right_sidebar_layout:

Right Sidebar
=============

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

Issues Panel
------------

This panel shows a collection of news and issues that the monitor has received.
The information stored is divided in three groups:

- Callbacks that are received related with new entities discovered in the network.
  The callbacks list is cleaned every time the *Refresh* button available in *Edit* in the application menu is pressed.

- Domains that are currently being monitored.
- Issues and problems automatically detected in the actual execution.

.. todo::
    Include a screenshot.

For the explanation of this information refer to the section :ref:`statistics_panel`.

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

Create new Serie Dialog
-----------------------
This Dialog will appear every time a new Chartbox is created, or adding a new series by the button in the Chartbox
*Series->AddSeries*.

.. todo::
    Include a screenshot.

For further details on how to configure a new serie refer to :ref:`create_serie`.
