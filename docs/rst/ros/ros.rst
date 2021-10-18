.. _ros_section:

###########################
Fast DDS Monitor with ROS 2
###########################

Fast DDS Monitor is a very useful tool to monitor and study a ROS 2 network.
The automatic discovery of entities in a local network allows to easily see the different Participants that
are running, as its endpoints, the topics that each one is using, and even the network interfaces that are being
used to communicate each other.
Additionally, you could receive statistics data from every endpoint in the network.
This data is very useful to analyze the performance and seek any possible communication problem in the network.

ROS 2 relies on DDS communication protocol to communicate different nodes.
There are different RMWs (ROS MiddleWare) available in the latest ROS 2 versions.
Just be sure to use Fast DDS as your ROS 2 middleware in order to receive statistic data and monitor your network.

In the following sections are described how to use Fast DDS with Statistics active in different ROS2 versions.

.. toctree::
   :maxdepth: 2

   galactic/galactic
