.. _ros_section:

###########################
Fast DDS Monitor with ROS 2
###########################

Fast DDS Monitor is a useful tool for monitoring and studying a ROS 2 network.
The automatic discovery of entities in a local network allows to easily see the different Participants that
are running, as well as their Endpoints, the Topics each one is using, and even the network interfaces they are using
to communicate with each other.
Additionally, one could receive statistical data from every endpoint in the network.
This data is very useful to analyze the performance and seek any possible communication problem in the network.

ROS 2 relies on DDS communication protocol to communicate different nodes.
There are different RMWs (ROS MiddleWare) available in the latest ROS 2 versions.
Make sure you are using Fast DDS as your ROS 2 middleware in order to receive statistical data and monitor your network.

In the following sections, instructions for using Fast DDS with Statistics in the latest ROS 2 version are provided,
as well as a brief tutorial demonstrating the integration of Fast DDS Monitor with ROS 2 in a simple scenario.

.. toctree::
   :maxdepth: 2

   jazzy/jazzy
