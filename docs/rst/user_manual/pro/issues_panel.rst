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

The following is an example of tracked error events:

**Monitor already initialized**
    Attempting to start monitoring a DDS Domain or Discovery Server network that is already active.
    Select **Retry** to open the initialization dialog again and choose a different domain number or
    server address.
