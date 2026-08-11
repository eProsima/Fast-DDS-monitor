.. include:: ../exports/alias.include

.. _installation_manual_linux:

#########################
DDS Monitor on Linux
#########################

This section provides instructions on how to install the *DDS Monitor* application.
This is available on the `eProsima <https://www.eprosima.com/>`_ website in the
`Downloads <https://www.eprosima.com/index.php/downloads-all>`_ section.

There are two mechanisms for running the monitor application.

- Through the *DDS Monitor* installer.
- Using the *AppImage* format, which is a portable format of the application software.

*DDS Monitor* installer
============================

The first option is to install the *DDS monitor* application together with all its dependencies.
To do so, first run the ``eProsima_DDS-Monitor-<FastDDS-Version>-Linux.run`` executable,
(you might need to make the file executable by running
``chmod +x eProsima_DDS-Monitor-<FastDDS-Version>-Linux.run`` first)
and follow the instructions it provides to install the program in a directory on the system.

.. figure:: /rst/figures/installer_linux.png
    :align: center

*DDS Monitor* portable format
==================================

*eProsima* also distributes a portable version of the *DDS Monitor* for Linux in AppImage format.
In this case, download this version from the
`eProsima Downloads website <https://www.eprosima.com/index.php/downloads-all>`_ and run the downloaded
file to launch the monitor.
The name of this file is ``eProsima_DDS-Monitor-<FastDDS-Version>-Linux.AppImage``.


.. warning::

    In case these files are not executed, check that they have executable permissions.
