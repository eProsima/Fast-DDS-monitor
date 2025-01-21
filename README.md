[![Fast DDS](resources/images/monitor_repo_banner.png)](https://www.eprosima.com/middleware/tools/fast-dds-monitor)

<br>

<div class="menu" align="center">
    <strong>
        <a href="https://eprosima.com/index.php/downloads-all">Download</a>
        <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
        <a href="https://fast-dds-monitor.readthedocs.io/en/latest/">Docs</a>
        <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
        <a href="https://eprosima.com/index.php/company-all/news">News</a>
        <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
        <a href="https://twitter.com/EProsima">Twitter</a>
        <span>&nbsp;&nbsp;•&nbsp;&nbsp;</span>
        <a href="mailto:info@eprosima.com">Contact Us</a>
    </strong>
</div>

<br><br>

<div class="badges" align="center">
    <a href="https://www.gnu.org/licenses/gpl-3.0.en.html"><img alt="License" src="https://img.shields.io/github/license/eProsima/Fast-DDS-monitor.svg"/></a>
    <a href="https://github.com/eProsima/Fast-DDS-monitor/releases"><img alt="Releases" src="https://img.shields.io/github/v/release/eProsima/Fast-DDS-monitor?sort=semver"/></a>
    <a href="https://github.com/eProsima/Fast-DDS-monitor/issues"><img alt="Issues" src="https://img.shields.io/github/issues/eProsima/Fast-DDS-monitor.svg"/></a>
    <a href="https://github.com/eProsima/Fast-DDS-monitor/network/members"><img alt="Forks" src="https://img.shields.io/github/forks/eProsima/Fast-DDS-monitor.svg"/></a>
    <a href="https://github.com/eProsima/Fast-RTPS/stargazers"><img alt="Stars" src="https://img.shields.io/github/stars/eProsima/Fast-DDS-monitor.svg"/></a>
    <br>
    <a href="https://github.com/eProsima/Fast-DDS-monitor/actions/workflows/nightly.yml"><img alt="test" src="https://github.com/eProsima/Fast-DDS-monitor/actions/workflows/nightly.yml/badge.svg"/></a>
    <a href="https://fast-dds-monitor.readthedocs.io/en/latest/"><img alt="Documentation Status" src="https://readthedocs.org/projects/fast-dds-monitor/badge/?version=latest"></a>
</div>

<br><br>

*eProsima Fast DDS Monitor* is a graphical desktop application aimed at monitoring DDS environments deployed using the
*eProsima Fast DDS* library.
Thus, the user can monitor in real time the status of publication/subscription communications between DDS entities.
They can also choose from a wide variety of communication parameters to be measured (latency, throughput, packet loss,
etc.), as well as record and compute in real time statistical measurements on these parameters
(mean, variance, standard deviation, etc.).

Furthermore, the user can check the status of the deployed DDS network at any time, i.e. see for each DDS
Domain which DomainParticipants are instantiated, as well as their publishers and subscribers and the topics
they publish under or they subscribe to, respectively.
It is also possible to visualize the physical architecture of the network on which the DDS applications that use *Fast DDS*
are running.

*eProsima Fast DDS Monitor* is designed to meet the following criteria:

* **Monitoring**: real-time tracking of network status and DDS communication.
* **Intuitive**: graphical user interface developed following a user experience design approach.
* **Introspection**: easily navigate through the deployed and active DDS entities being able to inspect their
   configuration and physical deployment.
* **Troubleshooting**: detect at a glance the possible issues or anomalous events that may occur in the communication.

<div align="center">
    <img src="docs/rst/figures/screenshots/working_example2.gif" alt="Example of use">
</div>

## Commercial support

Looking for commercial support? Write us to info@eprosima.com

Find more about us at [eProsima’s webpage](https://eprosima.com/).

---

## Documentation

You can access the documentation online, which is hosted on [Read the Docs](https://fast-dds-monitor.readthedocs.io/en/latest/index.html).

* [Installation Manual](https://fast-dds-monitor.readthedocs.io/en/latest/rst/installation/linux.html)
* [Getting Started](https://fast-dds-monitor.readthedocs.io/en/latest/rst/getting_started/entities.html)
* [User Manual](https://fast-dds-monitor.readthedocs.io/en/latest/rst/user_manual/initialize_monitoring.html)
* [Developer Manual](https://fast-dds-monitor.readthedocs.io/en/latest/rst/developer_manual/installation/sources/linux.html)
* [ROS 2](https://fast-dds-monitor.readthedocs.io/en/latest/rst/ros/ros.html)
* [Docker Image](https://fast-dds-monitor.readthedocs.io/en/latest/rst/docker/docker.html)
* [Release Notes](https://fast-dds-monitor.readthedocs.io/en/latest/rst/notes/notes.html)
