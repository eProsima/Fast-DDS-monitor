.. include:: ../exports/alias.include

.. _application_menu:

################
Application Menu
################

This section describes the operations that can be performed in *Fast DDS Monitor* through the application menu.

File
====

.. _init_monitor_button:

Initialize Monitor
----------------------
Button to start monitoring a new DDS network.
The entities of this network will be automatically discovered.
Moreover, their connections, their configuration and statistical data reported by them will be built and
displayed on the monitor for further user queries.

Section :ref:`monitor_domain` contains all the definitions and explanation about what monitor a domain means in the
context of the application.

Pressing this button, a new Dialog with two tabs will be displayed.
Each tab allows to start a monitor in a DDS network deployed using the Simple Discovery Protocol (SDP)
or the Fast DDS Discovery Server (DS).

.. warning::
    Starting a monitor in a domain or *Discovery Server* already initialize will duplicate the entities in them
    and may lead to an undefined behavior.

Simple Discovery
^^^^^^^^^^^^^^^^
This dialog requests the user to introduce a number between 0 and 200 which will be the DDS Domain number.
This will start a monitor in a specific DDS domain.
The entities in this domain will be automatically discovered.

Discovery Server
^^^^^^^^^^^^^^^^
This dialog requests the user to introduce a list of network addresses in a specific string format to connect with one
or more *Fast DDS Discovery Servers*.
This string must contain the IP-port pair where the Discovery Server is listening in the format ``ip:port``
separated by ``;``.

This will connect the *Fast DDS Monitor* to the Discovery Servers listening on the addresses set,
and it will get all the discovery information of the entities connecting through them.

Quit
----
Close the application.

.. _edit_menu:

Edit
====

.. _display_historic_data_button:

Display Historical Data
-----------------------
Create a new historic *Chartbox* in the central panel.
To know how to configure a historic *Chartbox*, please refer to the section :ref:`historic_series`.

.. _display_dynamic_data_button:

Display Dynamic Data
--------------------
Create a new dynamic *Chartbox* in the central panel.
To know how to configure a dynamic *Chartbox*, please refer to the section :ref:`dynamic_series`.

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

View
====

Hide/Show Shortcuts Toolbar
---------------------------
Hide the shortcuts superior toolbar if visible, or reveal it otherwise.

Customize Shortcuts Toolbar
---------------------------
Allow to show or hide independently the shortcut buttons in the shortcut toolbar.

Hide/Show Left sidebar
----------------------
Hide the left sidebar if visible, or reveal it otherwise.

Help
====

Documentation
-------------

Link to this documentation.

Release Notes
-------------

.. warning::
    Button not supported.

Join Us on Twitter
------------------
Link to `eProsima Twitter account <https://twitter.com/EProsima>`_.

Search Feature Requests
-----------------------
Link to the *issues* section of the Fast DDS Monitor repository in
`GitHub <https://github.com/eProsima/Fast-DDS-monitor/issues>`_.

Report Issue
------------
Link to the *issues* section of the Fast DDS Monitor repository in
`GitHub <https://github.com/eProsima/Fast-DDS-monitor/issues>`_.

.. todo::
    Explain the form to add an issue.

About
-----
General information of the currently running *Fast DDS Monitor* application.
