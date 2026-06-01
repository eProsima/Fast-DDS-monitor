.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_issues_panel:
.. _pro_issues_panel_layout:

############
Issues Panel
############

The issues panel lists error events reported by the application.
Each entry describes what went wrong and, where applicable, offers a **Retry** button or a link to
the relevant documentation.
Most errors also produce a message in the terminal window.

.. figure:: /rst/figures/screenshots/issues_panel_pro.png
    :align: center

The following error events are currently tracked:

**Monitor already initialized**
    Attempting to start monitoring a DDS Domain or Discovery Server network that is already active.
    Select **Retry** to open the initialization dialog again and choose a different domain number or
    server address.

**Monitor initialization failed**
    The application could not connect to the specified DDS Domain or Discovery Server.
    Common causes include an unreachable Discovery Server address, a domain number outside the valid
    range (0-200), or a network configuration that blocks DDS multicast traffic.
    Check the connection parameters and try again.

**XML profile load error**
    The selected XML profiles file could not be parsed, or the chosen profile is invalid or
    incomplete.
    Verify that the file is well-formed and that the selected profile contains a valid
    DomainParticipant configuration.
    See the `Fast DDS XML configuration documentation <https://fast-dds.docs.eprosima.com/en/stable/fastdds/xml_configuration/xml_configuration.html>`_
    for the expected format.

**Database error**
    An internal error occurred while reading from or writing to the statistics database.
    This can happen if the database runs out of memory during a long session with high entity counts.
    Use **Edit - Delete Statistics Data** or the scheduler to periodically clear accumulated data
    and free memory.

**Scheduler error**
    A scheduled operation (database dump, statistics clear, or inactive-entity cleanup) could not
    be completed.
    Common causes include a missing output directory or one that cannot be written to for the dump
    file.
    Check the scheduler configuration from **Edit - Scheduler Configuration**.
