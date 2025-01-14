.. _fast_dds_suite:

Fast DDS Suite
==============

This Docker image contains the complete Fast DDS suite. This includes:

- :ref:`eProsima Fast DDS libraries and examples <fast_dds_suite_examples>`: *eProsima Fast DDS* is a C++
  implementation of the `DDS (Data Distribution Service) Specification <https://www.omg.org/spec/DDS/About-DDS/>`__,
  a protocol defined by the `Object Management Group (OMG) <https://www.omg.org/>`__.
  The *eProsima Fast DDS* library provides both an Application Programming Interface (API) and a communication protocol
  that deploy a Data-Centric Publisher-Subscriber (DCPS) model, with the purpose of establishing efficient and reliable
  information distribution among Real-Time Systems. *eProsima Fast DDS* is predictable, scalable, flexible, and
  efficient in resource handling.

  This Docker Image contains the Fast DDS libraries bundled with several examples that showcase a variety of
  capabilities of eProsima's Fast DDS implementation.

  You can read more about Fast DDS on the `Fast DDS documentation page <https://fast-dds.docs.eprosima.com/en/latest/>`_.

- :ref:`Shapes Demo <fast_dds_suite_shapes_demo>`: eProsima Shapes Demo is an application in which Publishers and
  Subscribers are shapes of different colors and sizes moving on a board. Each shape refers to its own topic: Square,
  Triangle or Circle. A single instance of the eProsima Shapes Demo can publish on or subscribe to several topics at
  a time.

  You can read more about this application on the `Shapes Demo documentation page <https://eprosima-shapes-demo.readthedocs.io/>`_.

- :ref:`Fast DDS Monitor <fast_dds_suite_monitor>`: eProsima Fast DDS Monitor is a graphical desktop application aimed
  at monitoring DDS environments deployed using the *eProsima Fast DDS* library. Thus, the user can monitor in real
  time the status of publication/subscription communications between DDS entities. They can also choose from a wide
  variety of communication parameters to be measured (latency, throughput, packet loss, etc.), as well as record and
  compute in real time statistical measurements on these parameters (mean, variance, standard deviation, etc.).

To load this image into your Docker repository, from a terminal run

.. code-block:: bash

 $ docker load -i ubuntu-fastdds-suite\ <FastDDS-Version>.tar

You can run this Docker container as follows

.. code-block:: bash

 $ xhost local:root
 $ docker run -it --privileged -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix \
 ubuntu-fastdds-suite:<FastDDS-Version>

From the resulting Bash Shell you can run each feature.

.. _fast_dds_suite_examples:

Fast DDS Examples
-----------------

Included in this Docker container is a set of binary examples that showcase several functionalities of the
Fast DDS libraries. These examples' path can be accessed from a terminal by typing

.. code-block:: bash

 $ goToExamples

From this folder you can access all examples, both for DDS and RTPS. We detail the steps to launch one such
example below.

Hello World Example
^^^^^^^^^^^^^^^^^^^

This is a minimal example that will perform a Publisher/Subscriber match and start sending samples.

.. code-block:: bash

 $ goToExamples
 $ cd hello_world/bin
 $ tmux new-session "./hello_world publisher 0 1000" \; \
 split-window "./hello_world subscriber" \; \
 select-layout even-vertical

This example is not constrained to the current instance. It is possible to run several instances of this
container to check the communication between them by running the following from each container.

.. code-block:: bash

 $ goToExamples
 $ cd hello_world/bin
 $ ./hello_world publisher

or

.. code-block:: bash

 $ goToExamples
 $ cd hello_world/bin
 $ ./hello_world subscriber

.. _fast_dds_suite_shapes_demo:

Shapes Demo
-----------

To launch the Shapes Demo, from a terminal run

.. code-block:: bash

 $ ShapesDemo

eProsima Shapes Demo usage information can be found on the `Shapes Demo First Steps
<https://eprosima-shapes-demo.readthedocs.io/en/latest/first_steps/first_steps.html>`_.

.. _fast_dds_suite_monitor:

Fast DDS Monitor
----------------

To launch the Fast DDS Monitor, from a terminal run

.. code-block:: bash

 $ fastdds_monitor

eProsima Fast DDS Monitor usage information can be located on the `Fast DDS Monitor User Manual
<https://fast-dds-monitor.readthedocs.io/en/latest/rst/user_manual/initialize_monitoring.html>`_.
