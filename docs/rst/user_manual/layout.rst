.. include:: ../exports/alias.include

.. _layout:

######
Layout
######

This section explains the User Interface and the Layout of the application.
It will briefly explain the main menus and windows that could be seen, in order to familiarize the user
with where to find the buttons and information.

.. _application_menu_layout:

Application Menu
================

This general menu contains all the buttons available for this application divided in 4 groups:

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

This horizontal bar contains the buttons in *ApplicationMenu->Edit*
so the user has a faster access to the main functionalities.
This bar could be configured in *ApplicationMenu->View*.

.. todo::
    Include a screenshot.

For the explanation of how to configure this bar refer to the section :ref:`shortcuts_bar`.

.. _left_sidebar_layout:

Left Sidebar
============

In this side bar it will be shown the different entities that has been discovered by the monitor.
They will be displayed in interactive lists that the user could press in order to select a specific entity.

For more information about what is an entity and how are they divided refer to :ref:`entities`.
For more information about what means to select an entity refer to :ref:`selected_entity`.

DDS Panel
---------

In this panel it will appear the DDS Entities of the monitor.
This entities are the DDS *DomainParticipant*, the DDS *DataReader* and *DataWriters* and the transport *Locators* that
each entity is using.
This panel will be filled with the entities that are related with the entity currently selected,
so could happen that not all the DDS entities discovered appears in this panel at a certain point.

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

**Physical** entities refer to the main information of the machine and the context where a *DomainParticipant*
is being executed.
This information is divided in *Host*, *User* and *Process*.
For the explanation of this entities and the interaction with them refer to the section :ref:`physical_panel`.

.. _right_sidebar_layout:

Right Sidebar
=============

.. _info_panel_layout:

Info Panel
----------

This panel shows the main information of the last entity clicked.
This information differs depending on the kind of the entity.
i.e. For a *DDS entity*, the *QoS* information would be shown, while for a *Process* it will be displayed the *pid*.

.. todo::
    Include a screenshot.

For the explanation of this entities and the interaction with them refer to the section :ref:`info_panel`.

.. _statistics_panel_layout:

Statistics Panel
----------------

This panel shows a summary of the main statistic data related with the entity clicked.

.. todo::
    Include a screenshot.

For the explanation of this entities and the interaction with them refer to the section :ref:`statistics_panel`.

Issues Panel
------------

This panel shows a collection of news and issues that the monitor has received.
The information stored is divided in three groups:

- Callbacks that are received related with new entities discovered in the network.
  This callbacks are erased every time *Refresh* is pressed.

- Domains that are being monitoring at the moment.
- Issues and problems automatically detected in the actual execution.

.. todo::
    Include a screenshot.

For the explanation of this entities and the interaction with them refer to the section :ref:`statistics_panel`.

.. _main_panel_layout:

Main Panel
==========

In the central window it will be displayed the data charts or *Chartbox* that the user has configured.
To create a new chart use the button *ApplicationMenu->Edit->DisplayNewData*. This button will create a new
*Chartbox* where new series could be added, removed or modified.

For further information about how to create a chart refer to the section :ref:`chart_panel`.

.. todo::
    Include a screenshot.

.. _chartbox_layout:

Chartbox
--------
This windows in the central panel store some *series* or *data configurations* to show a specific data type for
one or several entities in a time interval and with different accumulative processes.

These Chartbox could be moved along the main window.
In order to move one of this charts, press in the Chart title and grab the object to the new location inside the
main panel.
The rest of the panels will automatically rearrange when one panel is being moved.

.. todo::
    Include a screenshot.

.. _create_new_series_layout:

Create new Serie Dialog
-----------------------
This Dialog will appear every time a new Chartbox is created, or adding a new series by the button in the Chartbox
*Series->AddSeries*.

.. todo::
    Include a screenshot.
