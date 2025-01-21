#######################################
eProsima Fast DDS Monitor Documentation
#######################################

.. image:: /rst/figures/Logo.png
  :height: 100px
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
they publish under or they subscribe to, respectively.
It is also possible to visualize the physical architecture of the network on which the DDS applications that use
*Fast DDS* are running.

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

.. figure:: /rst/figures/screenshots/working_example2.gif
    :align: center

The source code for the Monitor application and the documentation can be found in our
`GitHub repository <https://github.com/eProsima/Fast-DDS-monitor>`_.

############
Contributing
############

*Fast DDS Monitor* is an open source project, and as such all contributions, both in the form of
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
* :ref:`ROS 2 <ros_section>`
* :ref:`Docker Image <docker>`
* :ref:`Release Notes <release_notes>`
