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

Displays the configuration of the alert currently selected in the Alerts List, including its
domain, host, id, kind, name, time between triggers, topic, and user.

For alert event notifications, see :ref:`pro_alert_messages_panel`.

.. _pro_alert_configuration_panel:

Alert Configuration
===================

The **Configuration** tab in the lower section of the Alerts Panel provides an integrated form for
creating and editing alert rules without opening a separate dialog.

.. figure:: /rst/figures/screenshots/alert_configuration_pro.png
    :align: center

The |help| button is available at the right side of the Configuration tab header.
Clicking it opens a contextual popover with a short description of the pane and tips.

The form contains the following fields:

- **Alert kind** — selects the DDS metric to monitor. The currently supported kinds are
  ``NO_DATA`` (fires when a topic stops receiving data) and ``NEW_DATA`` (fires when a topic
  receives new data).
- **Alert name** — a human-readable label for the alert rule. It is generated automatically from the
  selected kind and entity, but can be overridden manually.
- **Domain** — the DDS domain to monitor. Only domains currently being monitored are listed.
- **Host / User / Topic** — optional entity filters that narrow the scope of the alert to a specific
  host, user process, or topic. Each filter can be set from the discovered entities or entered
  manually using the override toggle.
- **Threshold** — the numeric value that triggers the alert when the metric crosses it. The units
  shown next to the field depend on the selected alert kind.
- **Time between alerts (ms)** — the minimum interval between two consecutive firings of the same
  alert rule, in milliseconds.
- **Timeout (ms)** — how long the metric must remain beyond the threshold before the alert fires,
  in milliseconds.
- **Script** — an optional path to a script executed when the alert fires.

Click **Create** to add a new alert rule, or **Save** to update an existing one after selecting it
in the Alerts List.
