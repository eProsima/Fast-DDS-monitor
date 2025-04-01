.. _developer_manual_installation_sources_linux:

###############################
Linux installation from sources
###############################

The instructions for installing the *eProsima Fast DDS Monitor application* from sources and the required
`Qt` installation are provided in this page.
It is organized as follows:

.. _fastdds_lib_sl:

Dependencies installation
=========================

*Fast DDS Monitor* depends on *eProsima Fast DDS* library, *eProsima Fast DDS Statistics Backend* library, Qt and
certain Debian packages.
This section describes the instructions for installing *eProsima Fast DDS* dependencies and requirements in a Linux
environment from sources.
The following packages will be installed:

- ``foonathan_memory_vendor``, an STL compatible C++ memory allocator library.
- ``fastcdr``, a C++ library that serializes according to the standard CDR serialization mechanism.
- ``fastdds``, the core library of eProsima Fast DDS library.
- ``fastdds_statistics_backend``, a C++ library that provides a simple and easy-to-use API for interacting with data
  from *Fast DDS* statistics module

First of all, the :ref:`Requirements <requirements>` and :ref:`Dependencies <dependencies>` detailed below need to be
met.
Afterwards, the user can choose whether to follow either the :ref:`colcon <colcon_installation>` or the
:ref:`CMake <cmake_installation>` installation instructions.

.. _requirements:

Requirements
------------

The installation of *eProsima Fast DDS* in a Linux environment from binaries requires the following tools to be
installed in the system:

* :ref:`cmake_gcc_pip_wget_git_sl`
* :ref:`colcon_install` [optional]
* :ref:`gtest_sl` [for test only]


.. _cmake_gcc_pip_wget_git_sl:

CMake, g++, pip, wget and git
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

These packages provide the tools required to install *eProsima Fast DDS* and its dependencies from command line.
Install CMake_, `g++ <https://gcc.gnu.org/>`_, pip_, wget_ and git_ using the package manager of the appropriate
Linux distribution. For example, on Ubuntu use the command:

.. code-block:: bash

    sudo apt install cmake g++ pip wget git


.. _colcon_install:

Colcon
^^^^^^

colcon_ is a command line tool based on CMake_ aimed at building sets of software packages.
Install the ROS 2 development tools (colcon_ and vcstool_) by executing the following command:

.. code-block:: bash

    pip3 install -U colcon-common-extensions vcstool

.. note::

    If this fails due to an Environment Error, add the :code:`--user` flag to the :code:`pip3` installation command.


.. _gtest_sl:

Gtest
^^^^^

Gtest is a unit testing library for C++.
By default, *eProsima Fast DDS Monitor* does not compile tests.
It is possible to activate them with the opportune
`CMake options <https://colcon.readthedocs.io/en/released/reference/verb/build.html#cmake-options>`_
when calling colcon_ or CMake_.
For more details, please refer to the :ref:`cmake_options` section.
For a detailed description of the Gtest installation process, please refer to the
`Gtest Installation Guide <https://github.com/google/googletest>`_.

.. _dependencies:

Dependencies
------------

*eProsima Fast DDS* has the following dependencies, when installed from sources in a Linux environment:

* :ref:`asiotinyxml2_sl`
* :ref:`openssl_sl`
* :ref:`eprosima_dependencies`
* :ref:`qt_installation`

.. _asiotinyxml2_sl:

Asio and TinyXML2 libraries
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Asio is a cross-platform C++ library for network and low-level I/O programming, which provides a consistent
asynchronous model.
TinyXML2 is a simple, small and efficient C++ XML parser.
Install these libraries using the package manager of the appropriate Linux distribution.
For example, on Ubuntu use the command:

.. code-block:: bash

    sudo apt install libasio-dev libtinyxml2-dev

.. _openssl_sl:

OpenSSL
^^^^^^^

OpenSSL is a robust toolkit for the TLS and SSL protocols and a general-purpose cryptography library.
Install OpenSSL_ using the package manager of the appropriate Linux distribution.
For example, on Ubuntu use the command:

.. code-block:: bash

   sudo apt install libssl-dev

.. _eprosima_dependencies:

eProsima dependencies
^^^^^^^^^^^^^^^^^^^^^

If there is already in the system an installation of *Fast DDS* library with version greater than `2.3.0` and
an installation of *Fast DDS Statistics Backend*, just source these
libraries when building the *Fast DDS Monitor* by using the command:

.. code-block:: bash

    source <fastdds-installation-path>/install/setup.bash

Otherwise, just download *Fast DDS* project from sources and build it together with *Fast DDS Monitor* using colcon
as it is explained in section :ref:`colcon_installation`.


.. _qt_installation:

Qt 5.15
^^^^^^^

Qt 5.15 is needed in order to build *Fast DDS Monitor*.
To install this Qt version, refer to `Qt Downloads <https://www.qt.io/download>`_ website.

.. note::

    When going through the installation steps, make sure the box of component *Qt Charts* is checked.


.. _colcon_installation:

Colcon installation
===================

#.  Create a :code:`Fast-DDS-Monitor` directory and download the :code:`.repos` file that will be used to install
    *eProsima Fast DDS Monitor* and its dependencies:

    .. code-block:: bash

        mkdir -p ~/Fast-DDS-Monitor/src
        cd ~/Fast-DDS-Monitor
        wget https://raw.githubusercontent.com/eProsima/Fast-DDS-monitor/main/fastdds_monitor.repos
        vcs import src < fastdds_monitor.repos

    .. note::

        In case there is an already *Fast DDS* installation in the system it is not required to download and build
        every dependency in the :code:`.repos` file.
        It is just needed to download and build the *Fast DDS Monitor* project having sourced its dependencies.
        Refer to section :ref:`eprosima_dependencies` in order to check how to source *Fast DDS* and
        *Fast DDS Statistics Backend* libraries.

    In order to build the project, it must be specified the path to the Qt 5.15 :code:`gcc_64` installation path.
    Using the standard Qt installation, this path should be similar to :code:`/home/<user>/Qt/5.15.2/gcc_64`.

#.  Build the packages:

    .. code-block:: bash

        colcon build --cmake-args -DQT_PATH=<qt-installation-path>

.. note::

    Being based on CMake_, it is possible to pass the CMake configuration options to the :code:`colcon build`
    command. For more information on the specific syntax, please refer to the
    `CMake specific arguments <https://colcon.readthedocs.io/en/released/reference/verb/build.html#cmake-specific-arguments>`_
    page of the colcon_ manual.


.. _cmake_installation:

CMake installation
==================

.. Warning::

    Only use this installation method if the colcon_ installation method is not suitable for your needs.

This section explains how to compile *eProsima Fast DDS Monitor* with CMake_, either
:ref:`locally <local_installation_sl>` or :ref:`globally <global_installation_sl>`.

.. _local_installation_sl:

Local installation
------------------

#.  Create a :code:`Fast-DDS` directory where to download and build *eProsima Fast DDS Monitor* and its dependencies:

    .. code-block:: bash

        mkdir ~/Fast-DDS-Monitor

#.  Clone the following dependencies and compile them using CMake_.

    * `Foonathan memory <https://github.com/foonathan/memory>`_

      .. code-block:: bash

          cd ~/Fast-DDS-Monitor
          git clone https://github.com/eProsima/foonathan_memory_vendor.git
          mkdir foonathan_memory_vendor/build
          cd foonathan_memory_vendor/build
          cmake .. -DCMAKE_INSTALL_PREFIX=~/Fast-DDS-Monitor/install -DBUILD_SHARED_LIBS=ON
          cmake --build . --target install

    * `Fast CDR <https://github.com/eProsima/Fast-CDR.git>`_

      .. code-block:: bash

          cd ~/Fast-DDS-Monitor
          git clone https://github.com/eProsima/Fast-CDR.git
          mkdir Fast-CDR/build
          cd Fast-CDR/build
          cmake .. -DCMAKE_INSTALL_PREFIX=~/Fast-DDS-Monitor/install
          cmake --build . --target install

    * `Fast DDS <https://github.com/eProsima/Fast-DDS.git>`_

        .. code-block:: bash

            cd ~/Fast-DDS-Monitor
            git clone https://github.com/eProsima/Fast-DDS.git
            mkdir Fast-DDS/build
            cd Fast-DDS/build
            cmake .. -DCMAKE_INSTALL_PREFIX=~/Fast-DDS-Monitor/install -DCMAKE_PREFIX_PATH=~/Fast-DDS-Monitor/install
            cmake --build . --target install

    * `Fast DDS Statistics Backend <https://github.com/eProsima/Fast-DDS-statistics-backend.git>`_

      .. code-block:: bash

          cd ~/Fast-DDS-Monitor
          git clone https://github.com/eProsima/Fast-DDS-statistics-backend.git
          mkdir Fast-DDS-statistics-backend/build
          cd Fast-DDS-statistics-backend/build
          cmake .. -DCMAKE_INSTALL_PREFIX=~/Fast-DDS-Monitor/install -DCMAKE_PREFIX_PATH=~/Fast-DDS-Monitor/install
          cmake --build . --target install

#.  Once all dependencies are installed, install *eProsima Fast DDS Monitor*:

    .. code-block:: bash

        cd ~/Fast-DDS-Monitor
        git clone https://github.com/eProsima/Fast-DDS-monitor.git
        mkdir Fast-DDS-monitor/build
        cd Fast-DDS-monitor/build
        cmake .. \
            -DCMAKE_INSTALL_PREFIX=~/Fast-DDS-Monitor/install \
            -DCMAKE_PREFIX_PATH=~/Fast-DDS-Monitor/install \
            -DQT_PATH=<qt-installation-path>
        cmake --build . --target install


.. note::

    By default, *eProsima Fast DDS Monitor* does not compile tests.
    However, they can be activated by downloading and installing `Gtest <https://github.com/google/googletest>`_
    and building with CMake option ``-DBUILD_TESTS=ON``.


.. _global_installation_sl:

Global installation
-------------------

To install *eProsima Fast DDS* system-wide instead of locally, remove all the flags that
appear in the configuration steps of :code:`Fast-CDR`, :code:`Fast-DDS`, :code:`Fast-DDS-Statistics-Backend`, and
:code:`Fast-DDS-Monitor`, and change the flags in the configuration step of :code:`foonathan_memory_vendor` to the
following:

.. code-block:: bash

    -DCMAKE_INSTALL_PREFIX=/usr/local/ -DBUILD_SHARED_LIBS=ON

.. _run_app_colcon_sl:

Run an application
==================

To run the *eProsima Fast DDS Monitor* application, source the *Fast DDS* and *Fast DDS Statistics Backend* libraries
and execute the executable file that has been installed in :code:`<install-path>/fastdds_monitor/bin/fastdds_monitor`:

.. code-block:: bash

    # If built has been done using colcon, all projects could be sourced as follows
    source install/setup.bash
    ./<build-path>/fastdds_monitor/fastdds_monitor

Be sure that this executable has execute permissions.

.. External links

.. _colcon: https://colcon.readthedocs.io/en/released/
.. _CMake: https://cmake.org
.. _pip: https://pypi.org/project/pip/
.. _wget: https://www.gnu.org/software/wget/
.. _git: https://git-scm.com/
.. _OpenSSL: https://www.openssl.org/
.. _Gtest: https://github.com/google/googletest
.. _vcstool: https://pypi.org/project/vcstool/
