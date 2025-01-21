.. include:: ../exports/alias.include

.. _application_menu:

################
Application Menu
################

This section describes the operations that can be performed in *Fast DDS Monitor* through the application menu.

.. _application_menu_file:

File
====

.. _init_monitor_button:

Initialize DDS Monitor
----------------------

Button to start monitoring a new DDS network.
The entities of this network will be automatically discovered.
Moreover, their connections, their configuration and statistical data reported by them will be built and
displayed on the monitor for further user queries.

Section :ref:`monitor_domain` contains all the definitions and explanation about what monitoring a domain means in the
context of the application.

Pressing this button, a new Dialog will be displayed requesting the user to introduce a number between 0 and 200,
which will be the DDS Domain number. This will start a monitor in a specific DDS domain.
The entities in this domain will be automatically discovered.

.. note::
    Starting a monitor in a Domain already initialized will prompt an error message,
    and create an issue that can be found in :ref:`issues_panel`. Selecting ``Retry`` allows the user to select
    a different Domain.

Initialize Discovery Server Monitor
-----------------------------------

Button to start monitoring a new DDS network.
The entities of this network will be automatically discovered.
Moreover, their connections, their configuration and statistical data reported by them will be built and
displayed on the monitor for further user queries.

Section :ref:`monitor_domain` contains all the definitions and explanation about what monitoring a domain means in the
context of the application.

Pressing this button, a new Dialog will be displayed requesting the user to introduce a list of network addresses in
a specific string format to connect with one or more *Fast DDS Discovery Servers*.
This string must contain the IP-port pair where the Discovery Server is listening in the format ``ip:port``
separated by ``;``.

This will connect the *Fast DDS Monitor* to the Discovery Servers listening on the addresses set,
and it will get all the discovery information of the entities connecting through them.

.. note::
    Starting a monitor in a *Discovery Server* already initialized will prompt an error message,
    and create an issue that can be found in :ref:`issues_panel`. Selecting ``Retry`` allows the user to select
    a different *Discovery Server*.

Export Charts to CSV
--------------------

Export all the data displayed in the current Fast DDS Monitor session to a CSV file.
Please refer to section :ref:`export_data` for more information on the format of the generated CSV file.

.. _dump_button:

Dump
----

Dump the information from the database to a JSON file.
Please refer to section :ref:`export_data` for more information on the format of the generated JSON file.

.. _dump_clear_button:

Dump and clear
--------------

Same as the previous one but clearing the statistics data of all the entities.

Quit
----

Close the application.

.. _edit_menu:

Edit
====

.. _display_historic_data_button:

Display Historical Data
-----------------------
Create a new historic *Chartbox* in the :ref:`chart_panel_index`.
To know how to configure a historic *Chartbox*, please refer to the section :ref:`historic_series`.

.. _display_dynamic_data_button:

Display Real-Time Data
----------------------
Create a new dynamic *Chartbox* in the :ref:`chart_panel_index`.
To know how to configure a dynamic *Chartbox*, please refer to the section :ref:`dynamic_series`.

.. _clear_inactive_entities:

Delete inactive entities
------------------------

This button removes all the inactive entities from the database.

.. _delete_statistics_data:

Delete statistics data
----------------------

This button clear the statistics data of all the entities.

.. _schedule_delete:

Scheduler Configuration
-----------------------

Prompts a dialogue box allowing to create a schedule to dump the database to a file, remove old data and/or remove
inactive entities at a specified interval.

.. _refresh_button:

Refresh
-------
This button resets the entity clicked and the entities models in case there is some entity missing in the display.

.. _clear_log:

Clear Log
---------
This button clears the callbacks log.

.. _clear_issues:

Clear Issues
------------
This button clears the issues log.

.. _view_menu:

View
====

Hide/Show Inactive entities
---------------------------
The user of the application can decide whether to display the currently inactive entities.
In case they are shown, it will be possible to access the data related to them, while if they are hidden from the
monitor, they will no longer be available in the whole application framework.
The latter means that it will not be possible to plot charts with data relating to these entities.
This button hides/reveals the currently inactive entities detected by the monitor.

.. _hide_show_metatraffic:

Hide/Show Metatraffic
---------------------
Entities utilized for sharing metatraffic data are not shown by default.
These include Fast-DDS Statistics module topics and the ones used by ROS for metatraffic data exchange, as well as the
endpoints to which these topics are bound.
As with the hide/show inactive entities feature, when metatraffic entities are hidden they are no longer available
in the whole application framework.
This button displays/hides the metatraffic entities detected by the monitor.

Dashboard Layout
----------------
Changes the size of the chart boxes displayed in the :ref:`chart_panel_index` of the application.
Three mutually exclusive layout options are defined and explained below.

 * |dashboard_layout_1| **Large**: A single full-screen chart is displayed.
 * |dashboard_layout_2| **Medium**: Adjusts the chart size to show two chart boxes per row.
 * |dashboard_layout_3| **Small**: Adjusts the chart size to show three chart boxes per row.

Hide/Show Shortcuts Toolbar
---------------------------
Hide the shortcuts superior toolbar if visible, or reveal it otherwise.

Customize Shortcuts Toolbar
---------------------------
Allows to show or hide independently the shortcut buttons in the shortcut toolbar.

Hide/Show Left sidebar
----------------------
Hide the left sidebar if visible, or reveal it otherwise.

Customize Left sidebar
----------------------
Allows to show or hide independently the different panels in the :ref:`left_panel`.

Help
====

Documentation
-------------

Link to this documentation.

Release Notes
-------------

Link to the `Releases <https://github.com/eProsima/Fast-DDS-monitor/releases>`_ section of the
`GitHub Fast DDS Monitor repository`_.

Join Us on Twitter
------------------
Link to `eProsima Twitter account <https://twitter.com/EProsima>`_.

Search Feature Requests
-----------------------
Link to the `Issues`_ section of the `GitHub Fast DDS Monitor repository`_.

Report Issue
------------
Link to create a new Issue in the `Issues`_ section of the `GitHub Fast DDS Monitor repository`_.

.. todo::
    Explain the form to add an issue.

About
-----
General information of the currently running *Fast DDS Monitor* application.

.. _GitHub Fast DDS Monitor repository: https://github.com/eProsima/Fast-DDS-monitor
.. _Issues: https://github.com/eProsima/Fast-DDS-monitor/issues
