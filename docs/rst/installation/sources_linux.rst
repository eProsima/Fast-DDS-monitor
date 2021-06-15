.. _linux_sources:

################################################
Fast DDS Monitor Linux installation from sources
################################################

The instructions for installing the *eProsima Fast DDS Monitor application* from sources and the required
`Qt` installation are provided in this page.
It is organized as follows:

.. contents::
    :local:
    :backlinks: none
    :depth: 2

.. _fastdds_lib_sl:

******************************************
Fast DDS Monitor dependencies installation
******************************************

Fast DDS Monitor depends on eProsima Fast DDS library, eProsima Fast DDS Statistics Backend library, Qt and
certain debian packages.

Requirements
============

The installation of *eProsima Fast DDS* in a Linux environment from binaries requires the following tools to be
installed in the system:

* :ref:`cmake_gcc_pip_wget_git_sl`
* :ref:`colcon_install`
* :ref:`gtest_sl` [for test only]

.. _cmake_gcc_pip_wget_git_sl:

CMake, g++, pip, wget and git
-----------------------------

These packages provide the tools required to install *eProsima Fast DDS* and its dependencies from command line.
Install CMake_, `g++ <https://gcc.gnu.org/>`_, pip_, wget_ and git_ using the package manager of the appropriate
Linux distribution. For example, on Ubuntu use the command:

.. code-block:: bash

    sudo apt install cmake g++ pip wget git

.. _gtest_sl:

.. _colcon_install:

Colcon
------

colcon_ is a command line tool based on CMake_ aimed at building sets of software packages.
This section explains how to use it to compile *eProsima Fast DDS* and its dependencies.
Install the ROS 2 development tools (colcon_ and vcstool_) by executing the following command:

   .. code-block:: bash

       pip3 install -U colcon-common-extensions vcstool

   .. note::

       If this fails due to an Environment Error, add the :code:`--user` flag to the :code:`pip3` installation command.

Gtest
-----

Gtest is a unit testing library for C++.
By default, *eProsima Fast DDS* does not compile tests.
It is possible to activate them with the opportune
`CMake configuration options <https://cmake.org/cmake/help/v3.6/manual/cmake.1.html#options>`_
when calling colcon_ or CMake_.
For more details, please refer to the :ref:`cmake_options` section.
For a detailed description of the Gtest installation process, please refer to the
`Gtest Installation Guide <https://github.com/google/googletest>`_.

.. _eprosima_dependencies:

eProsima dependencies
=====================

If it already exists in the system an installation of Fast DDS library with version greater than `2.3.0` and
an installation of Fast DDS Statistics Backend, just source these
libraries when building the Fast DDS Monitor by using the command:

.. code-block:: bash

    source <fastdds-installation-path>/install/setup.bash

In other case, just download Fast DDS project from sources and build it together with Fast DDS Monitor using colcon
as it is explained in section :ref:`colcon_installation`.

Qt Installation
===============

Qt 5.15 is needed in order to build Fast DDS Monitor.
To install this Qt version, refer to

.. todo::

    When Qt download goes, add link here to download page.
    `<https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwi1ooPa7JnxAhVEuqQKHcHPBlsQFjABegQIAxAE&`
    `url=https%3A%2F%2Fdownload.qt.io%2Fofficial_releases%2Fqt%2F5.15%2F&usg=AOvVaw3UbW9sxLQ9lUXskwMLwLn5>`

.. _colcon_installation:

*******************
Colcon installation
*******************

Create a :code:`Fast-DDS-Monitor` directory and download the :code:`.repos` file that will be used to install
*eProsima Fast DDS Monitor* and its dependencies:

   .. code-block:: bash

       mkdir -p ~/Fast-DDS-Monitor/src
       cd ~/Fast-DDS-Monitor
       wget https://raw.githubusercontent.com/eProsima/Fast-DDS-monitor/main/fastdds_monitor.repos
       vcs import src < fastdds_monitor.repos

.. note::

    In case there is an already Fast DDS installation in the system it is not required to download and build
    every dependency in the :code:`.repos` file.
    It is just needed to download and build the Fast DDS Monitor project having sourced its dependencies.
    Refer to section :ref:`eprosima_dependencies` in order to check how to source Fast DDS and Fast DDS Statistics Backend
    libraries.

In order to build the project, it must be specified the path to the qt 5.15 :code:`gcc_64` installation path.
Using the standard Qt installation, this path should be similar to :code:`/home/user/Qt/5.15.2/gcc_64`

#. Build the packages:

   .. code-block:: bash

       colcon build --cmake-args -DQT_PATH=<qt-installation-path>

.. _run_app_colcon_sl:

******************
Run an application
******************

To run the *eProsima Fast DDS Monitor* application, source the Fast DDS and Fast DDS Statistics Backend libraries
and execute the executable file that has been installed in :code:`<install-path>/fastdds_monitor/bin/fastdds_monitor`:

.. code-block:: bash

    source install/setup.bash
    ./<install-path>/fastdds_monitor/bin/fastdds_monitor

Be sure that this executable has execution system permission.

.. External links

.. _colcon: https://colcon.readthedocs.io/en/released/
.. _CMake: https://cmake.org
.. _pip: https://pypi.org/project/pip/
.. _wget: https://www.gnu.org/software/wget/
.. _git: https://git-scm.com/
.. _OpenSSL: https://www.openssl.org/
.. _Gtest: https://github.com/google/googletest
.. _vcstool: https://pypi.org/project/vcstool/
