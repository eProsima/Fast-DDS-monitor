.. include:: ../../exports/alias.include

.. _pro_application_menu:

################
Application Menu
################

This section describes the operations available through the *Fast DDS Monitor Pro* application menu.

.. _pro_application_menu_file:

File
====

.. _pro_init_monitor_button:

Initialize DDS Monitor
----------------------

Opens a dialog to start monitoring a new DDS network.
Enter the DDS Domain number (0–200) to start a monitor on that domain.
Entities in the domain are discovered automatically, and their connections, configuration, and
statistical data are collected and displayed.

See :ref:`monitor_domain` for a full explanation of domain monitoring.

.. note::
    Starting a monitor on a domain that is already initialized shows an error message and creates an
    entry in the :ref:`pro_issues_panel`. Select **Retry** to choose a different domain.

Initialize Discovery Server Monitor
------------------------------------

Opens a dialog to start monitoring a DDS network through one or more *Fast DDS Discovery Servers*.
Enter a semicolon-separated list of ``ip:port`` address pairs for the servers to connect to.

The monitor connects to the Discovery Servers at the specified addresses and collects all discovery
information for the entities communicating through them.

See :ref:`monitor_domain` for a full explanation.

.. note::
    Starting a monitor on a Discovery Server that is already initialized shows an error message and
    creates an entry in the :ref:`pro_issues_panel`. Select **Retry** to choose a different server.

Export Charts to CSV
--------------------

Exports all chart data from the current session to a CSV file.
See :ref:`pro_export_data` for details on the file format.

.. _pro_dump_button:

Dump
----

Dumps the contents of the statistics database to a JSON file.
See :ref:`pro_export_data` for details on the file format.

.. _pro_dump_clear_button:

Dump and Clear
--------------

Same as **Dump**, but also clears the statistics data for all entities.

Quit
----

Closes the application.

.. _pro_edit_menu:

Edit
====

.. _pro_display_historic_data_button:

Display Historical Data
-----------------------

Creates a new historical *Chartbox* in the :ref:`pro_chart_panel`.
See :ref:`historic_series` for details on configuring a historical Chartbox.

.. _pro_display_dynamic_data_button:

Display Real-Time Data
----------------------

Creates a new real-time *Chartbox* in the :ref:`pro_chart_panel`.
See :ref:`dynamic_series` for details on configuring a real-time Chartbox.

.. _pro_clear_inactive_entities:

Delete Inactive Entities
------------------------

Removes all inactive entities from the database.

.. _pro_delete_statistics_data:

Delete Statistics Data
----------------------

Clears the statistics data for all entities.

.. _pro_schedule_delete:

Scheduler Configuration
-----------------------

Opens a dialog to schedule periodic database dumps, data removal, and/or inactive-entity cleanup
at a specified interval.

.. _pro_alerts_configuration:

Alerts Configuration
--------------------

Opens a dialog to edit the notification and alert system settings.

.. _pro_refresh_button:

Refresh
-------

Resets the selected entity and the entity models.
Use this if an entity appears to be missing from the display.

.. _pro_clear_log:

Clear Log
---------

Clears the callbacks log.

.. _pro_clear_issues:

Clear Issues
------------

Clears the issues log.

.. _pro_view_menu:

View
====

Hide/Show Proxy Entities
------------------------

Toggles the display of proxy entities — entities from other domains whose statistics are reaching
the monitor's domain.
When hidden, proxy entities are not available anywhere in the application, including chart data.
The default behavior is to hide proxy entities.

Hide/Show Inactive Entities
----------------------------

Toggles the display of currently inactive entities.
When hidden, inactive entities are not available anywhere in the application, including chart data.

.. _pro_hide_show_metatraffic:

Hide/Show Metatraffic
---------------------

Toggles the display of metatraffic entities.
By default, these entities — including *Fast DDS* Statistics module topics, ROS metatraffic topics,
and their associated endpoints — are hidden.
When hidden, metatraffic entities are not available anywhere in the application, including chart data.

Revert/Perform ROS 2 Demangling
---------------------------------

By default, ROS 2 types are demangled to recover the original type name and IDL representation in the
IDL view, and to improve compatibility with *Fast DDS Gen* IDL usage.
Demangled IDLs display a badge in the corner of the IDL view.
This option toggles the demangling on or off.

Dashboard Layout
----------------

Changes the size of the Chartboxes in the :ref:`pro_chart_panel`.
Three mutually exclusive layouts are available:

* |dashboard_layout_1| **Large**: One full-screen chart.
* |dashboard_layout_2| **Medium**: Two charts per row.
* |dashboard_layout_3| **Small**: Three charts per row.

Hide/Show Shortcuts Toolbar
---------------------------

Hides or reveals the shortcuts toolbar.

Customize Shortcuts Toolbar
---------------------------

Independently shows or hides individual buttons in the shortcuts toolbar.

Hide/Show Left Sidebar
----------------------

Hides or reveals the left sidebar.

Customize Left Sidebar
----------------------

Independently shows or hides individual panels within the :ref:`pro_left_panel`.

Help
====

Documentation
-------------

Opens this documentation.

Release Notes
-------------

Link to the `Releases <https://github.com/eProsima/Fast-DDS-monitor/releases>`_ section of the
`GitHub Fast DDS Monitor repository`_.

Join Us on Twitter
------------------

Link to the `eProsima Twitter account <https://twitter.com/EProsima>`_.

Search Feature Requests
-----------------------

Link to the `Issues`_ section of the `GitHub Fast DDS Monitor repository`_.

Report Issue
------------

Link to create a new issue in the `Issues`_ section of the `GitHub Fast DDS Monitor repository`_.

About
-----

Displays general information about the currently running *Fast DDS Monitor Pro* application.

.. _GitHub Fast DDS Monitor repository: https://github.com/eProsima/Fast-DDS-monitor
.. _Issues: https://github.com/eProsima/Fast-DDS-monitor/issues
