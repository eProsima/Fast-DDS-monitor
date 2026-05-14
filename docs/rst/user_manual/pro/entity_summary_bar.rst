.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _entity_summary_bar:

########################
Entity Summary Bar |Pro|
########################

The *Entity Summary Bar* is a compact counter strip in the bottom status bar of the *Fast DDS Monitor Pro*
window. It shows the total number of the four main DDS entity types discovered across all active monitors,
giving you a quick read of your network at a glance without opening any panel.

.. _entity_summary_bar_counters:

Displayed Counters
==================

The bar shows four labelled counters inline:

* **P** is the total number of DomainParticipants discovered.
* **W** is the total number of DataWriters discovered.
* **R** is the total number of DataReaders discovered.
* **T** is the total number of distinct DDS Topics discovered.

All four values aggregate across every active monitor tab and update automatically as entities are
discovered or removed.

When the **Show Proxy Entities** option is enabled in the **View** menu, a blue asterisk appears
immediately after the counters to indicate that proxy entities are included in the totals.

.. _entity_summary_bar_tooltip:

Tooltip
=======

Hovering over the counter strip shows a tooltip that expands the same four values into a labelled list
under the heading *Entities discovered*, writing out each entity type by its full name.

When proxy entities are visible and at least one proxy entity of a given type exists, the tooltip shows
the proxy count in parentheses next to the total for that type.

.. _entity_summary_bar_location:

Location
========

The Entity Summary Bar sits in the bottom status bar of the window, to the right of the error and warning
counters, separated from them by a vertical divider. It remains visible regardless of which monitor tab is
active or how the workspace layout is arranged.
