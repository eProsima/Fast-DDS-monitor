.. include:: ../../../exports/alias.include
.. include:: ../../../exports/roles.include

.. _cmake_options:

#############
CMake options
#############

*eProsima Fast DDS Monitor* provides numerous CMake options for changing the behavior and configuration of
*Fast DDS Monitor*.
These options allow the developer to enable/disable certain *Fast DDS Monitor* settings by defining these options to
``ON``/``OFF`` at the CMake execution, or set the required path to certain dependencies.

.. warning::
    These options are only for developers who installed the *Fast DDS Monitor* following the compilation steps
    described in :ref:`developer_manual_installation_sources_linux`.

.. list-table::
    :header-rows: 1

    *   - Option
        - Description
        - Possible values
        - Default
    *   - :class:`QT_PATH`
        - Path to the directory where Qt has been installed. This |br|
          argument is required to find the Qt binaries. An example |br|
          of the path to the Qt 5.15 installation directory is: |br|
          ``/opt/Qt/5.15.2/gcc_64``.
        - -
        - -
    *   - :class:`BUILD_TEST`
        - Build the *Fast DDS Monitor* and documentation tests. |br|
          Setting :class:`BUILD_TEST` to ``ON`` sets :class:`BUILD_DOCUMENTATION_TESTS` |br|
          to ``ON``.
        - ``OFF`` |br|
          ``ON``
        - ``OFF``
    *   - :class:`BUILD_TEST_DOCUMENTATION`
        - Build the *Fast DDS Monitor* documentation tests. It is |br|
          set to ``ON`` if :class:`BUILD_TESTS` is set to ``ON``. |br|
        - ``OFF`` |br|
          ``ON``
        - ``OFF``
    *   - :class:`BUILD_DOCUMENTATION`
        - Build the *Fast DDS Monitor* documentation. It is |br|
          set to ``ON`` if :class:`BUILD_TESTS_DOCUMENTATION` is set |br|
          to ``ON``.
        - ``OFF`` |br|
          ``ON``
        - ``OFF``
    *   - :class:`BUILD_MOCK`
        - Build the *Fast DDS Statistics Backend* mocks, which is a |br|
          simulator of a *Fast DDS* application that generates random |br|
          statistics data for testing the *Fast DDS Monitor*. It is |br|
          set to ``ON`` if :class:`BUILD_TESTS` is set |br|
          to ``ON``, :class:`BUILD_MOCK` is set to ``ON``, or |br|
          :class:`COMPLEX_MOCK` is set to ``ON``.
        - ``OFF`` |br|
          ``ON``
        - ``OFF``
    *   - :class:`STATIC_MOCK`
        - Build the *Fast DDS Statistics Backend* static mock and link |br|
          the *Fast DDS Monitor* application against it. The static |br|
          mock is a simulator of a *Fast DDS* application that generates |br|
          deterministic statistics data for testing the *Fast DDS* |br|
          *Monitor*. It is set to ``ON`` if :class:`BUILD_TESTS` is set |br|
          to ``ON``.
        - ``OFF`` |br|
          ``ON``
        - ``OFF``
    *   - :class:`COMPLEX_MOCK`
        - Build the *Fast DDS Statistics Backend* complex mock and link |br|
          the *Fast DDS Monitor* application against it. The complex |br|
          mock is a simulator of a *Fast DDS* application that random |br|
          statistics data for testing the *Fast DDS Monior* |br|
          It is set to ``ON`` if :class:`BUILD_TESTS` is set |br|
          to ``ON``.
        - ``OFF`` |br|
          ``ON``
        - ``OFF``
