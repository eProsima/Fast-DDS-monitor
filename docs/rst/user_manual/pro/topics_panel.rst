.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _topics_panel:

#####################
Topics Explorer |Pro|
#####################

The *Topics Explorer* is a panel in the left sidebar that gives you a topic-centered view of the DDS
network. It lists every topic discovered across all active monitors in one place and lets you filter,
inspect, and act on topics without having to navigate through the entity hierarchy.

.. _topics_panel_location:

Accessing the Topics Explorer
==============================

The Topics Explorer is opened from the vertical icon bar on the far left of the application window. The
bar contains five icons stacked top to bottom: the main entity explorer, the Topics Explorer |topic_icon|,
alerts, status, and issues. Click the |topic_icon| icon to open the Topics Explorer. It appears in the
left sidebar between the main entity monitoring panel and the alerts panel. Clicking the same icon again
while the sidebar is already showing the Topics Explorer collapses the sidebar.

.. _topics_panel_layout:

Panel Layout
============

The panel is organized into three areas from top to bottom.

**Header bar**

A fixed label reading *TOPICS* with a blue underline marks the panel. It is always visible at the top.

**Filter bar**

A text field with a |search| icon lets you filter the topic list by name. Typing any text hides topics
whose names do not contain that string. The filter is case-insensitive and applies instantly as you type.
Clearing the field restores the full list. When the filter is active and no topics match, the list shows
a *No topics match filter* notice. When no topics have been discovered at all, it shows *No topics
discovered*.

**Topic list**

The main scrollable area lists every discovered topic as a row. Each row shows the topic name on the left
and the IDL type name in a smaller, muted font on the right. Both horizontal and vertical scrollbars
appear when the content overflows the panel width.

.. _topics_panel_expand:

Expanding Topics
================

Clicking a topic row toggles it open or closed. A small arrow chevron on the left of each row indicates
the current state, pointing right when collapsed and downward when expanded.

When a topic is expanded, the rows below it show the fields parsed from the topic's IDL type definition.
Each field row is indented according to its nesting depth. Struct fields that contain children show their
own chevron and can be expanded further, up to a maximum of three nesting levels. Leaf fields show their
field name on the left and the IDL type in a small muted label on the right.

.. _topics_panel_fields:

Field Rows
==========

Leaf fields that carry a numeric IDL type (integers, floats, and doubles) are interactive in two ways:

* **Drag to a Topic Chart** by pressing and holding a numeric leaf field and dragging it onto an open
  :ref:`Topic Chart <topic_charts>` pane. A drag badge appears under the cursor showing the field path
  while dragging. Dropping the field onto the chart adds it as a new series.

* **Right-click** a numeric leaf field to open a small context menu with a **Plot field** action, which
  opens a new :ref:`Topic Chart <topic_charts>` for that field directly.

Non-numeric struct or array fields can be expanded to reach their numeric children but cannot be dragged
or plotted themselves.

.. _topics_panel_context_actions:

Topic Context Menu
==================

Right-clicking any topic row opens a context menu with the following actions:

* **Change alias** opens a dialog to assign a custom display name to the topic.
* **View problems** filters the status log panel to show only events for this topic.
* **Show domain graph** (or **Show topic graph**) opens the domain or topic graph view for this topic.
* **Data type IDL view** opens an :ref:`IDL Pane <dockable_idl_pane>` showing the full IDL definition for
  the topic type.
* **Set alert** opens the alert configuration dialog for this topic.
* **Spy topic data** opens a :ref:`Spy Pane <dockable_spy_pane>` subscribed to this topic. This action is
  disabled for built-in Fast DDS topics that cannot be subscribed to.
* **Chart topic data** opens a :ref:`Topic Chart <topic_charts>` with this topic pre-selected. This action
  is disabled for built-in and statistics Fast DDS topics.

.. _topics_panel_domain_filter:

Multiple Monitors
=================

When more than one monitor is active (see :ref:`multiple_monitors`), the Topics Explorer shows topics from
all of them together. The domain identifier shown in the context menu and passed to any opened pane
identifies which monitor the topic belongs to, so actions such as Spy or Chart always target the correct
DDS environment even when the same topic name appears in more than one domain.
