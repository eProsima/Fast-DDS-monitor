.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_domain_view:
.. _pro_domain_graph:

#################
Domain View |Pro|
#################

The *Domain View* shows all entities belonging to the same DDS domain as an interactive graph.
Entities are displayed encapsulated inside their physical context, with arrows indicating the
publisher-subscriber relationships through their shared topics.
Arrows run from a DataWriter to its topic, and from a topic to its DataReaders.

.. thumbnail:: /rst/figures/screenshots/domain_graph_pro.png
    :align: center

Entities
========

Clicking any entity in the graph selects it; its details appear in the
:ref:`pro_info_panel` in the Explorer Panel.

Right-clicking an entity opens a context menu with the following actions:

- **Change alias** - opens a dialog to assign a custom display name to the entity.
  The alias is used throughout the application.
- **View problems** - filters the Problem Summary panel to show only issues related to this entity.

Topics
======

Topics appear as vertical lines in the graph, with DataWriters feeding into them and DataReaders
consuming from them.

Right-clicking a topic opens a context menu with additional actions besides the possibility to change alias and to view problems:

- **Filter topic graph** - opens a filtered view showing only the entities whose endpoints
  publish to or subscribe from this topic.
  The filtered graph opens in a new tab.
- **Data type IDL view** - opens a :ref:`dockable_idl_pane` showing the full IDL type definition
  for the topic. For ROS 2 topics the IDL is shown demangled by default; see
  :ref:`ros2_demangling` for details.
- **Set alert** - opens a dialog to create a new alert for this topic.
- **Spy topic data** - opens a :ref:`dockable_spy_pane` for this topic.
- **Publish topic data** - opens a :ref:`publisher_pane` for this topic.
- **Chart topic data** - opens a :ref:`time_series` chart for this topic.

.. thumbnail:: /rst/figures/screenshots/shapes_topic_pro.png
    :align: center

Metatraffic
===========

Metatraffic entities - *Fast DDS* statistics topics, ROS discovery topics, and their associated
endpoints - are hidden from the graph by default.
When hidden, they are completely excluded from the domain view and entity lists.

To show metatraffic in the graph, go to **View -> Hide/Show Metatraffic**.
When visible, metatraffic topics and their endpoints appear in the domain graph like any other
entity and can be interacted with in the same way.

Visibility |Pro|
================

Individual entities can be shown or hidden from the graph without removing them from the monitor.
This is controlled through the right-side configuration panel for the Domain View.

Click the |gear| button in the Domain View tab header to open the configuration panel.
Each entity type (Topics, Hosts, Users, Processes, Participants, DataWriters, DataReaders) is
listed in its own collapsible section with a checkbox per entity alias.
Clear a checkbox to hide that entity; the entity remains listed and can be restored at any time.
Hiding a container entity (such as a Host or Process) also hides all its descendants - child
entities cannot remain visible as orphan nodes in the graph.

See :ref:`domain-graph` for the full description of the visibility control panel.

Routed Domains and Proxy Entities |Pro|
=======================================

When multiple monitors are active (see :ref:`multiple_monitors`), each monitor tab shows its own
independent domain graph.
Entities from one domain are not shown in another domain's graph unless they are explicitly
bridged or proxied.

Proxy entities - entities from other domains whose statistics messages are reaching the current
monitor's domain - can optionally be displayed.
Go to **View -> Hide/Show Proxy Entities** to toggle their visibility.
When visible, proxy entities appear in the graph and entity lists and their data can be charted.
