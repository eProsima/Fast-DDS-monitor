.. include:: ../../exports/alias.include
.. include:: ../../exports/roles.include

.. _right_pane_config:

###################################
Right-Side Pane Configuration |Pro|
###################################

The *Right-Side Pane Configuration* panel is a sidebar that slides in from the right edge of the workspace.
It provides inline configuration for any pane in the workspace: you can create new panes, edit the
settings of existing ones, and switch a pane from one type to another, all without opening a separate
dialog.

.. _right_pane_config_opening:

Opening the Panel
=================

There are several ways to open the configuration panel:

* Click the |gear| button in the header of any existing pane to open the panel configured for that pane.
* Click an empty pane placeholder to enter the pane creation flow for that slot.
* The panel can also be opened programmatically when you use context menu actions that target it, such as
  opening a new pane from the split menu on any pane header.

To close the panel, click the **✕** button in its header.

.. _right_pane_config_layout:

Panel Layout
============

The panel has two fixed elements at the top that are always visible when a pane is selected or a creation
flow is active.

**Header bar**

Shows the label *PANEL CONFIGURATION* and a close button on the right.

**Pane type switcher**

A row of buttons labelled **Stats**, **Topic**, **Spy**, **IDL**, and **Image** lets you switch which type
of pane the panel is configuring. The active type is highlighted in blue.

When a pane is already selected, clicking a different type button switches the configuration form shown in
the panel so you can preview the creation options for that type. The pane in the workspace is not affected
until you confirm by clicking the create button. At that point the original pane is replaced in its cell.
Clicking the current pane's own type button at any time returns to its live configuration.

Below the type switcher, the content area shows the configuration form specific to the selected pane type
and its current mode.

.. _right_pane_config_modes:

Creation vs. Configuration Mode
================================

The panel operates in one of two modes depending on how it was opened.

In **creation mode**, the panel shows a wizard-style form for a pane type that does not yet exist. You
select the domain, topic, and other required parameters, then confirm to create the pane. Creation forms
include a cancel button that discards the flow without affecting the workspace layout.

In **configuration mode**, the panel shows the live settings for an already-open pane. Changes take effect
through explicit action buttons such as **Apply & Restart** or **Apply & Reload** rather than
automatically, so you can adjust multiple fields before committing.

.. _right_pane_config_by_type:

Configuration by Pane Type
===========================

Each pane type exposes a different set of sections in the configuration panel. The sections specific to
each type are documented in detail on the corresponding pane pages. The following is a summary with
references.

Statistics Chart
----------------

See :ref:`chart_panel` for the full statistics chart documentation.

The configuration panel for a statistics chart covers:

* Chart name editing.
* Data kind, time window, update period, and maximum data points, applied together with **Apply &
  Reset Chart**.
* Series list with per-series controls for label, color, visibility, max data points, and removal.
* An inline add-series form with entity and statistics kind selection.
* Y-axis locking with explicit minimum and maximum (and X-axis for historic charts).
* Display toggles for the legend and data points.
* Pause/resume toggle.
* Panel Actions with split submenus and screenshot options.

Topic Chart
-----------

See :ref:`topic_charts` for the full topic chart documentation.

The configuration panel for a topic chart covers:

* Chart name editing.
* Domain, time window, and maximum data points, applied together with **Apply & Reset Chart**.
* Series list with per-series controls for label, color, visibility, max data points, and removal.
* An inline add-series form with topic and numeric field selection. Click **+ Add Series** to expand it.
  Select a topic, wait for the first sample to arrive so fields are populated, then pick a field and
  confirm with **Add Series** or double-click the field.
* Y-axis locking with explicit minimum and maximum.
* Display toggles for the legend, data points, and the sliding window mode.
* Panel Actions with split submenus and screenshot options.
* Bulk actions: Show All Series, Hide All Series, Clear Chart.

Spy Pane
--------

See :ref:`dockable_spy_pane` for the full spy pane documentation.

The configuration panel for a spy pane covers:

* Domain and topic selection with **Apply & Restart** to switch the subscription.
* Playback toggle to start or stop the live data feed.
* Panel Actions with split submenus.
* Actions: Expand All, Collapse All, Clear, Copy JSON to Clipboard.

IDL Pane
--------

See :ref:`dockable_idl_pane` for the full IDL pane documentation.

The configuration panel for an IDL pane covers:

* A read-only **Topic** section showing the current topic name, domain, and resolved type name.
* A **Change Topic** section with domain and topic selection and an **Apply & Reload** button.
* A **Display** toggle for ROS 2 demangling.
* Panel Actions with split submenus.
* Actions: Select All.

Image Pane
----------

See :ref:`image_pane` for the full image pane documentation.

The configuration panel for an image pane covers:

* A read-only **Topic** section showing the current topic name and domain.
* A **Change Topic** section listing only image-compatible topics, with an **Apply & Reload** button.
* A **Playback** toggle to start or stop the frame stream.
* A read-only **Status** indicator (Streaming, Waiting for frames, Paused, or Error).
* A **Last Error** section visible only when a decode error has occurred.
* A **Frame Info** section showing resolution, encoding, and frame count once frames arrive.
* Panel Actions with split submenus.
