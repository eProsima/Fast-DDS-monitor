# Fast DDS Monitor

<a href="http://www.eprosima.com"><img src="https://encrypted-tbn3.gstatic.com/images?q=tbn:ANd9GcSd0PDlVz1U_7MgdTe0FRIWD0Jc9_YH-gGi0ZpLkr-qgCI6ZEoJZ5GBqQ" align="left" hspace="8" vspace="2" width="100" height="100" ></a>


[![License](https://img.shields.io/github/license/eProsima/Fast-DDS-monitor.svg)](https://www.gnu.org/licenses/gpl-3.0.en.html)
[![Releases](https://img.shields.io/github/v/release/eProsima/Fast-DDS-monitor?sort=semver)](https://github.com/eProsima/Fast-DDS-monitor/releases)
[![Issues](https://img.shields.io/github/issues/eProsima/Fast-DDS-monitor.svg)](https://github.com/eProsima/Fast-DDS-monitor/issues)
[![Forks](https://img.shields.io/github/forks/eProsima/Fast-DDS-monitor.svg)](https://github.com/eProsima/Fast-DDS-monitor/network/members)
[![Stars](https://img.shields.io/github/stars/eProsima/Fast-DDS-monitor.svg)](https://github.com/eProsima/Fast-RTPS/stargazers)
[![test](https://github.com/eProsima/Fast-DDS-monitor/actions/workflows/test.yml/badge.svg)](https://github.com/eProsima/Fast-DDS-monitor/actions/workflows/test.yml)
[![codecov](https://codecov.io/gh/eProsima/Fast-DDS-monitor/branch/main/graph/badge.svg?token=6NA5PVA9QL)](https://codecov.io/gh/eProsima/Fast-DDS-monitor)
[![Documentation Status](https://readthedocs.org/projects/fast-dds-monitor/badge/?version=latest)](https://fast-dds-monitor.readthedocs.io/en/latest/)

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

* **Monitoring**: real-time tracking of network status and DDS communication.
* **Intuitive**: graphical user interface developed following a user experience design approach.
* **Introspection**: easily navigate through the deployed and active DDS entities being able to inspect their
   configuration and physical deployment.
* **Troubleshooting**: detect at a glance the possible issues or anomalous events that may occur in the communication.

---
**NOTE**

In order to monitor a DDS network deployed using *Fast DDS* library, compiling the latter with statistics and
explicitly activating the statistics module is required. See [Example of Usage](https://fast-dds-monitor.readthedocs.io/en/latest/rst/getting_started/tutorial.html)
for a complete walkthrough example showing how to fulfill these requirements.

---

## Documentation

You can access the documentation online, which is hosted on [Read the Docs](https://fast-dds-monitor.readthedocs.io/en/latest/index.html).

* [Installation Manual](https://fast-dds-monitor.readthedocs.io/en/latest/rst/installation/linux.html)
* [Getting Started](https://fast-dds-monitor.readthedocs.io/en/latest/rst/getting_started/entities.html)
* [User Manual](https://fast-dds-monitor.readthedocs.io/en/latest/rst/user_manual/initialize_monitoring.html)
* [Developer Manual](https://fast-dds-monitor.readthedocs.io/en/latest/rst/developer_manual/installation/sources/linux.html)
* [Release Notes](https://fast-dds-monitor.readthedocs.io/en/latest/rst/notes/notes.html)
