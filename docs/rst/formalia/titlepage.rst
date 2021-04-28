.. raw:: html

  <h1>
    eProsima Fast DDS Monitor Documentation
  </h1>

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

*eProsima Fast DDS Monitor* is designed to meet the following criteria:

#. **Monitoring**: real-time tracking of network status and DDS communication.
#. **Intuitive**: graphical user interface developed following a user experience design approach.
#. **Introspection**: easily navigate through the deployed and active DDS entities being able to inspect their
   configuration and physical deployment.
#. **Troubleshooting**: detect at a glance the possible issues or anomalous events that may occur in the communication.

.. warning::
  This application is in the early stages of development.
  For this reason, it should not be considered stable, as the design and functionality may change significantly
  before the first release.
  Furthermore, several features may not be implemented yet.


#############
Main Features
#############
