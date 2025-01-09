#######################################
eProsima Fast DDS Monitor Documentation
#######################################

.. image:: /rst/figures/logo.png
  :height: 100px
  :width: 100px
  :align: left
  :alt: eProsima
  :target: http://www.eprosima.com/

*eProsima Fast DDS Monitor* is a graphical desktop application aimed at monitoring DDS environments deployed using the
*eProsima Fast DDS* library.
Thus, the user can monitor in real time the status of publication/subscription communications between DDS entities.
They can also choose from a wide variety of communication parameters to be measured (latency, throughput, packet loss,
etc.), as well as record and compute in real time statistical measurements on these parameters
(mean, variance, standard deviation, etc.).

Furthermore, the user can check the status of the deployed DDS network at any time, i.e. see for each DDS
Domain which DomainParticipants are instantiated, as well as their publishers and subscribers and the topics
under which they publish or to which they subscribe respectively.
It is also possible to see the physical architecture of the network on which the DDS applications that use *Fast DDS*
are running.

##################
Commercial Support
##################

Looking for commercial support? Write us to info@eprosima.com

Find more about us at `eProsima's webpage <https://eprosima.com/>`_.

########
Overview
########

*eProsima Fast DDS Monitor* is designed to meet the following criteria:

#. **Monitoring**: real-time tracking of network status and DDS communication.
#. **Intuitive**: graphical user interface developed following a user experience design approach.
#. **Introspection**: easily navigate through the deployed and active DDS entities being able to inspect their
   configuration and physical deployment.
#. **Troubleshooting**: detect at a glance the possible issues or anomalous events that may occur in the communication.

.. figure:: /rst/figures/screenshots/working_example.gif
    :align: center

.. warning::

    In order to monitor a DDS network deployed using *Fast DDS* library, compiling the latter with statistics and
    explicitly activating the statistics module is required. See :ref:`Fast DDS with Statistics module <fastdds-with-statistics>`
    for more details.

.. warning::

    If Fast DDS has been compiled with statistics and they are explicitly enabled and
    statistical data are not correctly received, only few data arrive or even none,
    configure the Fast DDS endpoints publishing statistics data with a less restrictive memory constraints.
    Please check the following
    `documentation <https://fast-dds.docs.eprosima.com/en/latest/fastdds/statistics/dds_layer/troubleshooting.html#troubleshooting>`_
    for more details on how to do this.

#################################
Contributing to the documentation
#################################

*Fast DDS Monitor Documentation* is an open source project, and as such all contributions, both in the form of
feedback and content generation, are most welcomed.
To make such contributions, please refer to the
`Contribution Guidelines <https://github.com/eProsima/all-docs/blob/master/CONTRIBUTING.md>`_ hosted in our GitHub
repository.

##############################
Structure of the documentation
##############################

This documentation is organized into the sections below.

* :ref:`Installation Manual <installation_manual_linux>`
* :ref:`Getting Started <entities>`
* :ref:`User Manual <initialize_monitoring>`
* :ref:`Developer Manual <developer_manual_installation_sources_linux>`
* :ref:`ROS2 <ros_section>`
* :ref:`Docker Image <docker>`
* :ref:`Release Notes <release_notes>`
