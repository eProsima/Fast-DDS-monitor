.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_alerts_panel:
.. _pro_alerts_panel_layout:

############
Alerts Panel
############

The alerts panel is located on the left side of the application window and allows the user to define
conditions to monitor and receive notifications about specific events in the DDS network.
It consists of two sections:

.. figure:: /rst/figures/screenshots/alert_panel_pro.png
    :align: center

.. _pro_alerts_list_panel:
.. _pro_alert_list_layout:

Alerts List
===========

Displays the list of alerts defined by the user.
Alerts are created using the |create_alert| button in the Shortcuts Bar or the **+** button in the
upper-right corner of the panel.
Selecting an alert highlights it and shows its details in the :ref:`pro_alert_info_panel`.
Right-click an alert to remove it.

.. _pro_alert_info_panel:
.. _pro_alert_data_layout:

Alert Info
==========

Displays the configuration of the alert currently selected in the Alerts List, including its name,
domain, host, user, topic, threshold, and duration.

For alert event notifications, see :ref:`pro_alert_messages_panel`.
