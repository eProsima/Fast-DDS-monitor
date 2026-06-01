.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _pro_domain_view:
.. _pro_domain_graph:

###########
Domain View
###########

The *Domain View* shows all entities belonging to the same DDS domain as an interactive graph.
Entities are displayed encapsulated inside their physical context, with arrows indicating the
publisher–subscriber relationships through their shared topics.
Arrows run from a DataWriter to its topic, and from a topic to its DataReaders.

.. thumbnail:: /rst/figures/screenshots/domain_graph_pro.png
    :align: center

Filtering the graph by topic shows only the entities whose endpoints publish to or subscribe from
the selected topic, opened in a new tab.

.. thumbnail:: /rst/figures/screenshots/shapes_topic_pro.png
    :align: center

Each topic's IDL type definition is also accessible from the *Domain View*.

.. thumbnail:: /rst/figures/screenshots/IDL_img_pro.png
    :align: center

Right-clicking the IDL view opens a context menu with options to copy selected text, select all, or
copy the title to the clipboard.
When the type is a ROS 2 type, the IDL and type name are shown demangled by default, indicated by a
badge in the upper-right corner.
Use **View → Revert ROS 2 Demangling** to display the raw type, or **View → Perform ROS 2 Demangling**
to restore demangling.

Clicking any entity in the graph displays its details in the :ref:`pro_info_panel`.
Right-clicking an entity allows you to rename its alias, filter the problem log to that entity, or
for topics - filter the domain graph to show only the entities related to that topic.

The :ref:`right_pane_config` sidebar |Pro| provides per-entity visibility controls.
Individual topics, hosts, users, processes, participants, writers, and readers can be shown or hidden
by alias, with **Show All** and **Hide All** bulk actions.
See :ref:`domain-graph` for details.
