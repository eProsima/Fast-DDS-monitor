.. include:: ../exports/alias.include

.. _application_menu:

################
Application Menu
################

Functionality related with :ref:`application_menu_layout`.

File
====

.. note::
    In future versions, this menu will contain generic buttons as open, save, etc.

Quit
----
Close the application.

.. _edit_menu:

Edit
====

.. _init_monitor_button:

Initialize New Monitor
----------------------
Button to start monitoring a new DDS network.
The entities in this network will be discovered automatically, and their connections and data will be built and
display in the monitor for further queries from the user.
Be aware that the discovery of this entities is made by DDS protocols, and so they will not be instantaneous or
simultaneous.

.. warning::
    Starting a monitor in a domain or *Discovery Server* already initialize will duplicate the entities in them
    and may lead to an **undefined behaviour**.

Pressing this button, a new Dialog will be displayed with two tabs.
Each of them allows to start a monitoring with different discovery protocols.

Simple Discovery
^^^^^^^^^^^^^^^^
Ask to introduce a number between 0 and 200.

This will allow to monitor a specific domain and all the DDS entities that are communicating in this domain
in the *Fast-DDS* statistics topics.
The entities in this domain will be discovered automatically, and their connections and data will be built and
display in the monitor for further queries from the user.

Discovery Server
^^^^^^^^^^^^^^^^
Ask to introduce a string with addresses to connect with a *Discovery Server*.
This string must contain addresses in a format ``ip:port`` separated by ``;``.

This will connect to the Discovery Servers listening in the addresses set, and will get all the discovery information
of the entities connecting through them.

Display New Data
----------------
Create a new *Chart* window in central panel.

To know how to configure a *Chart* refer to the section :ref:`chart_panel`.

.. _refresh_button:

Refresh
-------
This button reset several points in the monitor:

- It erases the callback information in *Issues* right panel.
- It reset the entity clicked, setting as clicked an abstract *All* entity that represents all the discovered ones.

View
====

Hide/Show Shortcuts Toolbar
---------------------------
Hide the shortcuts superior toolbar if visible, or reveal it otherwise.

Customize Shortcuts Toolbar
---------------------------
Allows to show or hide independently the shortcut buttons in the shortcut toolbar.

Hide/Show Left sidebar
----------------------
Hide the left sidebar if visible, or reveal it otherwise.

Hide/Show Right sidebar
------------------------
Hide the right sidebar if visible, or reveal it otherwise.

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
Link to `eProsima Twitter account <https://twitter.com/EProsima>`.

Search Feature Requests
-----------------------
Link to this project *issues* github page.

Report Issue
------------
Link to this project *issues* github page.

About
-----
General information of the application.
